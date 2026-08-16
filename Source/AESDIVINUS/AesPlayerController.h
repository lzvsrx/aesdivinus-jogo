#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AesTypes.h"
#include "AesPlayerController.generated.h"

class AAesCharacter;

UCLASS()
class AESDIVINUS_API AAesPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AAesPlayerController();

    virtual void BeginPlay() override;
    virtual void PlayerTick(float DeltaTime) override;
    virtual void SetupInputComponent() override;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    EAesScreen Screen = EAesScreen::Login;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    FAesAttributes Attributes;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    EArchetypePersonality Personality = EArchetypePersonality::Bravura;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    int32 RouteIndex = 1;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    int32 ChapterIndex = 0;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    float ChapterGoal = 880.0f;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    FString ChapterName = TEXT("Entrada na Floresta Wood");

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    FString DialogueSpeaker;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    FString DialogueText;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    TArray<FString> Choices;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    TArray<FAesEnemyState> Enemies;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    TArray<EAesBrand> ActiveBrands;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    TArray<FString> CraftedItems;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    EAesSquadOrder SquadOrder = EAesSquadOrder::Shield;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    int32 Ore = 0;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    bool bPaused = false;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    bool bInDialogue = false;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    bool bVictory = false;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    float LoadingProgress = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    FString Toast;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    bool bHasSavedGame = false;

    UPROPERTY(BlueprintReadOnly, Category = "AES")
    FString SaveStatusText;

    UFUNCTION(BlueprintCallable, Category = "AES")
    AAesCharacter* GetAesPawn() const;

    FString GetRouteTitle() const;
    FString GetRouteWeapon() const;
    FString GetRouteArmor() const;
    FString GetWeatherName() const;
    float GetHealthPercent() const;
    float GetCouragePercent() const;
    float GetLoyalty() const;

private:
    float MoveAxis = 0.0f;
    float ToastTime = 0.0f;
    float EndDelay = 0.0f;
    float AutoSaveTimer = 0.0f;
    bool bLoadingFromDatabase = false;

    void MoveRight(float Value);
    void Confirm();
    void Back();
    void Jump();
    void Attack();
    void Dodge();
    void Interact();
    void Pause();
    void ChoiceOne();
    void ChoiceTwo();
    void ChoiceThree();

    void ResetAttributesFromRoute();
    void StartLoading();
    void StartGame();
    void LoadChapter(int32 NewChapterIndex);
    void ApplyChoice(int32 ChoiceIndex);
    void SetOrder(EAesSquadOrder NewOrder);
    void ActivateBrand(EAesBrand Brand);
    void UpdateGameplay(float DeltaTime);
    void UpdateEnemies(float DeltaTime);
    void FinishGame(bool bWon);
    void SaveGameDatabase();
    bool LoadGameDatabase(bool bResumeGameplay);
    void ClearRuntimeCombatState();
    bool HasBrand(EAesBrand Brand) const;
    bool HasCraftedAesBlade() const;
    void AddToast(const FString& Message);
};
