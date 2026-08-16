#include "AesPlayerController.h"
#include "AesCharacter.h"
#include "AesSaveGame.h"
#include "AesStatsComponent.h"
#include "Kismet/GameplayStatics.h"

namespace
{
    struct FRouteData
    {
        const TCHAR* Title;
        const TCHAR* Weapon;
        const TCHAR* Armor;
        const TCHAR* Trait;
        FAesAttributes Mods;
    };

    TArray<FRouteData> BuildRoutes()
    {
        TArray<FRouteData> Routes;
        Routes.Add({ TEXT("Rota 1 - Pesado / Area"), TEXT("Espada de 2 maos e martelo"), TEXT("Pesada, bracelete e capacete"), TEXT("Bravura e determinado / impulsivo e arrogante"), { 5, 0, 2, -5, -2 } });
        Routes.Add({ TEXT("Rota 2 - Equilibrado / Defensivo"), TEXT("Espada de 1 mao e escudo"), TEXT("Mista, escudo de armas"), TEXT("Compromisso e transparencia / autoritarismo e arrogancia"), { 2, -5, 0, -1, 5 } });
        Routes.Add({ TEXT("Rota 3 - Alcance / Tatico"), TEXT("Lanca longa"), TEXT("Leve, manto de batalha"), TEXT("Prudencia e sabio / arrogante e desconsiderado"), { -5, 0, -1, 5, 1 } });
        Routes.Add({ TEXT("Rota 4 - Critico / Dual"), TEXT("Duas espadas leves"), TEXT("Malha e luvas de couro"), TEXT("Compromisso e disciplinado / arrogancia e perfeccionista"), { -5, 5, -2, 2, 0 } });
        Routes.Add({ TEXT("Rota 5 - Agilidade / Furtivo"), TEXT("Lanca leve"), TEXT("Malha e cinto de utilitarios"), TEXT("Destreza e versatil / hipocrita e arrogante"), { -5, 5, 0, 2, -2 } });
        return Routes;
    }

    float ChapterGoalFor(int32 Chapter)
    {
        return Chapter == 0 ? 880.0f : Chapter == 1 ? 980.0f : 1040.0f;
    }

    const TCHAR* AesSaveSlot()
    {
        return TEXT("AESDIVINUS_DATABASE");
    }
}

AAesPlayerController::AAesPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = false;
}

void AAesPlayerController::BeginPlay()
{
    Super::BeginPlay();
    ResetAttributesFromRoute();
    bHasSavedGame = UGameplayStatics::DoesSaveGameExist(AesSaveSlot(), 0);
    if (bHasSavedGame)
    {
        SaveStatusText = TEXT("Banco local encontrado. ENTER continua do checkpoint salvo.");
    }
}

void AAesPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
    ToastTime = FMath::Max(0.0f, ToastTime - DeltaTime);
    if (ToastTime <= 0.0f)
    {
        Toast.Empty();
    }

    if (Screen == EAesScreen::Loading)
    {
        LoadingProgress += DeltaTime * 58.0f;
        if (LoadingProgress >= 100.0f)
        {
            StartGame();
        }
    }

    if (Screen == EAesScreen::Gameplay && !bPaused && !bInDialogue)
    {
        UpdateGameplay(DeltaTime);
        AutoSaveTimer += DeltaTime;
        if (AutoSaveTimer >= 2.0f)
        {
            AutoSaveTimer = 0.0f;
            SaveGameDatabase();
        }
    }

    if (EndDelay > 0.0f)
    {
        EndDelay -= DeltaTime;
        if (EndDelay <= 0.0f)
        {
            FinishGame(true);
        }
    }
}

void AAesPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAxis(TEXT("MoveRight"), this, &AAesPlayerController::MoveRight);
    InputComponent->BindAction(TEXT("Confirm"), IE_Pressed, this, &AAesPlayerController::Confirm);
    InputComponent->BindAction(TEXT("Back"), IE_Pressed, this, &AAesPlayerController::Back);
    InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAesPlayerController::Jump);
    InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AAesPlayerController::Attack);
    InputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &AAesPlayerController::Dodge);
    InputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AAesPlayerController::Interact);
    InputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &AAesPlayerController::Pause);
    InputComponent->BindAction(TEXT("Choice1"), IE_Pressed, this, &AAesPlayerController::ChoiceOne);
    InputComponent->BindAction(TEXT("Choice2"), IE_Pressed, this, &AAesPlayerController::ChoiceTwo);
    InputComponent->BindAction(TEXT("Choice3"), IE_Pressed, this, &AAesPlayerController::ChoiceThree);
}

