#include "BoxSpawnerComponent.h"
#include "BoxDataFetcher.h"
#include "ColorBoxActor.h"
#include "Engine/World.h"

UBoxSpawnerComponent::UBoxSpawnerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    BoxActorClass = AAColorBoxActor::StaticClass();  
}

void UBoxSpawnerComponent::BeginPlay()
{
    Super::BeginPlay();

    UBoxDataFetcher::FetchData(GetWorld(), FOnBoxDataReady::CreateLambda(
        [this](const TArray<FBoxTypeData>& Types, const TArray<FBoxSpawnData>& Objects)
        {
            CachedTypes = Types;
            SpawnBoxes(Types, Objects);
        }));
}

FBoxTypeData* UBoxSpawnerComponent::GetTypeDataByName(const FString& TypeName)
{
    for (auto& Type : CachedTypes)
    {
        if (Type.Name == TypeName)
        {
            return &Type;
        }
    }
    return nullptr;
}

void UBoxSpawnerComponent::SpawnBoxes(const TArray<FBoxTypeData>& Types, const TArray<FBoxSpawnData>& Objects)
{
    UWorld* World = GetWorld();
    if (!World || !BoxActorClass) return;

    for (const auto& Spawn : Objects)
    {
        FBoxTypeData* TypeData = GetTypeDataByName(Spawn.TypeName);
        if (!TypeData) continue;

        FTransform SpawnTransform;
        SpawnTransform.SetLocation(Spawn.Transform.Location);
        SpawnTransform.SetRotation(FQuat(Spawn.Transform.Rotation));
        SpawnTransform.SetScale3D(Spawn.Transform.Scale);

        AAColorBoxActor* SpawnedBox = World->SpawnActor<AAColorBoxActor>(BoxActorClass, SpawnTransform);
        if (SpawnedBox)
        {
            SpawnedBox->InitializeBox(TypeData->Color, TypeData->Health, TypeData->Score);
        }
    }
}
