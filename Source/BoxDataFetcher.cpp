#include "BoxDataFetcher.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UBoxDataFetcher::FetchData(UWorld* WorldContext, FOnBoxDataReady OnDataReady)
{
    FString URL = TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb(TEXT("GET"));

    // Capture OnDataReady inside a lambda
    Request->OnProcessRequestComplete().BindLambda(
        [OnDataReady](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            UBoxDataFetcher::OnResponseReceived(Request, Response, bWasSuccessful, OnDataReady);
        });

    Request->ProcessRequest();
}

void UBoxDataFetcher::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnBoxDataReady Callback)
{
    if (!bWasSuccessful || !Response.IsValid() || Response->GetResponseCode() != 200)
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP request failed or bad response"));
        return;
    }

    TSharedPtr<FJsonObject> RootObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON"));
        return;
    }

    TArray<FBoxTypeData> TypeList;
    TArray<FBoxSpawnData> ObjectList;

    const TArray<TSharedPtr<FJsonValue>>* Types;
    if (RootObject->TryGetArrayField(TEXT("types"), Types))
    {
        for (const auto& Item : *Types)
        {
            TSharedPtr<FJsonObject> Obj = Item->AsObject();
            if (!Obj.IsValid()) continue;

            FBoxTypeData TypeData;
            TypeData.Name = Obj->GetStringField(TEXT("name"));

            const TArray<TSharedPtr<FJsonValue>>* ColorArray;
            if (Obj->TryGetArrayField(TEXT("color"), ColorArray) && ColorArray->Num() == 3)
            {
                float R = (*ColorArray)[0]->AsNumber();
                float G = (*ColorArray)[1]->AsNumber();
                float B = (*ColorArray)[2]->AsNumber();

                TypeData.Color = FLinearColor(R, G, B);
            }

            TypeData.Health = Obj->GetIntegerField(TEXT("health"));
            TypeData.Score = Obj->GetIntegerField(TEXT("score"));

            TypeList.Add(TypeData);
        }
    }

    const TArray<TSharedPtr<FJsonValue>>* Objects;
    if (RootObject->TryGetArrayField(TEXT("objects"), Objects))
    {
        for (const auto& Item : *Objects)
        {
            TSharedPtr<FJsonObject> Obj = Item->AsObject();
            if (!Obj.IsValid()) continue;

            FBoxSpawnData SpawnData;
            SpawnData.TypeName = Obj->GetStringField(TEXT("type"));

            TSharedPtr<FJsonObject> TransformObj = Obj->GetObjectField(TEXT("transform"));

            const TArray<TSharedPtr<FJsonValue>>* LocArr;
            const TArray<TSharedPtr<FJsonValue>>* RotArr;
            const TArray<TSharedPtr<FJsonValue>>* ScaleArr;

            if (TransformObj->TryGetArrayField(TEXT("location"), LocArr) &&
                TransformObj->TryGetArrayField(TEXT("rotation"), RotArr) &&
                TransformObj->TryGetArrayField(TEXT("scale"), ScaleArr))
            {
                SpawnData.Transform.Location = FVector((*LocArr)[0]->AsNumber(), (*LocArr)[1]->AsNumber(), (*LocArr)[2]->AsNumber());
                SpawnData.Transform.Rotation = FRotator((*RotArr)[1]->AsNumber(), (*RotArr)[2]->AsNumber(), (*RotArr)[0]->AsNumber());
                SpawnData.Transform.Scale = FVector((*ScaleArr)[0]->AsNumber(), (*ScaleArr)[1]->AsNumber(), (*ScaleArr)[2]->AsNumber());
            }

            ObjectList.Add(SpawnData);
        }
    }

    Callback.ExecuteIfBound(TypeList, ObjectList);
}