AAesCharacter* AAesPlayerController::GetAesPawn() const
{
    return Cast<AAesCharacter>(GetPawn());
}

void AAesPlayerController::MoveRight(float Value)
{
    MoveAxis = Value;
}

void AAesPlayerController::Confirm()
{
    if (Screen == EAesScreen::Login || Screen == EAesScreen::Register)
    {
        if (LoadGameDatabase(true))
        {
            AddToast(TEXT("Progresso carregado do banco local."));
        }
        else
        {
            Screen = EAesScreen::Creator;
            AddToast(TEXT("Conta local pronta. Crie seu William."));
        }
        return;
    }
    if (Screen == EAesScreen::Creator)
    {
        StartLoading();
        return;
    }
    if (Screen == EAesScreen::Ending)
    {
        if (!bVictory && LoadGameDatabase(true))
        {
            AddToast(TEXT("Voce voltou ao ultimo checkpoint salvo."));
        }
        else
        {
            Screen = EAesScreen::Login;
            AddToast(TEXT("Voltando ao inicio."));
        }
    }
}

void AAesPlayerController::Back()
{
    if (Screen == EAesScreen::Register)
    {
        Screen = EAesScreen::Login;
    }
    else if (Screen == EAesScreen::Creator)
    {
        Screen = EAesScreen::Login;
    }
    else if (Screen == EAesScreen::Gameplay)
    {
        bPaused = !bPaused;
    }
    else if (Screen == EAesScreen::Ending)
    {
        Screen = EAesScreen::Login;
        AddToast(TEXT("Inicio do jogo. O banco local permanece salvo."));
    }
}

void AAesPlayerController::Jump()
{
    if (Screen == EAesScreen::Gameplay && !bPaused && !bInDialogue)
    {
        if (AAesCharacter* AesPawn = GetAesPawn())
        {
            AesPawn->JumpOnBoard();
        }
    }
}

void AAesPlayerController::Attack()
{
    if (Screen != EAesScreen::Gameplay || bPaused || bInDialogue)
    {
        return;
    }

    AAesCharacter* AesPawn = GetAesPawn();
    if (!AesPawn || AesPawn->AttackCooldown > 0.0f)
    {
        return;
    }

    AesPawn->AttackCooldown = RouteIndex == 3 ? 0.24f : 0.36f;
    const float Reach = (RouteIndex == 2 || RouteIndex == 4) ? 104.0f : 74.0f;
    const float BaseDamage = 18.0f + Attributes.Forca * 1.5f + (HasCraftedAesBlade() ? 12.0f : 0.0f);
    bool bHit = false;

    for (FAesEnemyState& Enemy : Enemies)
    {
        if (!Enemy.bAlive)
        {
            continue;
        }

        const float DeltaX = Enemy.X - AesPawn->BoardPosition.X;
        const bool bInFront = FMath::Sign(DeltaX) == FMath::Sign(AesPawn->Facing) || FMath::Abs(DeltaX) < 20.0f;
        if (bInFront && FMath::Abs(DeltaX) < Reach)
        {
            const float AesBonus = Enemy.bCorrupted ? 1.8f : 1.0f;
            const bool bCritical = Personality == EArchetypePersonality::Perfeccionista && AesPawn->StatsComponent->CurrentCourage > 40.0f && FMath::FRand() < 0.25f;
            Enemy.Health -= BaseDamage * AesBonus * (bCritical ? 1.7f : 1.0f);
            Enemy.HitFlash = 0.16f;
            bHit = true;
            if (Enemy.Health <= 0.0f)
            {
                Enemy.bAlive = false;
                Ore += Enemy.bBoss ? 2 : 1;
                AesPawn->StatsComponent->CurrentCourage = FMath::Clamp(AesPawn->StatsComponent->CurrentCourage + 6.0f, 0.0f, 100.0f);
                AddToast(FString::Printf(TEXT("%s derrotado. Minerio +%d."), *Enemy.Type, Enemy.bBoss ? 2 : 1));
                SaveGameDatabase();
            }
        }
    }

    if (!bHit && AesPawn->StatsComponent)
    {
        AesPawn->StatsComponent->ReduceCourage(1.5f);
    }
}

