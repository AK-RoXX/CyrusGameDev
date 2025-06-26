#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoxDataFetcher.h"
#include "BoxSpawnerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPECYRUS_API UBoxSpawnerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBoxSpawnerComponent();

protected:
    virtual void BeginPlay() override;

private:
    void SpawnBoxes(const TArray<FBoxTypeData>& Types, const TArray<FBoxSpawnData>& Objects);
    FBoxTypeData* GetTypeDataByName(const FString& TypeName);

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AActor> BoxActorClass;

    TArray<FBoxTypeData> CachedTypes;
};
