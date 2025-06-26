#include "FPSGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "BoxSpawnerComponent.h"

AFPSGameModeBase::AFPSGameModeBase()
{
    PlayerScore = 0;
    BoxSpawner = nullptr;

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonPlayerController"));
    if (PlayerControllerBPClass.Class != nullptr)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }
}

void AFPSGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    PlayerScore = 0;

    BoxSpawner = NewObject<UBoxSpawnerComponent>(this);
    if (BoxSpawner)
    {
        BoxSpawner->RegisterComponent(); 
    }

    UE_LOG(LogTemp, Warning, TEXT("AFPSGameModeBase active, ready to spawn boxes!"));
}

void AFPSGameModeBase::AddScore(int32 Amount)
{
    PlayerScore += Amount;
    UE_LOG(LogTemp, Log, TEXT("Score: %d"), PlayerScore);
}

int32 AFPSGameModeBase::GetScore() const
{
    return PlayerScore;
}