void AAesPlayerController::Dodge()
{
    if (Screen == EAesScreen::Gameplay && !bPaused && !bInDialogue)
    {
        if (AAesCharacter* AesPawn = GetAesPawn())
        {
            AesPawn->DodgeOnBoard(Attributes.Agilidade);
        }
    }
}

void AAesPlayerController::Interact()
{
    if (Screen != EAesScreen::Gameplay || bPaused || bInDialogue)
    {
        return;
    }

    AAesCharacter* AesPawn = GetAesPawn();
    if (AesPawn && ChapterIndex >= 1 && FMath::Abs(AesPawn->BoardPosition.X - 250.0f) < 80.0f)
    {
        if (Ore >= 2 && !HasCraftedAesBlade())
        {
            Ore -= 2;
            CraftedItems.Add(TEXT("Lamina Aes"));
            ActivateBrand(EAesBrand::Thofestoe);
            AddToast(TEXT("Robert Smith forjou a Lamina Aes."));
            SaveGameDatabase();
        }
        else
        {
            AddToast(TEXT("Forja: junte 2 minerios Aes Divinus."));
        }
    }
}

void AAesPlayerController::Pause()
{
    if (Screen == EAesScreen::Gameplay)
    {
        bPaused = !bPaused;
    }
}

void AAesPlayerController::ChoiceOne()
{
    if (Screen == EAesScreen::Creator)
    {
        Personality = static_cast<EArchetypePersonality>((static_cast<int32>(Personality) + 1) % 4);
        ResetAttributesFromRoute();
    }
    else
    {
        ApplyChoice(0);
    }
}

void AAesPlayerController::ChoiceTwo()
{
    if (Screen == EAesScreen::Creator)
    {
        RouteIndex = (RouteIndex + 1) % 5;
        ResetAttributesFromRoute();
    }
    else
    {
        ApplyChoice(1);
    }
}

void AAesPlayerController::ChoiceThree()
{
    ApplyChoice(2);
}

void AAesPlayerController::ResetAttributesFromRoute()
{
    const TArray<FRouteData> Routes = BuildRoutes();
    Attributes = FAesAttributes();
    const FAesAttributes& Mods = Routes[FMath::Clamp(RouteIndex, 0, Routes.Num() - 1)].Mods;
    Attributes.Forca += Mods.Forca;
    Attributes.Agilidade += Mods.Agilidade;
    Attributes.Coragem += Mods.Coragem;
    Attributes.Percepcao += Mods.Percepcao;
    Attributes.Inspiracao += Mods.Inspiracao;

    if (Personality == EArchetypePersonality::Bravura) Attributes.Coragem += 3.0f;
    if (Personality == EArchetypePersonality::Prudente) Attributes.Percepcao += 3.0f;
    if (Personality == EArchetypePersonality::Perfeccionista) Attributes.Agilidade += 2.0f;
    if (Personality == EArchetypePersonality::Autocrata) Attributes.Inspiracao += 2.0f;

    if (AAesCharacter* AesPawn = GetAesPawn())
    {
        AesPawn->StatsComponent->BaseAttributes = Attributes;
        AesPawn->StatsComponent->Personality = Personality;
    }
}

void AAesPlayerController::StartLoading()
{
    ResetAttributesFromRoute();
    LoadingProgress = 0.0f;
    Screen = EAesScreen::Loading;
    if (!bLoadingFromDatabase)
    {
        SaveGameDatabase();
    }
}

