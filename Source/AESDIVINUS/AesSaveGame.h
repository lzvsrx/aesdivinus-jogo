#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AesTypes.h"
#include "AesSaveGame.generated.h"

UCLASS()
class AESDIVINUS_API UAesSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 SaveVersion = 1;

    UPROPERTY()
    int32 RouteIndex = 1;

    UPROPERTY()
    int32 ChapterIndex = 0;

    UPROPERTY()
    float ChapterGoal = 880.0f;

    UPROPERTY()
    FString ChapterName;

    UPROPERTY()
    EArchetypePersonality Personality = EArchetypePersonality::Bravura;

    UPROPERTY()
    FAesAttributes Attributes;

    UPROPERTY()
    TArray<EAesBrand> ActiveBrands;

    UPROPERTY()
    TArray<FString> CraftedItems;

    UPROPERTY()
    EAesSquadOrder SquadOrder = EAesSquadOrder::Shield;

    UPROPERTY()
    int32 Ore = 0;

    UPROPERTY()
    FVector2D PlayerPosition = FVector2D(80.0f, 550.0f);

    UPROPERTY()
    float Health = 100.0f;

    UPROPERTY()
    float Courage = 100.0f;

    UPROPERTY()
    float Loyalty = 100.0f;

    UPROPERTY()
    bool bHasValidProgress = false;
};
