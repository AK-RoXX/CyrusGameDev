// BoxDataFetcher.h
#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "BoxDataFetcher.generated.h"

USTRUCT()
struct FBoxTypeData
{
    GENERATED_BODY()

    FString Name;
    FLinearColor Color;
    int32 Health;
    int32 Score;
};

USTRUCT()
struct FBoxTransformData
{
    GENERATED_BODY()

    FVector Location;
    FRotator Rotation;
    FVector Scale;
};

USTRUCT()
struct FBoxSpawnData
{
    GENERATED_BODY()

    FString TypeName;
    FBoxTransformData Transform;
};

DECLARE_DELEGATE_TwoParams(FOnBoxDataReady, const TArray<FBoxTypeData>&, const TArray<FBoxSpawnData>&);

UCLASS()
class PROTOTYPECYRUS_API UBoxDataFetcher : public UObject
{
    GENERATED_BODY()

public:
    static void FetchData(UWorld* WorldContext, FOnBoxDataReady OnDataReady);

private:
    static void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnBoxDataReady Callback);
};