void AAesPlayerController::StartGame()
{
    Screen = EAesScreen::Gameplay;
    bPaused = false;
    bVictory = false;
    EndDelay = 0.0f;
    if (AAesCharacter* AesPawn = GetAesPawn())
    {
        AesPawn->SetBoardPosition(80.0f, 550.0f);
        AesPawn->StatsComponent->CurrentHealth = 100.0f;
        AesPawn->StatsComponent->CurrentCourage = 100.0f;
        AesPawn->StatsComponent->Loyalty = 100.0f;
        AesPawn->StatsComponent->BaseAttributes = Attributes;
    }
    LoadChapter(0);
    SaveGameDatabase();
}

void AAesPlayerController::LoadChapter(int32 NewChapterIndex)
{
    ChapterIndex = NewChapterIndex;
    ChapterGoal = ChapterGoalFor(ChapterIndex);
    Enemies.Empty();
    Choices.Empty();

    if (AAesCharacter* AesPawn = GetAesPawn())
    {
        AesPawn->SetBoardPosition(80.0f, 550.0f);
    }

    if (ChapterIndex == 0)
    {
        ChapterName = TEXT("1.1 - Entrada na Floresta Wood");
        DialogueSpeaker = TEXT("Ethan Armand");
        DialogueText = TEXT("A floresta esta quieta demais para uma marcha de trezentos homens.");
        Choices = { TEXT("1 Escudos"), TEXT("2 Donovan a frente") };
        Enemies.Add({ TEXT("Homines Corrupti"), 420.0f, 52.0f, 52.0f, 52.0f, 10.0f, true, false, true, 0.0f });
        Enemies.Add({ TEXT("Stipulation"), 690.0f, 72.0f, 72.0f, 46.0f, 13.0f, true, false, true, 0.0f });
    }
    else if (ChapterIndex == 1)
    {
        ChapterName = TEXT("1.2 - Clareira da Emboscada");
        DialogueSpeaker = TEXT("Donovan Michael");
        DialogueText = TEXT("O machado veio das arvores. O cavalo do principe caiu!");
        Choices = { TEXT("1 Reagrupar"), TEXT("2 Perseguir") };
        Enemies.Add({ TEXT("Duque Bezalel Michel"), 390.0f, 86.0f, 86.0f, 58.0f, 16.0f, true, false, true, 0.0f });
        Enemies.Add({ TEXT("Canis Ferox"), 760.0f, 132.0f, 132.0f, 84.0f, 20.0f, true, true, true, 0.0f });
    }
    else
    {
        ChapterName = TEXT("1.3 - Massacre do Exercito");
        DialogueSpeaker = TEXT("Duque Elric");
        DialogueText = TEXT("William, de pe! Se cairmos aqui, Gradon nao tera aviso.");
        Choices = { TEXT("1 Gloregni"), TEXT("2 Iusdicta"), TEXT("3 Thofestoe") };
        Enemies.Add({ TEXT("Servi Belli Larvae"), 430.0f, 96.0f, 96.0f, 38.0f, 18.0f, true, false, true, 0.0f });
        Enemies.Add({ TEXT("Bellum Bellatoris"), 840.0f, 230.0f, 230.0f, 34.0f, 28.0f, true, true, true, 0.0f });
    }

    bInDialogue = true;
    SaveGameDatabase();
}

void AAesPlayerController::ApplyChoice(int32 ChoiceIndex)
{
    if (!bInDialogue || !Choices.IsValidIndex(ChoiceIndex))
    {
        return;
    }

    AAesCharacter* AesPawn = GetAesPawn();
    if (!AesPawn || !AesPawn->StatsComponent)
    {
        return;
    }

    if (ChapterIndex == 0)
    {
        if (ChoiceIndex == 0)
        {
            SetOrder(EAesSquadOrder::Shield);
            AesPawn->StatsComponent->Loyalty = FMath::Clamp(AesPawn->StatsComponent->Loyalty + 8.0f, 0.0f, 100.0f);
            AesPawn->StatsComponent->CurrentCourage = FMath::Clamp(AesPawn->StatsComponent->CurrentCourage + 4.0f, 0.0f, 100.0f);
        }
        else
        {
            SetOrder(EAesSquadOrder::Archers);
            Attributes.Percepcao += 2.0f;
            AesPawn->StatsComponent->ReduceCourage(4.0f);
        }
    }
    else if (ChapterIndex == 1)
    {
        if (ChoiceIndex == 0)
        {
            SetOrder(EAesSquadOrder::Shield);
            AesPawn->StatsComponent->Loyalty = FMath::Clamp(AesPawn->StatsComponent->Loyalty + 10.0f, 0.0f, 100.0f);
            AesPawn->StatsComponent->CurrentCourage = FMath::Clamp(AesPawn->StatsComponent->CurrentCourage + 8.0f, 0.0f, 100.0f);
        }
        else
        {
            SetOrder(EAesSquadOrder::Charge);
            Attributes.Agilidade += 2.0f;
            AesPawn->StatsComponent->Loyalty = FMath::Clamp(AesPawn->StatsComponent->Loyalty - 6.0f, 0.0f, 100.0f);
        }
    }
    else
    {
        if (ChoiceIndex == 0) ActivateBrand(EAesBrand::Gloregni);
        if (ChoiceIndex == 1) ActivateBrand(EAesBrand::Iusdicta);
        if (ChoiceIndex == 2)
        {
            Ore += 2;
            ActivateBrand(EAesBrand::Thofestoe);
        }
    }

    bInDialogue = false;
    SaveGameDatabase();
}

void AAesPlayerController::SetOrder(EAesSquadOrder NewOrder)
{
    SquadOrder = NewOrder;
    AddToast(SquadOrder == EAesSquadOrder::Shield ? TEXT("Parede de Escudos!") : SquadOrder == EAesSquadOrder::Archers ? TEXT("Arqueiros em cobertura!") : TEXT("Investida!"));
    SaveGameDatabase();
}

void AAesPlayerController::ActivateBrand(EAesBrand Brand)
{
    if (!HasBrand(Brand))
    {
        ActiveBrands.Add(Brand);
    }
    if (AAesCharacter* AesPawn = GetAesPawn())
    {
        AesPawn->StatsComponent->ActivateBrand(Brand);
        Attributes = AesPawn->StatsComponent->BaseAttributes;
    }
    SaveGameDatabase();
}

void AAesPlayerController::UpdateGameplay(float DeltaTime)
{
    AAesCharacter* AesPawn = GetAesPawn();
    if (!AesPawn || !AesPawn->StatsComponent)
    {
        return;
    }

    const float Speed = 220.0f + Attributes.Agilidade * 4.0f;
    AesPawn->MoveOnBoard(MoveAxis, Speed, DeltaTime);
    AesPawn->BoardPosition.X = FMath::Clamp(AesPawn->BoardPosition.X, 30.0f, ChapterGoal + 180.0f);

    UpdateEnemies(DeltaTime);

    bool bAnyAlive = false;
    for (const FAesEnemyState& Enemy : Enemies)
    {
        bAnyAlive |= Enemy.bAlive;
    }

    if (!bAnyAlive && AesPawn->BoardPosition.X >= ChapterGoal)
    {
        if (ChapterIndex < 2)
        {
            LoadChapter(ChapterIndex + 1);
        }
        else if (EndDelay <= 0.0f)
        {
            EndDelay = 0.4f;
        }
    }

    if (AesPawn->StatsComponent->CurrentHealth <= 0.0f)
    {
        SaveStatusText = TEXT("Fim do jogo. Seu checkpoint anterior foi mantido no banco local.");
        FinishGame(false);
    }
}

void AAesPlayerController::UpdateEnemies(float DeltaTime)
{
    AAesCharacter* AesPawn = GetAesPawn();
    if (!AesPawn || !AesPawn->StatsComponent)
    {
        return;
    }

    const float WeatherDamage = ChapterIndex == 2 ? 1.25f : 1.0f;
    const float OrderSpeed = SquadOrder == EAesSquadOrder::Shield ? 0.78f : SquadOrder == EAesSquadOrder::Charge ? 1.14f : 1.0f;

    for (FAesEnemyState& Enemy : Enemies)
    {
        if (!Enemy.bAlive)
        {
            continue;
        }
        const float Direction = FMath::Sign(AesPawn->BoardPosition.X - Enemy.X);
        Enemy.X += Direction * Enemy.Speed * OrderSpeed * DeltaTime;
        Enemy.HitFlash = FMath::Max(0.0f, Enemy.HitFlash - DeltaTime);

        if (FMath::Abs(AesPawn->BoardPosition.X - Enemy.X) < 52.0f && AesPawn->InvulnerableTime <= 0.0f)
        {
            AesPawn->StatsComponent->CurrentHealth = FMath::Clamp(AesPawn->StatsComponent->CurrentHealth - Enemy.Damage * WeatherDamage * DeltaTime, 0.0f, 100.0f);
            AesPawn->StatsComponent->ReduceCourage((Enemy.bBoss ? 10.0f : 5.0f) * DeltaTime);
            const float LoyaltyLoss = Personality == EArchetypePersonality::Autocrata ? 2.4f : 1.2f;
            AesPawn->StatsComponent->Loyalty = FMath::Clamp(AesPawn->StatsComponent->Loyalty - LoyaltyLoss * DeltaTime, 0.0f, 100.0f);
        }

        if (SquadOrder == EAesSquadOrder::Archers && FMath::FRand() < DeltaTime * 0.65f)
        {
            Enemy.Health -= 11.0f + Attributes.Inspiracao * 0.45f;
            Enemy.HitFlash = 0.12f;
            if (Enemy.Health <= 0.0f)
            {
                Enemy.bAlive = false;
                Ore += Enemy.bBoss ? 2 : 1;
                SaveGameDatabase();
            }
        }
    }
}

void AAesPlayerController::FinishGame(bool bWon)
{
    if (bWon)
    {
        SaveGameDatabase();
        SaveStatusText = TEXT("Vitoria salva no banco local.");
    }
    bVictory = bWon;
    Screen = EAesScreen::Ending;
    bPaused = false;
    bInDialogue = false;
}

void AAesPlayerController::SaveGameDatabase()
{
    if (Screen == EAesScreen::Ending && !bVictory)
    {
        return;
    }

    UAesSaveGame* SaveData = Cast<UAesSaveGame>(UGameplayStatics::CreateSaveGameObject(UAesSaveGame::StaticClass()));
    if (!SaveData)
    {
        SaveStatusText = TEXT("Falha ao criar banco local.");
        return;
    }

    SaveData->RouteIndex = RouteIndex;
    SaveData->ChapterIndex = ChapterIndex;
    SaveData->ChapterGoal = ChapterGoal;
    SaveData->ChapterName = ChapterName;
    SaveData->Personality = Personality;
    SaveData->Attributes = Attributes;
    SaveData->ActiveBrands = ActiveBrands;
    SaveData->CraftedItems = CraftedItems;
    SaveData->SquadOrder = SquadOrder;
    SaveData->Ore = Ore;
    SaveData->bHasValidProgress = true;

    if (AAesCharacter* AesPawn = GetAesPawn())
    {
        SaveData->PlayerPosition = AesPawn->BoardPosition;
        if (AesPawn->StatsComponent)
        {
            SaveData->Health = FMath::Max(AesPawn->StatsComponent->CurrentHealth, 35.0f);
            SaveData->Courage = FMath::Max(AesPawn->StatsComponent->CurrentCourage, 35.0f);
            SaveData->Loyalty = AesPawn->StatsComponent->Loyalty;
        }
    }

    bHasSavedGame = UGameplayStatics::SaveGameToSlot(SaveData, AesSaveSlot(), 0);
    SaveStatusText = bHasSavedGame ? TEXT("Jogo salvo no banco local.") : TEXT("Falha ao salvar banco local.");
}

bool AAesPlayerController::LoadGameDatabase(bool bResumeGameplay)
{
    if (!UGameplayStatics::DoesSaveGameExist(AesSaveSlot(), 0))
    {
        bHasSavedGame = false;
        return false;
    }

    UAesSaveGame* SaveData = Cast<UAesSaveGame>(UGameplayStatics::LoadGameFromSlot(AesSaveSlot(), 0));
    if (!SaveData || !SaveData->bHasValidProgress)
    {
        bHasSavedGame = false;
        return false;
    }

    RouteIndex = SaveData->RouteIndex;
    ChapterIndex = SaveData->ChapterIndex;
    ChapterGoal = SaveData->ChapterGoal;
    ChapterName = SaveData->ChapterName;
    Personality = SaveData->Personality;
    Attributes = SaveData->Attributes;
    ActiveBrands = SaveData->ActiveBrands;
    CraftedItems = SaveData->CraftedItems;
    SquadOrder = SaveData->SquadOrder;
    Ore = SaveData->Ore;
    ClearRuntimeCombatState();
    bLoadingFromDatabase = true;
    LoadChapter(ChapterIndex);
    bLoadingFromDatabase = false;
    bInDialogue = false;

    if (AAesCharacter* AesPawn = GetAesPawn())
    {
        AesPawn->SetBoardPosition(FMath::Max(SaveData->PlayerPosition.X, 80.0f), SaveData->PlayerPosition.Y);
        if (AesPawn->StatsComponent)
        {
            AesPawn->StatsComponent->BaseAttributes = Attributes;
            AesPawn->StatsComponent->Personality = Personality;
            AesPawn->StatsComponent->CurrentHealth = FMath::Clamp(SaveData->Health, 35.0f, 100.0f);
            AesPawn->StatsComponent->CurrentCourage = FMath::Clamp(SaveData->Courage, 35.0f, 100.0f);
            AesPawn->StatsComponent->Loyalty = FMath::Clamp(SaveData->Loyalty, 0.0f, 100.0f);
        }
    }

    bHasSavedGame = true;
    SaveStatusText = TEXT("Progresso carregado do banco local.");
    if (bResumeGameplay)
    {
        Screen = EAesScreen::Gameplay;
        bPaused = false;
        bVictory = false;
    }
    return true;
}

void AAesPlayerController::ClearRuntimeCombatState()
{
    EndDelay = 0.0f;
    bPaused = false;
    bInDialogue = false;
    bVictory = false;
    LoadingProgress = 0.0f;
}

bool AAesPlayerController::HasBrand(EAesBrand Brand) const
{
    return ActiveBrands.Contains(Brand);
}

bool AAesPlayerController::HasCraftedAesBlade() const
{
    return CraftedItems.Contains(TEXT("Lamina Aes"));
}

void AAesPlayerController::AddToast(const FString& Message)
{
    Toast = Message;
    ToastTime = 2.4f;
}

FString AAesPlayerController::GetRouteTitle() const
{
    const TArray<FRouteData> Routes = BuildRoutes();
    return Routes[FMath::Clamp(RouteIndex, 0, Routes.Num() - 1)].Title;
}

FString AAesPlayerController::GetRouteWeapon() const
{
    const TArray<FRouteData> Routes = BuildRoutes();
    return Routes[FMath::Clamp(RouteIndex, 0, Routes.Num() - 1)].Weapon;
}

FString AAesPlayerController::GetRouteArmor() const
{
    const TArray<FRouteData> Routes = BuildRoutes();
    return Routes[FMath::Clamp(RouteIndex, 0, Routes.Num() - 1)].Armor;
}

FString AAesPlayerController::GetWeatherName() const
{
    if (ChapterIndex == 0) return TEXT("Sol filtrado");
    if (ChapterIndex == 1) return TEXT("Nevoa escura");
    return TEXT("Chuva de sangue");
}

float AAesPlayerController::GetHealthPercent() const
{
    if (const AAesCharacter* AesPawn = GetAesPawn())
    {
        return AesPawn->StatsComponent->CurrentHealth / 100.0f;
    }
    return 1.0f;
}

float AAesPlayerController::GetCouragePercent() const
{
    if (const AAesCharacter* AesPawn = GetAesPawn())
    {
        return AesPawn->StatsComponent->CurrentCourage / 100.0f;
    }
    return 1.0f;
}

float AAesPlayerController::GetLoyalty() const
{
    if (const AAesCharacter* AesPawn = GetAesPawn())
    {
        return AesPawn->StatsComponent->Loyalty;
    }
    return 100.0f;
}

