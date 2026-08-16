#include "AesHUD.h"
#include "AesPlayerController.h"
#include "AesCharacter.h"
#include "AesStatsComponent.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"

AAesPlayerController* AAesHUD::GetAesController() const
{
    return Cast<AAesPlayerController>(PlayerOwner);
}

void AAesHUD::DrawHUD()
{
    Super::DrawHUD();
    AAesPlayerController* PC = GetAesController();
    if (!PC || !Canvas)
    {
        return;
    }

    if (PC->Screen == EAesScreen::Login || PC->Screen == EAesScreen::Register) DrawLogin(PC);
    if (PC->Screen == EAesScreen::Creator) DrawCreator(PC);
    if (PC->Screen == EAesScreen::Loading) DrawLoading(PC);
    if (PC->Screen == EAesScreen::Gameplay) DrawGameplay(PC);
    if (PC->Screen == EAesScreen::Ending) DrawEnding(PC);

    if (!PC->Toast.IsEmpty())
    {
        DrawPanel(Canvas->ClipX * 0.5f - 260.0f, 22.0f, 520.0f, 44.0f, FLinearColor(0.02f, 0.02f, 0.02f, 0.82f));
        DrawCenteredText(PC->Toast, 34.0f, 1.0f, FLinearColor(0.93f, 0.88f, 0.55f, 1.0f));
    }
}

void AAesHUD::DrawLogin(AAesPlayerController* PC)
{
    const float W = Canvas->ClipX;
    const float H = Canvas->ClipY;
    DrawInterfaceBackdrop();
    DrawOrnateFrame(24.0f, 18.0f, W - 48.0f, H - 36.0f, TEXT("AESDIVINUS: INTERFACES"));

    const bool bRegister = PC->Screen == EAesScreen::Register;

    const float FlowW = FMath::Min(W - 160.0f, 780.0f);
    const float FlowX = (W - FlowW) * 0.5f;
    const float FlowY = 76.0f;
    const TCHAR* Steps[] = { TEXT("LOGIN"), TEXT("CADASTRO"), TEXT("PERSONAGEM"), TEXT("HISTORIA"), TEXT("BATALHA") };
    for (int32 I = 0; I < 5; ++I)
    {
        const bool bActive = (I == 0 && !bRegister) || (I == 1 && bRegister);
        const float StepX = FlowX + I * (FlowW / 5.0f);
        DrawPanel(StepX + 8.0f, FlowY, FlowW / 5.0f - 16.0f, 22.0f, bActive ? FLinearColor(0.0f, 0.42f, 0.28f, 0.95f) : FLinearColor(0.08f, 0.07f, 0.055f, 0.90f));
        DrawText(Steps[I], bActive ? FLinearColor::White : FLinearColor(0.68f, 0.62f, 0.50f, 1.0f), StepX + 20.0f, FlowY + 5.0f, nullptr, 0.58f);
    }

    if (!bRegister)
    {
        const float LoginW = FMath::Clamp(W * 0.54f, 520.0f, 760.0f);
        const float LoginH = FMath::Clamp(H * 0.56f, 360.0f, 500.0f);
        const float LoginX = (W - LoginW) * 0.5f;
        const float LoginY = H * 0.18f;

        DrawOrnateFrame(LoginX, LoginY, LoginW, LoginH, TEXT("INICIALIZACAO & LOGIN"));
        DrawForestArtPanel(LoginX + 22.0f, LoginY + 38.0f, LoginW - 44.0f, LoginH - 68.0f, true);
        DrawIconSeal(LoginX + 54.0f, LoginY + 72.0f, 0.55f, FLinearColor(0.74f, 0.76f, 0.70f, 1.0f));
        DrawIconSeal(LoginX + 58.0f, LoginY + LoginH - 68.0f, 0.62f, FLinearColor(0.55f, 0.54f, 0.50f, 1.0f));
        DrawPanel(LoginX + LoginW * 0.31f, LoginY + LoginH * 0.21f, LoginW * 0.38f, 156.0f, FLinearColor(0.01f, 0.012f, 0.012f, 0.42f));

        float LoginTextW = 0.0f;
        float LoginTextH = 0.0f;
        GetTextSize(TEXT("AESDIVINUS"), LoginTextW, LoginTextH, nullptr, 1.55f);
        DrawText(TEXT("AESDIVINUS"), FLinearColor(0.91f, 0.82f, 0.62f, 1.0f), LoginX + (LoginW - LoginTextW) * 0.5f, LoginY + LoginH * 0.26f, nullptr, 1.55f);
        GetTextSize(TEXT("Pressione ENTER para comecar"), LoginTextW, LoginTextH, nullptr, 0.82f);
        DrawText(TEXT("Pressione ENTER para comecar"), FLinearColor(0.92f, 0.90f, 0.84f, 1.0f), LoginX + (LoginW - LoginTextW) * 0.5f, LoginY + LoginH * 0.40f, nullptr, 0.82f);
        DrawAesButton(LoginX + LoginW * 0.5f - 86.0f, LoginY + LoginH * 0.52f, 172.0f, 34.0f, TEXT("ENVIAR"), true);
        DrawAesButton(LoginX + LoginW * 0.5f - 86.0f, LoginY + LoginH * 0.62f, 172.0f, 34.0f, TEXT("CRIAR CONTA"), false);

        if (PC->bHasSavedGame)
        {
            DrawText(TEXT("SALVO: ENTER continua do banco local"), FLinearColor(0.0f, 0.92f, 0.52f, 1.0f), LoginX + 38.0f, LoginY + LoginH - 36.0f, nullptr, 0.76f);
        }
    }
    else
    {
        const float RegisterW = FMath::Clamp(W * 0.58f, 650.0f, 900.0f);
        const float RegisterH = FMath::Clamp(H * 0.62f, 430.0f, 560.0f);
        const float RegisterX = (W - RegisterW) * 0.5f;
        const float RegisterY = H * 0.16f;

        DrawOrnateFrame(RegisterX, RegisterY, RegisterW, RegisterH, TEXT("CADASTRO DE USUARIO"));
        DrawLibraryArtPanel(RegisterX + 22.0f, RegisterY + 38.0f, RegisterW - 44.0f, RegisterH - 72.0f);
        DrawPanel(RegisterX + RegisterW * 0.25f, RegisterY + 76.0f, RegisterW * 0.50f, RegisterH - 154.0f, FLinearColor(0.02f, 0.026f, 0.026f, 0.86f));
        DrawInputField(RegisterX + RegisterW * 0.32f, RegisterY + 116.0f, RegisterW * 0.36f, TEXT("Nome de Usuario"), TEXT("William"), false);
        DrawInputField(RegisterX + RegisterW * 0.32f, RegisterY + 178.0f, RegisterW * 0.36f, TEXT("E-mail"), TEXT("william@gradon.local"), false);
        DrawInputField(RegisterX + RegisterW * 0.32f, RegisterY + 240.0f, RegisterW * 0.36f, TEXT("Senha"), TEXT("aesdivinus"), true);
        DrawInputField(RegisterX + RegisterW * 0.32f, RegisterY + 302.0f, RegisterW * 0.36f, TEXT("Confirmacao de Senha"), TEXT("aesdivinus"), true);
        DrawAesButton(RegisterX + RegisterW * 0.33f - 150.0f, RegisterY + RegisterH - 64.0f, 150.0f, 32.0f, TEXT("FINALIZAR"), true);
        DrawAesButton(RegisterX + RegisterW * 0.67f, RegisterY + RegisterH - 64.0f, 150.0f, 32.0f, TEXT("VOLTAR"), false);
    }

    DrawPanel(W * 0.5f - 260.0f, H - 36.0f, 520.0f, 20.0f, FLinearColor(0.03f, 0.03f, 0.026f, 0.92f));
    DrawCenteredText(TEXT("ENTER / ESPACO - entrar | ESC - voltar"), H - 54.0f, 0.85f, FLinearColor(0.78f, 0.78f, 0.72f, 1.0f));
}

void AAesHUD::DrawCreator(AAesPlayerController* PC)
{
    const float W = Canvas->ClipX;
    const float H = Canvas->ClipY;
    if (PC)
    {
    DrawInterfaceBackdrop();
    DrawOrnateFrame(24.0f, 18.0f, W - 48.0f, H - 36.0f, TEXT("CRIACAO DE PERSONAGEM"));

    const float PreviewX = W * 0.32f;
    const float PreviewY = H * 0.18f;
    const float PreviewW = W * 0.36f;
    const float PreviewH = H * 0.55f;
    const float CenterX = PreviewX + PreviewW * 0.50f;
    const float BaseY = PreviewY + PreviewH - 78.0f;
    DrawOrnateFrame(PreviewX, PreviewY, PreviewW, PreviewH, TEXT("PRINCIPE WILLIAM DE AUGUSTO"));
    DrawPanel(PreviewX + 22.0f, PreviewY + 46.0f, PreviewW - 44.0f, PreviewH - 80.0f, FLinearColor(0.08f, 0.09f, 0.09f, 0.74f));
    DrawSegment(PreviewX + 86.0f, PreviewY + 76.0f, PreviewX + PreviewW - 80.0f, PreviewY + PreviewH - 120.0f, FLinearColor(0.92f, 0.78f, 0.42f, 0.20f), 20.0f);
    DrawPanel(CenterX - 130.0f, BaseY + 34.0f, 260.0f, 18.0f, FLinearColor(0.12f, 0.10f, 0.08f, 1.0f));
    DrawPanel(CenterX - 110.0f, BaseY + 18.0f, 220.0f, 24.0f, FLinearColor(0.33f, 0.29f, 0.21f, 1.0f));
    DrawSegment(CenterX - 80.0f, BaseY + 20.0f, CenterX + 80.0f, BaseY + 20.0f, FLinearColor(0.0f, 0.75f, 0.47f, 0.65f), 2.5f);
    DrawWilliam(CenterX, BaseY + 16.0f, 1.0f, true, 1.90f);
    DrawText(TEXT("360"), FLinearColor(0.83f, 0.72f, 0.50f, 1.0f), CenterX - 16.0f, BaseY + 56.0f, nullptr, 0.78f);

    DrawOrnateFrame(W * 0.07f, H * 0.24f, W * 0.19f, H * 0.42f, TEXT("CORPO"));
    for (int32 R = 0; R < 3; ++R)
    {
        for (int32 C = 0; C < 3; ++C)
        {
            const float IX = W * 0.095f + C * 48.0f;
            const float IY = H * 0.31f + R * 52.0f;
            DrawPanel(IX, IY, 34.0f, 34.0f, FLinearColor(0.07f, 0.08f, 0.07f, 0.90f));
            DrawIconSeal(IX + 17.0f, IY + 17.0f, 0.16f, (R == 1 && C == 1) ? FLinearColor(0.0f, 0.85f, 0.50f, 1.0f) : FLinearColor(0.70f, 0.56f, 0.28f, 1.0f));
        }
    }

    const float X = W * 0.72f;
    DrawOrnateFrame(X, H * 0.24f, W * 0.21f, H * 0.42f, TEXT("ARQUETIPO"));
    DrawText(FString::Printf(TEXT("1 %s"), *StaticEnum<EArchetypePersonality>()->GetNameStringByValue(static_cast<int64>(PC->Personality))), FLinearColor(0.88f, 0.84f, 0.72f, 1.0f), X + 24.0f, H * 0.32f, nullptr, 0.88f);
    DrawText(FString::Printf(TEXT("2 %s"), *PC->GetRouteTitle()), FLinearColor(0.88f, 0.84f, 0.72f, 1.0f), X + 24.0f, H * 0.37f, nullptr, 0.88f);
    DrawText(FString::Printf(TEXT("Arma: %s"), *PC->GetRouteWeapon()), FLinearColor(0.72f, 0.72f, 0.68f, 1.0f), X + 24.0f, H * 0.45f, nullptr, 0.75f);
    DrawText(FString::Printf(TEXT("Armadura: %s"), *PC->GetRouteArmor()), FLinearColor(0.72f, 0.72f, 0.68f, 1.0f), X + 24.0f, H * 0.49f, nullptr, 0.75f);
    DrawText(FString::Printf(TEXT("FOR %.0f  AGI %.0f"), PC->Attributes.Forca, PC->Attributes.Agilidade), FLinearColor::White, X + 24.0f, H * 0.56f, nullptr, 0.78f);
    DrawText(FString::Printf(TEXT("COR %.0f  PER %.0f  INS %.0f"), PC->Attributes.Coragem, PC->Attributes.Percepcao, PC->Attributes.Inspiracao), FLinearColor::White, X + 24.0f, H * 0.60f, nullptr, 0.78f);

    DrawOrnateFrame(W * 0.06f, H * 0.74f, W * 0.88f, H * 0.18f, TEXT("PERSONAGENS DO PROLOGO"));
    const float LineY = H * 0.89f;
    DrawCompanionFigure(TEXT("Ethan Armand"), W * 0.12f, LineY, 0.48f);
    DrawCompanionFigure(TEXT("Donovan Michael"), W * 0.23f, LineY, 0.50f);
    DrawCompanionFigure(TEXT("Santa Guerreira Isabeau Moreau"), W * 0.34f, LineY, 0.47f);
    DrawCompanionFigure(TEXT("Principe William de Augusto"), W * 0.47f, LineY, 0.56f);
    DrawCompanionFigure(TEXT("Princesa Hilda de Augusto"), W * 0.60f, LineY, 0.50f);
    DrawCompanionFigure(TEXT("Bellum Bellatoris"), W * 0.71f, LineY, 0.54f);
    DrawCompanionFigure(TEXT("Roger Redhead"), W * 0.81f, LineY, 0.48f);
    DrawCompanionFigure(TEXT("Albert Roberts"), W * 0.90f, LineY, 0.50f);
    DrawAesButton(W * 0.72f, H * 0.69f, 220.0f, 36.0f, TEXT("ENTER - INICIAR PROLOGO"), true);
    return;
    }
    DrawPanel(0, 0, W, H, FLinearColor(0.04f, 0.06f, 0.08f, 1.0f));
    DrawPanel(0, 0, W * 0.58f, H, FLinearColor(0.04f, 0.10f, 0.09f, 1.0f));
    DrawPanel(W * 0.58f, 0, W * 0.42f, H, FLinearColor(0.07f, 0.07f, 0.08f, 0.96f));

    const float CX = W * 0.29f;
    const float BaseY = H * 0.72f;
    for (int32 I = 0; I < 7; ++I)
    {
        DrawPanel(CX - 190.0f + I * 64.0f, BaseY + 55.0f + (I % 2) * 4.0f, 58.0f, 10.0f, FLinearColor(0.18f, 0.18f, 0.18f, 1.0f));
    }
    DrawPanel(CX - 150.0f, BaseY + 26.0f, 300.0f, 40.0f, FLinearColor(0.42f, 0.42f, 0.42f, 1.0f));
    DrawPanel(CX - 120.0f, BaseY + 18.0f, 240.0f, 18.0f, FLinearColor(0.28f, 0.28f, 0.29f, 1.0f));
    DrawWilliam(CX, BaseY + 18.0f, 1.0f, true, 1.85f);
    const float LineY = H - 52.0f;
    DrawCompanionFigure(TEXT("Hilda"), CX - 250.0f, LineY, 0.64f);
    DrawCompanionFigure(TEXT("Elric"), CX - 170.0f, LineY, 0.66f);
    DrawCompanionFigure(TEXT("Ethan"), CX + 170.0f, LineY, 0.60f);
    DrawCompanionFigure(TEXT("Donovan"), CX + 250.0f, LineY, 0.62f);

    const float X = W * 0.61f;
    DrawText(TEXT("Criacao de Personagem"), FLinearColor(0.93f, 0.88f, 0.55f, 1.0f), X, 60.0f, nullptr, 1.35f);
    DrawText(TEXT("Principe William de Augusto"), FLinearColor::White, X, 108.0f, nullptr, 1.0f);
    DrawText(FString::Printf(TEXT("1 Arquétipo: %s"), *StaticEnum<EArchetypePersonality>()->GetNameStringByValue(static_cast<int64>(PC->Personality))), FLinearColor(0.8f, 0.8f, 0.82f, 1.0f), X, 154.0f, nullptr, 1.0f);
    DrawText(FString::Printf(TEXT("2 %s"), *PC->GetRouteTitle()), FLinearColor(0.8f, 0.8f, 0.82f, 1.0f), X, 188.0f, nullptr, 1.0f);
    DrawText(FString::Printf(TEXT("Arma: %s"), *PC->GetRouteWeapon()), FLinearColor(0.7f, 0.7f, 0.72f, 1.0f), X, 228.0f, nullptr, 0.9f);
    DrawText(FString::Printf(TEXT("Armadura: %s"), *PC->GetRouteArmor()), FLinearColor(0.7f, 0.7f, 0.72f, 1.0f), X, 256.0f, nullptr, 0.9f);

    DrawText(TEXT("Atributos"), FLinearColor(0.83f, 0.69f, 0.22f, 1.0f), X, 314.0f, nullptr, 1.05f);
    DrawText(FString::Printf(TEXT("Forca %.0f  Agilidade %.0f"), PC->Attributes.Forca, PC->Attributes.Agilidade), FLinearColor::White, X, 350.0f, nullptr, 0.95f);
    DrawText(FString::Printf(TEXT("Coragem %.0f  Percepcao %.0f"), PC->Attributes.Coragem, PC->Attributes.Percepcao), FLinearColor::White, X, 382.0f, nullptr, 0.95f);
    DrawText(FString::Printf(TEXT("Inspiracao %.0f"), PC->Attributes.Inspiracao), FLinearColor::White, X, 414.0f, nullptr, 0.95f);
    DrawPanel(X, H - 98.0f, 420.0f, 48.0f, FLinearColor(0.14f, 0.38f, 0.28f, 1.0f));
    DrawText(TEXT("ENTER - INICIAR PROLOGO"), FLinearColor::White, X + 84.0f, H - 84.0f, nullptr, 1.0f);
}

void AAesHUD::DrawLoading(AAesPlayerController* PC)
{
    const float W = Canvas->ClipX;
    const float H = Canvas->ClipY;
    DrawInterfaceBackdrop();
    DrawOrnateFrame(32.0f, 30.0f, W - 64.0f, H - 60.0f, TEXT("CARREGANDO HISTORIA"));
    DrawOrnateFrame(W * 0.12f, H * 0.20f, W * 0.76f, H * 0.52f, TEXT("CRONICAS DE GRADON"));
    DrawPanel(W * 0.15f, H * 0.28f, W * 0.70f, H * 0.31f, FLinearColor(0.55f, 0.43f, 0.24f, 0.36f));
    DrawPanel(W * 0.17f, H * 0.31f, W * 0.24f, H * 0.22f, FLinearColor(0.13f, 0.10f, 0.07f, 0.70f));
    DrawSegment(W * 0.22f, H * 0.53f, W * 0.29f, H * 0.36f, FLinearColor(0.72f, 0.62f, 0.42f, 0.85f), 9.0f);
    DrawSegment(W * 0.29f, H * 0.36f, W * 0.35f, H * 0.53f, FLinearColor(0.72f, 0.62f, 0.42f, 0.85f), 9.0f);
    DrawAesOreCrystal(W * 0.50f, H * 0.49f, 1.45f);
    DrawAesStone(TEXT("ingot"), W * 0.62f, H * 0.50f, 1.0f);
    DrawAesStone(TEXT("geode"), W * 0.70f, H * 0.50f, 0.86f);
    DrawItemCard(TEXT("ESPADA DIVINA"), TEXT("sword"), W * 0.18f, H * 0.74f, 150.0f, 120.0f);
    DrawItemCard(TEXT("MARTELO AES"), TEXT("hammer"), W * 0.33f, H * 0.74f, 150.0f, 120.0f);
    DrawItemCard(TEXT("LANCA LONGA"), TEXT("lance"), W * 0.48f, H * 0.74f, 150.0f, 120.0f);
    DrawItemCard(TEXT("CINZEIS"), TEXT("chisel"), W * 0.63f, H * 0.74f, 150.0f, 120.0f);
    DrawText(TEXT("...das profundezas do minerio Aes Divinus"), FLinearColor(0.84f, 0.78f, 0.62f, 1.0f), W * 0.52f, H * 0.36f, nullptr, 0.86f);
    DrawText(TEXT("os juramentos antigos respondem ao herdeiro."), FLinearColor(0.84f, 0.78f, 0.62f, 1.0f), W * 0.52f, H * 0.41f, nullptr, 0.86f);
    DrawBar(W * 0.22f, H * 0.64f, W * 0.56f, 20.0f, PC->LoadingProgress / 100.0f, TEXT(""), FLinearColor(0.08f, 0.07f, 0.05f, 1.0f), FLinearColor(0.83f, 0.69f, 0.22f, 1.0f));
    DrawSegment(W * 0.22f, H * 0.64f, W * 0.22f + W * 0.56f * FMath::Clamp(PC->LoadingProgress / 100.0f, 0.0f, 1.0f), H * 0.64f, FLinearColor(0.20f, 0.95f, 0.58f, 0.75f), 2.0f);
}

void AAesHUD::DrawGameplay(AAesPlayerController* PC)
{
    const float W = Canvas->ClipX;
    const float H = Canvas->ClipY;
    AAesCharacter* Pawn = PC->GetAesPawn();
    const float CameraX = Pawn ? FMath::Clamp(Pawn->BoardPosition.X - W * 0.38f, 0.0f, PC->ChapterGoal - W * 0.62f) : 0.0f;

    DrawForestScene(PC, CameraX);

    if (PC->ChapterIndex >= 1)
    {
        const float ForgeX = 250.0f - CameraX;
        DrawForge(ForgeX, H - 80.0f);
    }

    if (Pawn)
    {
        const float PX = Pawn->BoardPosition.X - CameraX;
        const float PY = H - (640.0f - Pawn->BoardPosition.Y);
        DrawWilliam(PX, PY, Pawn->Facing, PC->CraftedItems.Num() > 0, 1.12f);
    }

    for (const FAesEnemyState& Enemy : PC->Enemies)
    {
        if (!Enemy.bAlive) continue;
        const float EX = Enemy.X - CameraX;
        const float EY = H - 80.0f;
        DrawEnemyFigure(Enemy, EX, EY);
    }

    DrawOrnateFrame(14.0f, 14.0f, 388.0f, 112.0f, TEXT("WILLIAM"));
    DrawBar(36.0f, 48.0f, 300.0f, 14.0f, PC->GetHealthPercent(), TEXT("HP"), FLinearColor(0.20f, 0.0f, 0.0f, 1.0f), FLinearColor(0.75f, 0.04f, 0.12f, 1.0f));
    DrawBar(36.0f, 70.0f, 300.0f, 14.0f, PC->GetCouragePercent(), TEXT("COR"), FLinearColor(0.0f, 0.0f, 0.14f, 1.0f), FLinearColor(0.12f, 0.55f, 0.95f, 1.0f));
    DrawIconSeal(368.0f, 72.0f, 0.58f, FLinearColor(0.0f, 0.82f, 0.48f, 1.0f));
    DrawText(FString::Printf(TEXT("Lealdade %.0f%% | Minerio %d | %s"), PC->GetLoyalty(), PC->Ore, *PC->GetWeatherName()), FLinearColor::White, 34.0f, 94.0f, nullptr, 0.74f);
    DrawOrnateFrame(14.0f, 136.0f, 360.0f, 38.0f, TEXT(""));
    DrawText(PC->ChapterName, FLinearColor(0.93f, 0.88f, 0.55f, 1.0f), 28.0f, 146.0f, nullptr, 0.78f);

    DrawOrnateFrame(W - 178.0f, 16.0f, 154.0f, 152.0f, TEXT("ESQUADRA"));
    DrawIconSeal(W - 142.0f, 63.0f, 0.36f, PC->SquadOrder == EAesSquadOrder::Shield ? FLinearColor(0.0f, 0.92f, 0.52f, 1.0f) : FLinearColor(0.60f, 0.60f, 0.55f, 1.0f));
    DrawIconSeal(W - 142.0f, 101.0f, 0.36f, PC->SquadOrder == EAesSquadOrder::Archers ? FLinearColor(0.0f, 0.92f, 0.52f, 1.0f) : FLinearColor(0.60f, 0.60f, 0.55f, 1.0f));
    DrawIconSeal(W - 142.0f, 139.0f, 0.36f, PC->SquadOrder == EAesSquadOrder::Charge ? FLinearColor(0.0f, 0.92f, 0.52f, 1.0f) : FLinearColor(0.60f, 0.60f, 0.55f, 1.0f));
    DrawText(TEXT("1 Escudos"), FLinearColor::White, W - 120.0f, 54.0f, nullptr, 0.68f);
    DrawText(TEXT("2 Arqueiros"), FLinearColor::White, W - 120.0f, 92.0f, nullptr, 0.68f);
    DrawText(TEXT("3 Investida"), FLinearColor::White, W - 120.0f, 130.0f, nullptr, 0.68f);

    DrawOrnateFrame(W * 0.5f - 338.0f, H - 74.0f, 676.0f, 52.0f, TEXT(""));
    DrawText(TEXT("A/D mover | Espaco pular | J atacar | K esquivar | E forja | 1/2/3 ordens | P pausa"), FLinearColor(0.86f, 0.86f, 0.80f, 1.0f), W * 0.5f - 310.0f, H - 54.0f, nullptr, 0.75f);
    for (int32 I = 0; I < 6; ++I)
    {
        const float SlotX = W * 0.5f + 176.0f + I * 26.0f;
        DrawPanel(SlotX, H - 58.0f, 20.0f, 20.0f, FLinearColor(0.07f, 0.07f, 0.06f, 1.0f));
        if (I == 0) DrawAesTool(TEXT("sword"), SlotX + 10.0f, H - 48.0f, 0.12f);
        else if (I == 1) DrawAesTool(TEXT("hammer"), SlotX + 10.0f, H - 48.0f, 0.11f);
        else if (I == 2) DrawAesTool(TEXT("dagger"), SlotX + 10.0f, H - 48.0f, 0.12f);
        else DrawIconSeal(SlotX + 10.0f, H - 48.0f, 0.12f, I < PC->ActiveBrands.Num() ? FLinearColor(0.0f, 0.86f, 0.48f, 1.0f) : FLinearColor(0.40f, 0.35f, 0.25f, 1.0f));
    }

    if (PC->bInDialogue)
    {
        DrawOrnateFrame(W * 0.5f - 390.0f, H - 232.0f, 780.0f, 160.0f, TEXT("DIALOGO"));
        DrawText(PC->DialogueSpeaker, FLinearColor(0.83f, 0.69f, 0.22f, 1.0f), W * 0.5f - 362.0f, H - 190.0f, nullptr, 1.0f);
        DrawText(PC->DialogueText, FLinearColor::White, W * 0.5f - 362.0f, H - 158.0f, nullptr, 0.9f);
        for (int32 I = 0; I < PC->Choices.Num(); ++I)
        {
            DrawText(PC->Choices[I], FLinearColor(0.85f, 0.85f, 0.85f, 1.0f), W * 0.5f - 350.0f + I * 230.0f, H - 108.0f, nullptr, 0.9f);
        }
    }

    if (PC->bPaused)
    {
        DrawOrnateFrame(W - 390.0f, 22.0f, 360.0f, H - 44.0f, TEXT("PAUSA"));
        DrawText(TEXT("Pausa"), FLinearColor(0.83f, 0.69f, 0.22f, 1.0f), W - 340.0f, 50.0f, nullptr, 1.3f);
        DrawText(PC->GetRouteTitle(), FLinearColor::White, W - 340.0f, 104.0f, nullptr, 0.9f);
        DrawText(FString::Printf(TEXT("Marcas: %d/5"), PC->ActiveBrands.Num()), FLinearColor::White, W - 340.0f, 140.0f, nullptr, 0.9f);
        DrawText(FString::Printf(TEXT("Itens: %s"), PC->CraftedItems.Num() ? TEXT("Lamina Aes") : TEXT("nenhum")), FLinearColor::White, W - 340.0f, 176.0f, nullptr, 0.9f);
        DrawText(TEXT("P ou ESC para voltar"), FLinearColor(0.75f, 0.75f, 0.75f, 1.0f), W - 340.0f, H - 64.0f, nullptr, 0.85f);
    }
}

void AAesHUD::DrawForestScene(AAesPlayerController* PC, float CameraX)
{
    const float W = Canvas->ClipX;
    const float H = Canvas->ClipY;
    const FLinearColor SkyTop = PC->ChapterIndex == 2 ? FLinearColor(0.13f, 0.03f, 0.03f, 1.0f) : PC->ChapterIndex == 1 ? FLinearColor(0.05f, 0.08f, 0.12f, 1.0f) : FLinearColor(0.12f, 0.22f, 0.16f, 1.0f);
    const FLinearColor SkyMid = PC->ChapterIndex == 2 ? FLinearColor(0.23f, 0.07f, 0.06f, 1.0f) : PC->ChapterIndex == 1 ? FLinearColor(0.12f, 0.18f, 0.22f, 1.0f) : FLinearColor(0.25f, 0.43f, 0.33f, 1.0f);
    DrawPanel(0, 0, W, H, SkyTop);
    DrawPanel(0, H * 0.16f, W, H * 0.32f, SkyMid);
    DrawPanel(0, H * 0.46f, W, H * 0.23f, FLinearColor(0.15f, 0.31f, 0.25f, 0.58f));

    for (int32 I = 0; I < 7; ++I)
    {
        const float X = FMath::Fmod(I * 250.0f - CameraX * 0.035f, W + 260.0f) - 130.0f;
        DrawSegment(X, 40.0f, X + 150.0f, H - 110.0f, FLinearColor(0.93f, 0.82f, 0.46f, PC->ChapterIndex == 0 ? 0.12f : 0.05f), 18.0f);
    }

    for (int32 Layer = 0; Layer < 3; ++Layer)
    {
        const float Parallax = 0.055f + Layer * 0.055f;
        const float TreeGap = 135.0f - Layer * 12.0f;
        const FLinearColor Trunk = Layer == 0 ? FLinearColor(0.04f, 0.09f, 0.07f, 0.92f) : Layer == 1 ? FLinearColor(0.06f, 0.13f, 0.09f, 0.92f) : FLinearColor(0.09f, 0.19f, 0.13f, 0.96f);
        const FLinearColor Leaf = Layer == 0 ? FLinearColor(0.02f, 0.10f, 0.07f, 0.85f) : Layer == 1 ? FLinearColor(0.05f, 0.18f, 0.10f, 0.90f) : FLinearColor(0.10f, 0.30f, 0.17f, 0.95f);
        const float Offset = FMath::Fmod(CameraX * Parallax, TreeGap);

        for (int32 I = -1; I < 16; ++I)
        {
            const float Seed = static_cast<float>((I + 31) * (Layer + 3));
            const float X = I * TreeGap - Offset + FMath::Fmod(Seed * 17.0f, 44.0f);
            const float TrunkW = 18.0f + Layer * 7.0f + FMath::Fmod(Seed, 4.0f) * 3.0f;
            const float TopY = 104.0f + FMath::Fmod(Seed * 9.0f, 84.0f) - Layer * 28.0f;
            DrawPanel(X, TopY, TrunkW, H - 86.0f - TopY, Trunk);
            DrawPanel(X + TrunkW * 0.55f, TopY + 30.0f, 6.0f, H - 122.0f - TopY, FLinearColor(0.12f, 0.24f, 0.16f, 0.35f));
            DrawSegment(X + TrunkW * 0.4f, TopY + 92.0f, X - 42.0f, TopY + 130.0f, Trunk, 7.0f);
            DrawSegment(X + TrunkW * 0.6f, TopY + 122.0f, X + 58.0f, TopY + 92.0f, Trunk, 6.0f);
            for (int32 C = 0; C < 4; ++C)
            {
                DrawPanel(X - 48.0f + C * 25.0f, TopY - 30.0f + (C % 2) * 14.0f, 76.0f, 42.0f, Leaf);
            }
        }
    }

    for (int32 I = -1; I < 9; ++I)
    {
        const float X = FMath::Fmod(I * 210.0f - CameraX * 0.24f, W + 240.0f) - 120.0f;
        const float Y = H - 210.0f + (I % 3) * 8.0f;
        DrawPanel(X, Y, 70.0f, 28.0f, FLinearColor(0.08f, 0.19f, 0.12f, 0.90f));
        DrawPanel(X + 32.0f, Y - 18.0f, 58.0f, 36.0f, FLinearColor(0.10f, 0.25f, 0.15f, 0.90f));
        DrawPanel(X + 72.0f, Y + 4.0f, 64.0f, 25.0f, FLinearColor(0.07f, 0.17f, 0.10f, 0.86f));
        DrawSegment(X + 18.0f, Y + 30.0f, X + 4.0f, Y + 52.0f, FLinearColor(0.12f, 0.08f, 0.05f, 0.72f), 5.0f);
    }

    const float GroundY = H - 80.0f;
    DrawPanel(0, GroundY - 24.0f, W, 24.0f, FLinearColor(0.13f, 0.20f, 0.12f, 1.0f));
    DrawPanel(0, GroundY, W, 80.0f, PC->ChapterIndex == 2 ? FLinearColor(0.18f, 0.10f, 0.08f, 1.0f) : FLinearColor(0.28f, 0.23f, 0.17f, 1.0f));
    for (int32 I = 0; I < 30; ++I)
    {
        const float X = FMath::Fmod(I * 81.0f - CameraX * 0.55f, W + 90.0f) - 40.0f;
        DrawPanel(X, GroundY - 12.0f + (I % 4) * 3.0f, 42.0f, 5.0f, FLinearColor(0.10f, 0.12f, 0.08f, 0.55f));
        DrawSegment(X + 8.0f, GroundY - 2.0f, X + 46.0f, GroundY - 16.0f, FLinearColor(0.16f, 0.10f, 0.06f, 0.75f), 3.0f);
    }

    if (PC->ChapterIndex == 1)
    {
        DrawPanel(0, H * 0.34f, W, H * 0.34f, FLinearColor(0.68f, 0.78f, 0.82f, 0.10f));
    }
    else if (PC->ChapterIndex == 2)
    {
        for (int32 I = 0; I < 42; ++I)
        {
            const float X = FMath::Fmod(I * 47.0f + GetWorld()->GetTimeSeconds() * 32.0f, W);
            const float Y = FMath::Fmod(I * 89.0f + GetWorld()->GetTimeSeconds() * 110.0f, H);
            DrawSegment(X, Y, X - 3.0f, Y + 16.0f, FLinearColor(0.55f, 0.0f, 0.0f, 0.42f), 2.0f);
        }
    }
}

void AAesHUD::DrawWilliam(float X, float FeetY, float Facing, bool bAesBlade, float Scale)
{
    const float F = Facing >= 0.0f ? 1.0f : -1.0f;
#define AES_R(RX, RY, RW, RH, COLOR) DrawPanel(X + (RX) * Scale, FeetY + (RY) * Scale, (RW) * Scale, (RH) * Scale, (COLOR))
#define AES_L(X1, Y1, X2, Y2, COLOR, THICK) DrawSegment(X + (X1) * Scale, FeetY + (Y1) * Scale, X + (X2) * Scale, FeetY + (Y2) * Scale, (COLOR), (THICK) * Scale)

    const float T = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    const float Walk = FMath::Sin(T * 7.0f) * 2.0f;
    const FLinearColor Skin(0.96f, 0.90f, 0.83f, 1.0f);
    const FLinearColor Hair(0.90f, 0.76f, 0.50f, 1.0f);
    const FLinearColor Steel(0.29f, 0.31f, 0.35f, 1.0f);
    const FLinearColor SteelLight(0.55f, 0.59f, 0.65f, 1.0f);
    const FLinearColor SteelDark(0.11f, 0.12f, 0.14f, 1.0f);
    const FLinearColor Aes(0.18f, 0.55f, 0.34f, 1.0f);
    const FLinearColor AesGlow(0.35f, 0.95f, 0.62f, 0.78f);
    const FLinearColor Gold(0.83f, 0.69f, 0.22f, 1.0f);
    const FLinearColor ValoisBlue(0.0f, 0.14f, 0.40f, 1.0f);
    const FLinearColor Outline(0.025f, 0.025f, 0.030f, 1.0f);

    AES_R(-28.0f, -92.0f, 13.0f, 82.0f, FLinearColor(0.0f, 0.05f, 0.17f, 0.78f));
    AES_R(-21.0f, -18.0f + Walk, 15.0f, 18.0f, Outline);
    AES_R(6.0f, -18.0f - Walk, 15.0f, 18.0f, Outline);
    AES_R(-17.0f, -56.0f + Walk, 12.0f, 42.0f, SteelDark);
    AES_R(5.0f, -56.0f - Walk, 12.0f, 42.0f, SteelDark);
    AES_R(-14.0f, -54.0f + Walk, 8.0f, 31.0f, SteelLight);
    AES_R(6.0f, -54.0f - Walk, 8.0f, 31.0f, SteelLight);
    AES_R(-23.0f, -48.0f, 46.0f, 9.0f, FLinearColor(0.13f, 0.07f, 0.04f, 1.0f));
    AES_R(-20.0f, -43.0f, 40.0f, 6.0f, Gold);

    AES_R(-25.0f, -95.0f, 50.0f, 43.0f, Outline);
    AES_R(-21.0f, -91.0f, 42.0f, 39.0f, Steel);
    AES_R(-16.0f, -87.0f, 32.0f, 10.0f, SteelLight);
    AES_R(-19.0f, -77.0f, 38.0f, 26.0f, ValoisBlue);
    AES_R(-4.0f, -94.0f, 8.0f, 50.0f, Aes);
    AES_R(-2.0f, -89.0f, 4.0f, 40.0f, AesGlow);
    AES_L(-14.0f, -74.0f, 0.0f, -55.0f, Gold, 2.0f);
    AES_L(14.0f, -74.0f, 0.0f, -55.0f, Gold, 2.0f);
    AES_R(-31.0f, -99.0f, 62.0f, 7.0f, Gold);
    AES_R(-32.0f, -99.0f, 12.0f, 12.0f, Aes);
    AES_R(20.0f, -99.0f, 12.0f, 12.0f, Aes);
    AES_R(-36.0f, -88.0f, 14.0f, 35.0f, SteelLight);
    AES_R(22.0f, -88.0f, 14.0f, 35.0f, SteelLight);
    AES_R(-39.0f, -76.0f, 10.0f, 12.0f, Gold);
    AES_R(29.0f, -76.0f, 10.0f, 12.0f, Gold);
    AES_R(-42.0f, -58.0f, 13.0f, 27.0f, SteelDark);
    AES_R(29.0f, -58.0f, 13.0f, 27.0f, SteelDark);

    AES_R(-16.0f, -128.0f, 32.0f, 34.0f, Outline);
    AES_R(-14.0f, -126.0f, 28.0f, 32.0f, Skin);
    AES_R(-17.0f, -133.0f, 34.0f, 10.0f, Hair);
    AES_R(-21.0f, -126.0f, 9.0f, 23.0f, Hair);
    AES_R(12.0f, -126.0f, 8.0f, 20.0f, Hair);
    AES_R(-13.0f, -117.0f, 5.0f, 4.0f, FLinearColor(0.10f, 0.21f, 0.36f, 1.0f));
    AES_R(8.0f, -117.0f, 5.0f, 4.0f, Gold);
    AES_R(-4.0f, -111.0f, 5.0f, 10.0f, FLinearColor(0.78f, 0.66f, 0.56f, 1.0f));
    AES_R(-8.0f, -99.0f, 16.0f, 2.0f, FLinearColor(0.34f, 0.18f, 0.14f, 1.0f));
    AES_R(-12.0f, -94.0f, 24.0f, 7.0f, SteelLight);

    AES_L(F * 21.0f, -78.0f, F * 55.0f, -108.0f, Outline, 7.0f);
    AES_L(F * 21.0f, -78.0f, F * 55.0f, -108.0f, SteelDark, 5.0f);
    AES_L(F * 35.0f, -103.0f, F * 83.0f, -146.0f, bAesBlade ? Aes : Gold, 5.0f);
    AES_L(F * 40.0f, -98.0f, F * 88.0f, -141.0f, bAesBlade ? FLinearColor(0.68f, 0.95f, 0.78f, 0.90f) : FLinearColor(0.95f, 0.87f, 0.56f, 0.90f), 1.5f);
    AES_R(F * 28.0f - 4.0f, -106.0f, 8.0f, 6.0f, Gold);
    AES_R(F * -58.0f - 8.0f, -91.0f, 32.0f, 42.0f, FLinearColor(0.02f, 0.28f, 0.18f, 0.92f));
    AES_R(F * -54.0f - 8.0f, -86.0f, 24.0f, 31.0f, Aes);
    AES_R(F * -48.0f - 8.0f, -80.0f, 12.0f, 20.0f, Gold);
#undef AES_R
#undef AES_L
}

void AAesHUD::DrawCompanionFigure(const FString& RoleName, float X, float FeetY, float Scale)
{
#define AES_CR(RX, RY, RW, RH, COLOR) DrawPanel(X + (RX) * Scale, FeetY + (RY) * Scale, (RW) * Scale, (RH) * Scale, (COLOR))
#define AES_CL(X1, Y1, X2, Y2, COLOR, THICK) DrawSegment(X + (X1) * Scale, FeetY + (Y1) * Scale, X + (X2) * Scale, FeetY + (Y2) * Scale, (COLOR), (THICK) * Scale)
    if (RoleName.Contains(TEXT("William")))
    {
        DrawWilliam(X, FeetY, 1.0f, true, Scale);
        DrawText(RoleName, FLinearColor(0.93f, 0.88f, 0.55f, 1.0f), X - 56.0f * Scale, FeetY + 7.0f, nullptr, 0.50f);
        return;
    }

    const bool bEthan = RoleName.Contains(TEXT("Ethan"));
    const bool bDonovan = RoleName.Contains(TEXT("Donovan"));
    const bool bIsabeau = RoleName.Contains(TEXT("Isabeau")) || RoleName.Contains(TEXT("Santa"));
    const bool bHilda = RoleName.Contains(TEXT("Hilda"));
    const bool bElric = RoleName.Contains(TEXT("Elric")) || RoleName.Contains(TEXT("Bellum Bellatoris"));
    const bool bRoger = RoleName.Contains(TEXT("Roger"));
    const bool bAlbert = RoleName.Contains(TEXT("Albert"));

    const FLinearColor Gold(0.83f, 0.69f, 0.22f, 1.0f);
    FLinearColor Steel(0.45f, 0.47f, 0.51f, 1.0f);
    const FLinearColor Dark(0.05f, 0.05f, 0.06f, 1.0f);
    FLinearColor Skin(0.86f, 0.68f, 0.55f, 1.0f);
    FLinearColor Cloth(0.12f, 0.26f, 0.16f, 1.0f);
    FLinearColor Hair(0.35f, 0.18f, 0.10f, 1.0f);
    FLinearColor Accent(0.18f, 0.55f, 0.34f, 1.0f);
    if (bEthan) { Cloth = FLinearColor(0.18f, 0.20f, 0.22f, 1.0f); Hair = FLinearColor(0.20f, 0.10f, 0.05f, 1.0f); Steel = FLinearColor(0.62f, 0.66f, 0.70f, 1.0f); Accent = FLinearColor(0.75f, 0.62f, 0.42f, 1.0f); }
    if (bDonovan) { Cloth = FLinearColor(0.035f, 0.045f, 0.050f, 1.0f); Hair = FLinearColor(0.04f, 0.035f, 0.030f, 1.0f); Skin = FLinearColor(0.50f, 0.33f, 0.24f, 1.0f); Accent = FLinearColor(0.25f, 0.28f, 0.30f, 1.0f); }
    if (bIsabeau) { Cloth = FLinearColor(0.73f, 0.74f, 0.66f, 1.0f); Hair = FLinearColor(0.94f, 0.94f, 0.86f, 1.0f); Skin = FLinearColor(0.88f, 0.72f, 0.58f, 1.0f); Accent = FLinearColor(0.86f, 0.78f, 0.56f, 1.0f); }
    if (bHilda) { Cloth = FLinearColor(0.30f, 0.16f, 0.42f, 1.0f); Hair = FLinearColor(0.92f, 0.82f, 0.60f, 1.0f); Accent = FLinearColor(0.0f, 0.72f, 0.46f, 1.0f); }
    if (bElric) { Cloth = FLinearColor(0.0f, 0.14f, 0.40f, 1.0f); Hair = FLinearColor(0.70f, 0.70f, 0.68f, 1.0f); Skin = FLinearColor(0.72f, 0.58f, 0.48f, 1.0f); }
    if (bRoger) { Cloth = FLinearColor(0.13f, 0.30f, 0.20f, 1.0f); Hair = FLinearColor(0.86f, 0.66f, 0.30f, 1.0f); Accent = FLinearColor(0.48f, 0.58f, 0.50f, 1.0f); }
    if (bAlbert) { Cloth = FLinearColor(0.43f, 0.18f, 0.05f, 1.0f); Hair = FLinearColor(0.78f, 0.18f, 0.06f, 1.0f); Steel = FLinearColor(0.62f, 0.34f, 0.13f, 1.0f); Accent = FLinearColor(0.95f, 0.56f, 0.20f, 1.0f); }

    AES_CR(-13.0f, -16.0f, 11.0f, 16.0f, Dark);
    AES_CR(4.0f, -16.0f, 11.0f, 16.0f, Dark);
    AES_CR(-12.0f, -53.0f, 10.0f, 38.0f, Dark);
    AES_CR(3.0f, -53.0f, 10.0f, 38.0f, Dark);
    if (bElric)
    {
        AES_CR(-29.0f, -94.0f, 58.0f, 74.0f, FLinearColor(0.11f, 0.12f, 0.13f, 1.0f));
        AES_CR(-35.0f, -103.0f, 70.0f, 18.0f, FLinearColor(0.48f, 0.50f, 0.48f, 1.0f));
        AES_CR(-42.0f, -93.0f, 18.0f, 58.0f, FLinearColor(0.18f, 0.20f, 0.22f, 1.0f));
    }
    if (bIsabeau)
    {
        AES_CR(-25.0f, -96.0f, 50.0f, 82.0f, FLinearColor(0.80f, 0.78f, 0.68f, 1.0f));
        AES_CL(-18.0f, -132.0f, 0.0f, -150.0f, Gold, 2.0f);
        AES_CL(18.0f, -132.0f, 0.0f, -150.0f, Gold, 2.0f);
    }
    AES_CR(-19.0f, -86.0f, 38.0f, 38.0f, Cloth);
    AES_CR(-21.0f, -92.0f, 42.0f, 12.0f, Steel);
    AES_CR(-3.0f, -89.0f, 6.0f, 40.0f, Accent);
    AES_CR(-27.0f, -80.0f, 10.0f, 32.0f, Steel);
    AES_CR(17.0f, -80.0f, 10.0f, 32.0f, Steel);
    AES_CR(-13.0f, -122.0f, 26.0f, 31.0f, Skin);
    AES_CR(-16.0f, -128.0f, 32.0f, 10.0f, Hair);
    AES_CR(-17.0f, -118.0f, 7.0f, 18.0f, Hair);
    AES_CR(10.0f, -118.0f, 7.0f, 18.0f, Hair);
    if (bDonovan)
    {
        AES_CR(-20.0f, -126.0f, 40.0f, 16.0f, Hair);
        AES_CR(-12.0f, -101.0f, 24.0f, 12.0f, Hair);
        AES_CR(-31.0f, -88.0f, 16.0f, 45.0f, FLinearColor(0.02f, 0.025f, 0.030f, 1.0f));
        AES_CR(15.0f, -88.0f, 16.0f, 45.0f, FLinearColor(0.02f, 0.025f, 0.030f, 1.0f));
    }
    AES_CR(-8.0f, -111.0f, 4.0f, 4.0f, Dark);
    AES_CR(5.0f, -111.0f, 4.0f, 4.0f, Dark);
    if (bElric)
    {
        AES_CR(-17.0f, -127.0f, 34.0f, 34.0f, FLinearColor(0.68f, 0.68f, 0.66f, 0.72f));
        AES_CR(-26.0f, -84.0f, 52.0f, 8.0f, Gold);
        AES_CL(31.0f, -82.0f, 31.0f, -138.0f, Steel, 5.0f);
        AES_CL(31.0f, -138.0f, 18.0f, -120.0f, Steel, 3.0f);
        AES_CL(31.0f, -138.0f, 44.0f, -120.0f, Steel, 3.0f);
    }
    else
    {
        AES_CL(23.0f, -70.0f, 61.0f, -24.0f, Steel, 4.0f);
        AES_CL(28.0f, -65.0f, 66.0f, -19.0f, FLinearColor(0.80f, 0.88f, 0.92f, 1.0f), 1.5f);
    }
    if (bHilda)
    {
        AES_CR(-42.0f, -78.0f, 28.0f, 34.0f, FLinearColor(0.16f, 0.14f, 0.15f, 1.0f));
        AES_CR(-38.0f, -74.0f, 20.0f, 26.0f, FLinearColor(0.18f, 0.36f, 0.25f, 1.0f));
        AES_CR(-13.0f, -88.0f, 26.0f, 18.0f, FLinearColor(0.72f, 0.62f, 0.56f, 1.0f));
    }
    if (bEthan)
    {
        AES_CR(-33.0f, -89.0f, 18.0f, 40.0f, Steel);
        AES_CR(15.0f, -89.0f, 18.0f, 40.0f, Steel);
        AES_CR(-18.0f, -86.0f, 36.0f, 9.0f, FLinearColor(0.83f, 0.72f, 0.52f, 1.0f));
    }
    if (bRoger)
    {
        AES_CR(-31.0f, -89.0f, 62.0f, 62.0f, FLinearColor(0.04f, 0.12f, 0.10f, 0.82f));
        AES_CR(-18.0f, -96.0f, 36.0f, 12.0f, FLinearColor(0.10f, 0.22f, 0.15f, 1.0f));
    }
    if (bAlbert)
    {
        AES_CR(-32.0f, -94.0f, 64.0f, 18.0f, Steel);
        AES_CR(-26.0f, -74.0f, 52.0f, 34.0f, FLinearColor(0.36f, 0.15f, 0.04f, 1.0f));
    }
    DrawText(RoleName, FLinearColor(0.93f, 0.88f, 0.55f, 1.0f), X - 43.0f * Scale, FeetY + 6.0f, nullptr, 0.48f);
#undef AES_CR
#undef AES_CL
}

void AAesHUD::DrawEnemyFigure(const FAesEnemyState& Enemy, float X, float FeetY)
{
    float S = Enemy.bBoss ? 1.42f : 1.0f;
    if (Enemy.Type.Contains(TEXT("Canis"))) { S = 1.0f; }
    if (Enemy.Type.Contains(TEXT("Servi"))) { S = 1.22f; }
    const FLinearColor Flesh = Enemy.HitFlash > 0.0f ? FLinearColor(1.0f, 0.20f, 0.20f, 1.0f) : Enemy.bBoss ? FLinearColor(0.05f, 0.01f, 0.01f, 1.0f) : FLinearColor(0.70f, 0.13f, 0.13f, 1.0f);
    const FLinearColor Vein(0.18f, 0.00f, 0.18f, 1.0f);
    const FLinearColor Magma(1.0f, 0.20f, 0.0f, 1.0f);
#define AES_ER(RX, RY, RW, RH, COLOR) DrawPanel(X + (RX) * S, FeetY + (RY) * S, (RW) * S, (RH) * S, (COLOR))
#define AES_EL(X1, Y1, X2, Y2, COLOR, THICK) DrawSegment(X + (X1) * S, FeetY + (Y1) * S, X + (X2) * S, FeetY + (Y2) * S, (COLOR), (THICK) * S)

    if (Enemy.Type.Contains(TEXT("Canis")))
    {
        const FLinearColor Hide = Enemy.HitFlash > 0.0f ? FLinearColor(0.95f, 0.20f, 0.16f, 1.0f) : FLinearColor(0.30f, 0.10f, 0.08f, 1.0f);
        AES_ER(-58.0f, -50.0f, 90.0f, 42.0f, Hide);
        AES_ER(18.0f, -72.0f, 38.0f, 32.0f, Hide);
        AES_ER(28.0f, -66.0f, 8.0f, 7.0f, Magma);
        AES_ER(44.0f, -66.0f, 8.0f, 7.0f, Magma);
        AES_ER(40.0f, -55.0f, 24.0f, 5.0f, FLinearColor(0.88f, 0.82f, 0.70f, 1.0f));
        AES_ER(-46.0f, -12.0f, 13.0f, 14.0f, FLinearColor(0.07f, 0.04f, 0.035f, 1.0f));
        AES_ER(-12.0f, -12.0f, 13.0f, 14.0f, FLinearColor(0.07f, 0.04f, 0.035f, 1.0f));
        AES_ER(24.0f, -12.0f, 13.0f, 14.0f, FLinearColor(0.07f, 0.04f, 0.035f, 1.0f));
        AES_ER(49.0f, -12.0f, 13.0f, 14.0f, FLinearColor(0.07f, 0.04f, 0.035f, 1.0f));
        AES_EL(-52.0f, -45.0f, -84.0f, -74.0f, Hide, 10.0f);
        AES_EL(8.0f, -78.0f, 24.0f, -98.0f, Hide, 5.0f);
        AES_EL(46.0f, -78.0f, 60.0f, -98.0f, Hide, 5.0f);
    }
    else if (Enemy.Type.Contains(TEXT("Stipulation")))
    {
        const FLinearColor Pale = Enemy.HitFlash > 0.0f ? FLinearColor(1.0f, 0.32f, 0.32f, 1.0f) : FLinearColor(0.72f, 0.72f, 0.70f, 1.0f);
        AES_ER(-22.0f, -86.0f, 44.0f, 84.0f, FLinearColor(0.04f, 0.05f, 0.055f, 1.0f));
        AES_ER(-18.0f, -121.0f, 36.0f, 34.0f, Pale);
        AES_ER(-14.0f, -132.0f, 28.0f, 14.0f, FLinearColor(0.02f, 0.025f, 0.030f, 1.0f));
        AES_ER(-11.0f, -109.0f, 6.0f, 5.0f, FLinearColor(0.02f, 0.02f, 0.02f, 1.0f));
        AES_ER(5.0f, -109.0f, 6.0f, 5.0f, FLinearColor(0.02f, 0.02f, 0.02f, 1.0f));
        AES_ER(-44.0f, -92.0f, 26.0f, 54.0f, FLinearColor(0.02f, 0.08f, 0.10f, 0.90f));
        AES_ER(18.0f, -92.0f, 26.0f, 54.0f, FLinearColor(0.02f, 0.08f, 0.10f, 0.90f));
        AES_EL(-10.0f, -80.0f, -42.0f, -24.0f, Pale, 8.0f);
        AES_EL(10.0f, -80.0f, 42.0f, -24.0f, Pale, 8.0f);
    }
    else if (Enemy.Type.Contains(TEXT("Bezalel")))
    {
        AES_ER(-21.0f, -86.0f, 42.0f, 84.0f, FLinearColor(0.36f, 0.03f, 0.035f, 1.0f));
        AES_ER(-17.0f, -125.0f, 34.0f, 38.0f, FLinearColor(0.72f, 0.62f, 0.55f, 1.0f));
        AES_ER(-18.0f, -132.0f, 36.0f, 12.0f, FLinearColor(0.03f, 0.03f, 0.035f, 1.0f));
        AES_ER(-10.0f, -110.0f, 5.0f, 4.0f, FLinearColor(0.04f, 0.0f, 0.0f, 1.0f));
        AES_ER(5.0f, -110.0f, 5.0f, 4.0f, FLinearColor(0.04f, 0.0f, 0.0f, 1.0f));
        AES_ER(-22.0f, -91.0f, 44.0f, 8.0f, FLinearColor(0.15f, 0.12f, 0.09f, 1.0f));
        AES_EL(-20.0f, -74.0f, -54.0f, -23.0f, FLinearColor(0.08f, 0.08f, 0.08f, 1.0f), 8.0f);
        AES_EL(20.0f, -74.0f, 54.0f, -23.0f, FLinearColor(0.08f, 0.08f, 0.08f, 1.0f), 8.0f);
        AES_ER(-20.0f, -17.0f, 15.0f, 18.0f, FLinearColor(0.05f, 0.04f, 0.04f, 1.0f));
        AES_ER(5.0f, -17.0f, 15.0f, 18.0f, FLinearColor(0.05f, 0.04f, 0.04f, 1.0f));
    }
    else if (Enemy.Type.Contains(TEXT("Servi")))
    {
        const FLinearColor Rot = Enemy.HitFlash > 0.0f ? FLinearColor(1.0f, 0.25f, 0.22f, 1.0f) : FLinearColor(0.42f, 0.50f, 0.38f, 1.0f);
        AES_ER(-42.0f, -100.0f, 84.0f, 98.0f, Rot);
        AES_ER(-18.0f, -160.0f, 36.0f, 48.0f, FLinearColor(0.75f, 0.70f, 0.58f, 1.0f));
        AES_ER(-13.0f, -146.0f, 7.0f, 8.0f, FLinearColor(0.02f, 0.01f, 0.01f, 1.0f));
        AES_ER(6.0f, -146.0f, 7.0f, 8.0f, FLinearColor(0.02f, 0.01f, 0.01f, 1.0f));
        AES_EL(-18.0f, -158.0f, -48.0f, -190.0f, FLinearColor(0.48f, 0.40f, 0.30f, 1.0f), 5.0f);
        AES_EL(18.0f, -158.0f, 48.0f, -190.0f, FLinearColor(0.48f, 0.40f, 0.30f, 1.0f), 5.0f);
        AES_ER(-18.0f, -66.0f, 36.0f, 42.0f, FLinearColor(0.09f, 0.0f, 0.0f, 1.0f));
        AES_EL(-45.0f, -70.0f, -75.0f, -20.0f, Rot, 13.0f);
        AES_EL(45.0f, -70.0f, 74.0f, -20.0f, Rot, 13.0f);
        AES_EL(48.0f, -58.0f, 72.0f, -88.0f, FLinearColor(0.50f, 0.50f, 0.46f, 1.0f), 6.0f);
    }
    else
    {
        const bool bBellum = Enemy.Type.Contains(TEXT("Bellum"));
        const FLinearColor Body = Enemy.HitFlash > 0.0f ? FLinearColor(1.0f, 0.20f, 0.20f, 1.0f) : bBellum ? FLinearColor(0.04f, 0.018f, 0.014f, 1.0f) : FLinearColor(0.42f, 0.10f, 0.42f, 1.0f);
        AES_ER(-35.0f, -81.0f, 70.0f, 80.0f, FLinearColor(0.02f, 0.01f, 0.01f, 1.0f));
        AES_ER(-28.0f, -76.0f, 56.0f, 74.0f, Body);
        AES_ER(-38.0f, -92.0f, 76.0f, 19.0f, bBellum ? Magma : FLinearColor(0.18f, 0.08f, 0.16f, 1.0f));
        AES_ER(-18.0f, -112.0f, 36.0f, 31.0f, bBellum ? FLinearColor(0.10f, 0.03f, 0.02f, 1.0f) : Body);
        AES_ER(-14.0f, -116.0f, 28.0f, 8.0f, FLinearColor(0.02f, 0.01f, 0.01f, 1.0f));
        AES_ER(-11.0f, -101.0f, 6.0f, 6.0f, Magma);
        AES_ER(6.0f, -101.0f, 6.0f, 6.0f, Magma);
        AES_ER(-9.0f, -91.0f, 18.0f, 3.0f, Magma);
        AES_EL(-21.0f, -62.0f, -43.0f, -22.0f, Body, 12.0f);
        AES_EL(22.0f, -63.0f, 51.0f, -17.0f, FLinearColor(0.18f, 0.17f, 0.16f, 1.0f), 12.0f);
        AES_EL(45.0f, -20.0f, 75.0f, -7.0f, FLinearColor(0.55f, 0.55f, 0.50f, 1.0f), 8.0f);
        AES_EL(51.0f, -17.0f, 68.0f, -37.0f, FLinearColor(0.55f, 0.55f, 0.50f, 1.0f), 5.0f);
        AES_ER(-25.0f, -16.0f, 18.0f, 17.0f, FLinearColor(0.12f, 0.07f, 0.05f, 1.0f));
        AES_ER(7.0f, -16.0f, 18.0f, 17.0f, FLinearColor(0.12f, 0.07f, 0.05f, 1.0f));
        AES_EL(-18.0f, -70.0f, 18.0f, -20.0f, Vein, 3.0f);
        AES_EL(15.0f, -72.0f, -12.0f, -34.0f, Vein, 2.0f);
        AES_EL(-5.0f, -72.0f, -22.0f, -36.0f, Magma, 2.0f);
        AES_EL(6.0f, -70.0f, 25.0f, -39.0f, Magma, 2.0f);
        if (bBellum)
        {
            AES_ER(-8.0f, -62.0f, 16.0f, 45.0f, Magma);
            AES_ER(-18.0f, -80.0f, 36.0f, 5.0f, Magma);
            AES_EL(-34.0f, -112.0f, -55.0f, -139.0f, Magma, 6.0f);
            AES_EL(34.0f, -112.0f, 55.0f, -139.0f, Magma, 6.0f);
            AES_EL(-55.0f, -139.0f, -25.0f, -127.0f, Magma, 4.0f);
            AES_EL(55.0f, -139.0f, 25.0f, -127.0f, Magma, 4.0f);
            AES_ER(-16.0f, -146.0f, 32.0f, 30.0f, FLinearColor(1.0f, 0.34f, 0.0f, 0.70f));
            AES_EL(-40.0f, -25.0f, 48.0f, -118.0f, Magma, 6.0f);
        }
    }
#undef AES_ER
#undef AES_EL

    const float NameY = Enemy.Type.Contains(TEXT("Servi")) ? FeetY - 226.0f * S : FeetY - 164.0f * S;
    DrawBar(X - 42.0f, NameY + 20.0f, 84.0f, 8.0f, Enemy.Health / Enemy.MaxHealth, TEXT(""), FLinearColor(0.05f, 0.05f, 0.05f, 1.0f), Enemy.bBoss ? FLinearColor(1.0f, 0.27f, 0.0f, 1.0f) : FLinearColor(0.55f, 0.0f, 0.0f, 1.0f));
    DrawText(Enemy.Type, FLinearColor(0.93f, 0.88f, 0.55f, 1.0f), X - 64.0f, NameY, nullptr, 0.66f);
}

void AAesHUD::DrawForge(float X, float GroundY)
{
    DrawAesOreCrystal(X - 72.0f, GroundY - 132.0f, 0.55f);
    DrawAesStone(TEXT("ingot"), X - 16.0f, GroundY - 108.0f, 0.52f);
    DrawAesStone(TEXT("geode"), X + 32.0f, GroundY - 108.0f, 0.45f);
    DrawPanel(X - 48.0f, GroundY - 82.0f, 96.0f, 82.0f, FLinearColor(0.18f, 0.10f, 0.07f, 1.0f));
    DrawPanel(X - 54.0f, GroundY - 96.0f, 108.0f, 18.0f, FLinearColor(0.28f, 0.18f, 0.11f, 1.0f));
    DrawPanel(X - 18.0f, GroundY - 126.0f, 36.0f, 38.0f, FLinearColor(0.22f, 0.22f, 0.22f, 1.0f));
    DrawPanel(X - 12.0f, GroundY - 138.0f, 24.0f, 16.0f, FLinearColor(1.0f, 0.55f, 0.12f, 1.0f));
    DrawPanel(X + 22.0f, GroundY - 48.0f, 38.0f, 9.0f, FLinearColor(0.58f, 0.58f, 0.54f, 1.0f));
    DrawSegment(X + 50.0f, GroundY - 42.0f, X + 68.0f, GroundY - 20.0f, FLinearColor(0.40f, 0.24f, 0.12f, 1.0f), 5.0f);
    DrawAesTool(TEXT("hammer"), X + 56.0f, GroundY - 104.0f, 0.48f);
    DrawAesTool(TEXT("chisel"), X + 78.0f, GroundY - 72.0f, 0.36f);
    DrawAesTool(TEXT("stylus"), X - 42.0f, GroundY - 66.0f, 0.34f);
    DrawText(TEXT("Forja Aes"), FLinearColor(0.77f, 0.61f, 0.15f, 1.0f), X - 34.0f, GroundY - 158.0f, nullptr, 0.8f);
}

void AAesHUD::DrawAesOreCrystal(float X, float Y, float Scale)
{
#define AES_OR(RX, RY, RW, RH, COLOR) DrawPanel(X + (RX) * Scale, Y + (RY) * Scale, (RW) * Scale, (RH) * Scale, (COLOR))
#define AES_OL(X1, Y1, X2, Y2, COLOR, THICK) DrawSegment(X + (X1) * Scale, Y + (Y1) * Scale, X + (X2) * Scale, Y + (Y2) * Scale, (COLOR), (THICK) * Scale)
    const FLinearColor Gold(0.83f, 0.69f, 0.22f, 1.0f);
    const FLinearColor Emerald(0.02f, 0.65f, 0.36f, 1.0f);
    AES_OR(-18.0f, 10.0f, 56.0f, 14.0f, Gold);
    AES_OR(-3.0f, -48.0f, 24.0f, 60.0f, Emerald);
    AES_OR(3.0f, -39.0f, 10.0f, 42.0f, FLinearColor(0.45f, 1.0f, 0.70f, 0.75f));
    AES_OR(-14.0f, -18.0f, 15.0f, 34.0f, FLinearColor(0.0f, 0.42f, 0.25f, 1.0f));
    AES_OR(18.0f, -22.0f, 15.0f, 38.0f, FLinearColor(0.0f, 0.48f, 0.28f, 1.0f));
    AES_OL(-3.0f, -48.0f, 9.0f, -66.0f, Gold, 3.0f);
    AES_OL(21.0f, -48.0f, 9.0f, -66.0f, Gold, 3.0f);
    AES_OL(-14.0f, -18.0f, -6.0f, -31.0f, Gold, 2.0f);
    AES_OL(33.0f, -22.0f, 24.0f, -35.0f, Gold, 2.0f);
#undef AES_OR
#undef AES_OL
}

void AAesHUD::DrawAesTool(const FString& ToolName, float X, float Y, float Scale)
{
    const FLinearColor Wood(0.30f, 0.18f, 0.10f, 1.0f);
    const FLinearColor Leather(0.18f, 0.09f, 0.04f, 1.0f);
    const FLinearColor Steel(0.56f, 0.58f, 0.55f, 1.0f);
    const FLinearColor DarkSteel(0.16f, 0.17f, 0.17f, 1.0f);
    const FLinearColor Gold(0.83f, 0.69f, 0.30f, 1.0f);
    const FLinearColor Aes(0.0f, 0.82f, 0.48f, 1.0f);

    if (ToolName == TEXT("sword"))
    {
        DrawSegment(X - 44.0f * Scale, Y + 48.0f * Scale, X + 45.0f * Scale, Y - 48.0f * Scale, Steel, 8.0f * Scale);
        DrawSegment(X - 36.0f * Scale, Y + 38.0f * Scale, X + 42.0f * Scale, Y - 43.0f * Scale, Aes, 2.2f * Scale);
        DrawSegment(X - 54.0f * Scale, Y + 36.0f * Scale, X - 28.0f * Scale, Y + 61.0f * Scale, Gold, 5.0f * Scale);
        DrawSegment(X - 61.0f * Scale, Y + 52.0f * Scale, X - 42.0f * Scale, Y + 71.0f * Scale, Leather, 8.0f * Scale);
    }
    else if (ToolName == TEXT("lance"))
    {
        DrawSegment(X - 62.0f * Scale, Y + 44.0f * Scale, X + 58.0f * Scale, Y - 46.0f * Scale, Wood, 6.0f * Scale);
        DrawSegment(X + 40.0f * Scale, Y - 32.0f * Scale, X + 70.0f * Scale, Y - 58.0f * Scale, Steel, 7.0f * Scale);
        DrawSegment(X + 45.0f * Scale, Y - 34.0f * Scale, X + 64.0f * Scale, Y - 51.0f * Scale, Aes, 2.0f * Scale);
        DrawSegment(X - 10.0f * Scale, Y + 5.0f * Scale, X + 10.0f * Scale, Y - 10.0f * Scale, Gold, 3.0f * Scale);
    }
    else if (ToolName == TEXT("axe"))
    {
        DrawSegment(X - 42.0f * Scale, Y + 48.0f * Scale, X + 30.0f * Scale, Y - 42.0f * Scale, Wood, 8.0f * Scale);
        DrawPanel(X + 14.0f * Scale, Y - 58.0f * Scale, 36.0f * Scale, 38.0f * Scale, DarkSteel);
        DrawSegment(X + 14.0f * Scale, Y - 40.0f * Scale, X - 8.0f * Scale, Y - 65.0f * Scale, Steel, 8.0f * Scale);
        DrawSegment(X + 46.0f * Scale, Y - 40.0f * Scale, X + 70.0f * Scale, Y - 65.0f * Scale, Steel, 8.0f * Scale);
        DrawPanel(X + 26.0f * Scale, Y - 48.0f * Scale, 10.0f * Scale, 18.0f * Scale, Aes);
    }
    else if (ToolName == TEXT("dagger"))
    {
        DrawSegment(X - 26.0f * Scale, Y + 32.0f * Scale, X + 27.0f * Scale, Y - 30.0f * Scale, Steel, 7.0f * Scale);
        DrawSegment(X - 18.0f * Scale, Y + 22.0f * Scale, X + 24.0f * Scale, Y - 25.0f * Scale, Aes, 2.0f * Scale);
        DrawSegment(X - 34.0f * Scale, Y + 27.0f * Scale, X - 18.0f * Scale, Y + 43.0f * Scale, Gold, 5.0f * Scale);
        DrawSegment(X - 42.0f * Scale, Y + 38.0f * Scale, X - 30.0f * Scale, Y + 52.0f * Scale, Leather, 7.0f * Scale);
    }
    else if (ToolName == TEXT("hammer"))
    {
        DrawSegment(X - 60.0f * Scale, Y + 42.0f * Scale, X + 18.0f * Scale, Y - 24.0f * Scale, Wood, 9.0f * Scale);
        DrawPanel(X + 4.0f * Scale, Y - 48.0f * Scale, 42.0f * Scale, 32.0f * Scale, DarkSteel);
        DrawPanel(X - 2.0f * Scale, Y - 43.0f * Scale, 54.0f * Scale, 12.0f * Scale, Steel);
        DrawPanel(X + 16.0f * Scale, Y - 42.0f * Scale, 8.0f * Scale, 22.0f * Scale, Aes);
        DrawSegment(X + 8.0f * Scale, Y - 47.0f * Scale, X + 43.0f * Scale, Y - 19.0f * Scale, Aes, 2.0f * Scale);
        DrawPanel(X - 7.0f * Scale, Y - 27.0f * Scale, 10.0f * Scale, 10.0f * Scale, Gold);
    }
    else if (ToolName == TEXT("stylus"))
    {
        DrawSegment(X - 42.0f * Scale, Y + 38.0f * Scale, X + 42.0f * Scale, Y - 38.0f * Scale, Wood, 8.0f * Scale);
        DrawSegment(X - 8.0f * Scale, Y + 7.0f * Scale, X + 42.0f * Scale, Y - 38.0f * Scale, Gold, 3.0f * Scale);
        DrawSegment(X + 38.0f * Scale, Y - 34.0f * Scale, X + 58.0f * Scale, Y - 48.0f * Scale, Steel, 5.0f * Scale);
        DrawSegment(X - 45.0f * Scale, Y + 40.0f * Scale, X - 26.0f * Scale, Y + 56.0f * Scale, Aes, 3.0f * Scale);
    }
    else
    {
        DrawSegment(X - 28.0f * Scale, Y + 38.0f * Scale, X + 20.0f * Scale, Y - 34.0f * Scale, Wood, 6.0f * Scale);
        DrawSegment(X + 17.0f * Scale, Y - 31.0f * Scale, X + 40.0f * Scale, Y - 55.0f * Scale, Steel, 5.0f * Scale);
        DrawSegment(X - 8.0f * Scale, Y + 20.0f * Scale, X + 34.0f * Scale, Y - 42.0f * Scale, Gold, 2.0f * Scale);
    }
}

void AAesHUD::DrawAesStone(const FString& StoneName, float X, float Y, float Scale)
{
    const FLinearColor Emerald(0.0f, 0.62f, 0.36f, 1.0f);
    const FLinearColor Glow(0.36f, 1.0f, 0.66f, 0.75f);
    const FLinearColor Gold(0.83f, 0.68f, 0.28f, 1.0f);
    const FLinearColor OreDark(0.11f, 0.12f, 0.10f, 1.0f);
    if (StoneName == TEXT("ingot"))
    {
        DrawPanel(X - 32.0f * Scale, Y - 14.0f * Scale, 64.0f * Scale, 28.0f * Scale, Emerald);
        DrawPanel(X - 24.0f * Scale, Y - 22.0f * Scale, 56.0f * Scale, 8.0f * Scale, Glow);
        DrawSegment(X - 22.0f * Scale, Y - 8.0f * Scale, X + 18.0f * Scale, Y + 9.0f * Scale, FLinearColor(0.0f, 0.28f, 0.17f, 1.0f), 2.0f * Scale);
        DrawIconSeal(X, Y, 0.18f * Scale, Gold);
    }
    else if (StoneName == TEXT("geode"))
    {
        DrawPanel(X - 34.0f * Scale, Y - 20.0f * Scale, 68.0f * Scale, 40.0f * Scale, OreDark);
        DrawPanel(X - 20.0f * Scale, Y - 11.0f * Scale, 38.0f * Scale, 21.0f * Scale, FLinearColor(0.02f, 0.36f, 0.22f, 1.0f));
        DrawPanel(X - 10.0f * Scale, Y - 5.0f * Scale, 14.0f * Scale, 10.0f * Scale, Glow);
        DrawSegment(X - 30.0f * Scale, Y - 18.0f * Scale, X - 15.0f * Scale, Y - 28.0f * Scale, Gold, 4.0f * Scale);
        DrawSegment(X + 25.0f * Scale, Y + 16.0f * Scale, X + 38.0f * Scale, Y + 6.0f * Scale, Gold, 4.0f * Scale);
    }
    else
    {
        DrawAesOreCrystal(X, Y, Scale);
    }
}

void AAesHUD::DrawItemCard(const FString& Title, const FString& ItemType, float X, float Y, float W, float H)
{
    DrawPanel(X, Y, W, H, FLinearColor(0.58f, 0.49f, 0.33f, 0.45f));
    DrawPanel(X + 8.0f, Y + 8.0f, W - 16.0f, H - 16.0f, FLinearColor(0.14f, 0.11f, 0.07f, 0.72f));
    DrawSegment(X + 16.0f, Y + 28.0f, X + W - 16.0f, Y + 28.0f, FLinearColor(0.77f, 0.62f, 0.35f, 1.0f), 1.6f);
    DrawText(Title, FLinearColor(0.92f, 0.84f, 0.66f, 1.0f), X + 15.0f, Y + 12.0f, nullptr, 0.56f);
    DrawAesTool(ItemType, X + W * 0.50f, Y + H * 0.58f, 0.58f);
}

void AAesHUD::DrawForestArtPanel(float X, float Y, float W, float H, bool bNight)
{
    const FLinearColor SkyA = bNight ? FLinearColor(0.02f, 0.07f, 0.12f, 1.0f) : FLinearColor(0.14f, 0.33f, 0.31f, 1.0f);
    const FLinearColor SkyB = bNight ? FLinearColor(0.02f, 0.14f, 0.15f, 1.0f) : FLinearColor(0.38f, 0.62f, 0.56f, 1.0f);
    DrawPanel(X, Y, W, H, SkyA);
    DrawPanel(X, Y + H * 0.42f, W, H * 0.34f, SkyB);
    for (int32 I = 0; I < 5; ++I)
    {
        const float RayX = X + W * (0.18f + I * 0.15f);
        DrawSegment(RayX, Y + 8.0f, RayX + W * 0.10f, Y + H * 0.72f, FLinearColor(0.72f, 0.86f, 0.78f, bNight ? 0.10f : 0.18f), W * 0.018f);
    }
    for (int32 Layer = 0; Layer < 3; ++Layer)
    {
        const float Step = W / (4.0f + Layer);
        const FLinearColor Trunk = Layer == 0 ? FLinearColor(0.015f, 0.035f, 0.030f, 0.96f) : Layer == 1 ? FLinearColor(0.035f, 0.080f, 0.060f, 0.92f) : FLinearColor(0.07f, 0.15f, 0.10f, 0.88f);
        const FLinearColor Leaf = Layer == 0 ? FLinearColor(0.015f, 0.065f, 0.045f, 0.86f) : Layer == 1 ? FLinearColor(0.04f, 0.13f, 0.075f, 0.86f) : FLinearColor(0.11f, 0.25f, 0.15f, 0.80f);
        for (int32 I = 0; I < 7; ++I)
        {
            const float TX = X - Step * 0.5f + I * Step + Layer * 18.0f;
            const float TopY = Y + H * (0.10f + 0.06f * (I % 3)) - Layer * 8.0f;
            DrawPanel(TX, TopY, 11.0f + Layer * 4.0f, Y + H - TopY, Trunk);
            DrawSegment(TX + 7.0f, TopY + H * 0.22f, TX - 26.0f, TopY + H * 0.32f, Trunk, 4.0f + Layer);
            DrawSegment(TX + 8.0f, TopY + H * 0.28f, TX + 34.0f, TopY + H * 0.18f, Trunk, 4.0f + Layer);
            DrawPanel(TX - 28.0f, TopY - 16.0f, 68.0f, 34.0f, Leaf);
            DrawPanel(TX - 48.0f, TopY + 8.0f, 72.0f, 30.0f, Leaf);
        }
    }
    DrawPanel(X, Y + H * 0.72f, W, H * 0.28f, FLinearColor(0.07f, 0.12f, 0.08f, 0.95f));
    DrawPanel(X, Y + H * 0.82f, W, H * 0.18f, FLinearColor(0.13f, 0.10f, 0.07f, 0.98f));
    DrawPanel(X + W * 0.12f, Y + H * 0.76f, W * 0.18f, H * 0.06f, FLinearColor(0.08f, 0.17f, 0.10f, 0.86f));
    DrawPanel(X + W * 0.70f, Y + H * 0.78f, W * 0.22f, H * 0.05f, FLinearColor(0.10f, 0.18f, 0.11f, 0.80f));
}

void AAesHUD::DrawLibraryArtPanel(float X, float Y, float W, float H)
{
    DrawPanel(X, Y, W, H, FLinearColor(0.09f, 0.075f, 0.055f, 1.0f));
    DrawPanel(X + W * 0.38f, Y, W * 0.24f, H, FLinearColor(0.12f, 0.11f, 0.10f, 1.0f));
    for (int32 Side = 0; Side < 2; ++Side)
    {
        const float SX = Side == 0 ? X + 12.0f : X + W - W * 0.26f - 12.0f;
        DrawPanel(SX, Y + 10.0f, W * 0.26f, H - 20.0f, FLinearColor(0.10f, 0.055f, 0.025f, 0.94f));
        for (int32 Row = 0; Row < 4; ++Row)
        {
            const float BY = Y + 24.0f + Row * (H - 48.0f) / 4.0f;
            DrawPanel(SX + 8.0f, BY, W * 0.26f - 16.0f, 4.0f, FLinearColor(0.34f, 0.22f, 0.12f, 1.0f));
            for (int32 Book = 0; Book < 9; ++Book)
            {
                const float BH = 18.0f + static_cast<float>((Book + Row) % 3) * 5.0f;
                DrawPanel(SX + 14.0f + Book * 12.0f, BY - BH, 8.0f, BH, Book % 2 ? FLinearColor(0.18f, 0.08f, 0.05f, 1.0f) : FLinearColor(0.10f, 0.18f, 0.13f, 1.0f));
            }
        }
    }
    DrawPanel(X + W * 0.45f, Y + H * 0.18f, W * 0.10f, H * 0.48f, FLinearColor(0.04f, 0.04f, 0.04f, 0.90f));
    DrawSegment(X + W * 0.50f, Y + H * 0.18f, X + W * 0.50f, Y + H * 0.68f, FLinearColor(0.65f, 0.45f, 0.25f, 1.0f), 2.0f);
    for (int32 C = 0; C < 3; ++C)
    {
        const float CX = X + W * (0.18f + C * 0.32f);
        DrawSegment(CX, Y + H * 0.48f, CX, Y + H * 0.30f, FLinearColor(0.45f, 0.30f, 0.14f, 1.0f), 3.0f);
        DrawPanel(CX - 8.0f, Y + H * 0.30f, 16.0f, 20.0f, FLinearColor(1.0f, 0.55f, 0.16f, 0.78f));
    }
    DrawPanel(X, Y + H * 0.70f, W, H * 0.30f, FLinearColor(0.09f, 0.07f, 0.05f, 0.82f));
}

void AAesHUD::DrawStoryArtPanel(float X, float Y, float W, float H)
{
    DrawOrnateFrame(X, Y, W, H, TEXT("CARREGANDO HISTORIA"));
    DrawPanel(X + 18.0f, Y + 34.0f, W - 36.0f, H - 56.0f, FLinearColor(0.50f, 0.38f, 0.20f, 0.90f));
    DrawPanel(X + 30.0f, Y + 46.0f, W - 60.0f, H - 80.0f, FLinearColor(0.76f, 0.64f, 0.40f, 0.84f));
    DrawSegment(X + 46.0f, Y + H - 70.0f, X + W - 46.0f, Y + 58.0f, FLinearColor(0.35f, 0.22f, 0.12f, 0.20f), 3.0f);
    DrawText(TEXT("...das profundezas do minerio,"), FLinearColor(0.12f, 0.08f, 0.05f, 1.0f), X + W * 0.43f, Y + 58.0f, nullptr, 0.60f);
    DrawText(TEXT("os antigos juramentos despertam."), FLinearColor(0.12f, 0.08f, 0.05f, 1.0f), X + W * 0.43f, Y + 82.0f, nullptr, 0.60f);
    DrawPanel(X + W * 0.15f, Y + H * 0.45f, 34.0f, 48.0f, FLinearColor(0.30f, 0.22f, 0.15f, 1.0f));
    DrawPanel(X + W * 0.16f, Y + H * 0.36f, 26.0f, 24.0f, FLinearColor(0.42f, 0.30f, 0.18f, 1.0f));
    DrawSegment(X + W * 0.20f, Y + H * 0.49f, X + W * 0.32f, Y + H * 0.38f, FLinearColor(0.25f, 0.16f, 0.08f, 1.0f), 5.0f);
    DrawAesOreCrystal(X + W * 0.55f, Y + H * 0.62f, 0.86f);
    DrawPanel(X + W * 0.21f, Y + H * 0.73f, W * 0.58f, 16.0f, FLinearColor(0.10f, 0.07f, 0.04f, 1.0f));
    DrawPanel(X + W * 0.22f, Y + H * 0.735f, W * 0.38f, 8.0f, FLinearColor(0.82f, 0.65f, 0.22f, 1.0f));
    DrawText(TEXT("Berwick, Gradon e Valois aguardam a decisao do principe."), FLinearColor(0.17f, 0.10f, 0.05f, 1.0f), X + 46.0f, Y + H - 56.0f, nullptr, 0.58f);
}

void AAesHUD::DrawCreatorShowcase(float X, float Y, float W, float H, AAesPlayerController* PC)
{
    DrawOrnateFrame(X, Y, W, H, TEXT("CRIACAO DE PERSONAGEM"));
    DrawPanel(X + 20.0f, Y + 36.0f, W - 40.0f, H - 58.0f, FLinearColor(0.15f, 0.14f, 0.12f, 0.95f));
    DrawPanel(X + 20.0f, Y + 36.0f, W - 40.0f, H * 0.44f, FLinearColor(0.44f, 0.50f, 0.50f, 0.42f));
    DrawSegment(X + W * 0.24f, Y + H * 0.60f, X + W * 0.50f, Y + H * 0.28f, FLinearColor(0.92f, 0.78f, 0.42f, 0.20f), 18.0f);
    DrawSegment(X + W * 0.74f, Y + H * 0.60f, X + W * 0.50f, Y + H * 0.28f, FLinearColor(0.92f, 0.78f, 0.42f, 0.16f), 16.0f);
    DrawPanel(X + W * 0.10f, Y + H * 0.33f, W * 0.17f, H * 0.47f, FLinearColor(0.035f, 0.035f, 0.030f, 0.92f));
    DrawPanel(X + W * 0.73f, Y + H * 0.33f, W * 0.17f, H * 0.47f, FLinearColor(0.035f, 0.035f, 0.030f, 0.92f));
    for (int32 I = 0; I < 6; ++I)
    {
        const float IX = X + W * 0.13f + (I % 2) * 38.0f;
        const float IY = Y + H * 0.41f + (I / 2) * 36.0f;
        DrawPanel(IX, IY, 24.0f, 24.0f, FLinearColor(0.12f, 0.10f, 0.07f, 1.0f));
        DrawIconSeal(IX + 12.0f, IY + 12.0f, 0.10f, I == 1 ? FLinearColor(0.0f, 0.86f, 0.48f, 1.0f) : FLinearColor(0.75f, 0.60f, 0.34f, 1.0f));
    }
    DrawText(TEXT("Corpo"), FLinearColor(0.88f, 0.80f, 0.62f, 1.0f), X + W * 0.13f, Y + H * 0.36f, nullptr, 0.58f);
    DrawText(TEXT("Arquetipo"), FLinearColor(0.88f, 0.80f, 0.62f, 1.0f), X + W * 0.755f, Y + H * 0.36f, nullptr, 0.58f);
    for (int32 I = 0; I < 4; ++I)
    {
        DrawIconSeal(X + W * 0.80f, Y + H * (0.46f + I * 0.095f), 0.18f, I == static_cast<int32>(PC->Personality) % 4 ? FLinearColor(0.0f, 0.86f, 0.48f, 1.0f) : FLinearColor(0.58f, 0.48f, 0.30f, 1.0f));
    }
    const float BaseY = Y + H * 0.82f;
    DrawPanel(X + W * 0.33f, BaseY, W * 0.34f, 14.0f, FLinearColor(0.12f, 0.10f, 0.07f, 1.0f));
    DrawPanel(X + W * 0.37f, BaseY - 18.0f, W * 0.26f, 22.0f, FLinearColor(0.34f, 0.30f, 0.22f, 1.0f));
    DrawSegment(X + W * 0.40f, BaseY - 15.0f, X + W * 0.60f, BaseY - 15.0f, FLinearColor(0.0f, 0.84f, 0.48f, 0.70f), 2.0f);
    DrawWilliam(X + W * 0.50f, BaseY - 2.0f, 1.0f, true, 1.15f);
    DrawText(TEXT("360"), FLinearColor(0.88f, 0.80f, 0.62f, 1.0f), X + W * 0.48f, BaseY + 20.0f, nullptr, 0.62f);
}

void AAesHUD::DrawBattlePreviewPanel(float X, float Y, float W, float H)
{
    DrawOrnateFrame(X, Y, W, H, TEXT("BATTLEFIELD HUD"));
    DrawForestArtPanel(X + 18.0f, Y + 34.0f, W - 36.0f, H - 56.0f, false);
    DrawBar(X + 34.0f, Y + 50.0f, 112.0f, 8.0f, 0.82f, TEXT(""), FLinearColor(0.15f, 0.0f, 0.0f, 1.0f), FLinearColor(0.78f, 0.03f, 0.08f, 1.0f));
    DrawBar(X + 34.0f, Y + 63.0f, 112.0f, 8.0f, 0.76f, TEXT(""), FLinearColor(0.0f, 0.0f, 0.12f, 1.0f), FLinearColor(0.12f, 0.52f, 0.95f, 1.0f));
    DrawIconSeal(X + W * 0.50f, Y + 62.0f, 0.26f, FLinearColor(0.0f, 0.86f, 0.48f, 1.0f));
    DrawWilliam(X + W * 0.28f, Y + H - 62.0f, 1.0f, true, 0.45f);
    DrawCompanionFigure(TEXT("Ethan"), X + W * 0.40f, Y + H - 62.0f, 0.35f);
    const float EnemyBase = Y + H - 62.0f;
    const float BarbarianX = X + W * 0.62f;
    DrawPanel(BarbarianX - 10.0f, EnemyBase - 40.0f, 20.0f, 40.0f, FLinearColor(0.48f, 0.12f, 0.08f, 1.0f));
    DrawPanel(BarbarianX - 9.0f, EnemyBase - 58.0f, 18.0f, 18.0f, FLinearColor(0.60f, 0.25f, 0.16f, 1.0f));
    DrawSegment(BarbarianX - 22.0f, EnemyBase - 36.0f, BarbarianX - 48.0f, EnemyBase - 70.0f, FLinearColor(0.58f, 0.58f, 0.54f, 1.0f), 5.0f);
    DrawPanel(BarbarianX - 34.0f, EnemyBase - 76.0f, 30.0f, 8.0f, FLinearColor(0.22f, 0.20f, 0.18f, 1.0f));
    DrawBar(BarbarianX - 28.0f, EnemyBase - 78.0f, 56.0f, 5.0f, 0.80f, TEXT(""), FLinearColor(0.10f, 0.0f, 0.0f, 1.0f), FLinearColor(0.72f, 0.0f, 0.0f, 1.0f));
    const float BellumX = X + W * 0.78f;
    DrawPanel(BellumX - 19.0f, EnemyBase - 66.0f, 38.0f, 66.0f, FLinearColor(0.06f, 0.025f, 0.020f, 1.0f));
    DrawPanel(BellumX - 13.0f, EnemyBase - 86.0f, 26.0f, 24.0f, FLinearColor(0.11f, 0.025f, 0.015f, 1.0f));
    DrawSegment(BellumX - 14.0f, EnemyBase - 80.0f, BellumX - 36.0f, EnemyBase - 108.0f, FLinearColor(1.0f, 0.25f, 0.0f, 0.86f), 4.0f);
    DrawSegment(BellumX + 14.0f, EnemyBase - 80.0f, BellumX + 36.0f, EnemyBase - 108.0f, FLinearColor(1.0f, 0.25f, 0.0f, 0.86f), 4.0f);
    DrawSegment(BellumX - 8.0f, EnemyBase - 58.0f, BellumX + 8.0f, EnemyBase - 20.0f, FLinearColor(1.0f, 0.22f, 0.0f, 1.0f), 3.0f);
    DrawPanel(BellumX - 8.0f, EnemyBase - 78.0f, 5.0f, 5.0f, FLinearColor(1.0f, 0.55f, 0.0f, 1.0f));
    DrawPanel(BellumX + 3.0f, EnemyBase - 78.0f, 5.0f, 5.0f, FLinearColor(1.0f, 0.55f, 0.0f, 1.0f));
    DrawBar(BellumX - 34.0f, EnemyBase - 100.0f, 68.0f, 5.0f, 0.85f, TEXT(""), FLinearColor(0.12f, 0.0f, 0.0f, 1.0f), FLinearColor(1.0f, 0.25f, 0.0f, 1.0f));
    DrawPanel(X + W - 58.0f, Y + 54.0f, 36.0f, 110.0f, FLinearColor(0.02f, 0.025f, 0.02f, 0.64f));
    DrawIconSeal(X + W - 40.0f, Y + 76.0f, 0.24f, FLinearColor(0.77f, 0.66f, 0.25f, 1.0f));
    DrawIconSeal(X + W - 40.0f, Y + 113.0f, 0.24f, FLinearColor(0.0f, 0.86f, 0.48f, 1.0f));
    DrawIconSeal(X + W - 40.0f, Y + 150.0f, 0.24f, FLinearColor(0.0f, 0.58f, 0.88f, 1.0f));
    DrawPanel(X + W * 0.38f, Y + H - 38.0f, W * 0.28f, 22.0f, FLinearColor(0.025f, 0.025f, 0.022f, 0.88f));
    for (int32 I = 0; I < 6; ++I)
    {
        DrawPanel(X + W * 0.40f + I * 24.0f, Y + H - 34.0f, 18.0f, 16.0f, FLinearColor(0.12f, 0.10f, 0.07f, 1.0f));
    }
}

void AAesHUD::DrawEnding(AAesPlayerController* PC)
{
    const float W = Canvas->ClipX;
    const float H = Canvas->ClipY;
    DrawInterfaceBackdrop();
    DrawOrnateFrame(W * 0.5f - 350.0f, H * 0.5f - 190.0f, 700.0f, 380.0f, TEXT("RELATORIO DO PROLOGO"));
    DrawCenteredText(PC->bVictory ? TEXT("Prologo concluido") : TEXT("FIM DO JOGO"), H * 0.5f - 132.0f, 1.6f, FLinearColor(0.93f, 0.88f, 0.55f, 1.0f));
    DrawCenteredText(PC->bVictory ? TEXT("O aviso chega a Gradon. O exercito caiu, mas a chama Aes permanece.") : TEXT("Reconfigure rota, taticas e marcas para resistir ao prologo."), H * 0.5f - 78.0f, 0.95f, FLinearColor::White);
    DrawCenteredText(FString::Printf(TEXT("HP %.0f%%  Coragem %.0f%%  Lealdade %.0f%%  Minerio %d"), PC->GetHealthPercent() * 100.0f, PC->GetCouragePercent() * 100.0f, PC->GetLoyalty(), PC->Ore), H * 0.5f - 20.0f, 0.95f, FLinearColor(0.85f, 0.85f, 0.85f, 1.0f));
    DrawCenteredText(PC->SaveStatusText, H * 0.5f + 28.0f, 0.82f, FLinearColor(0.0f, 0.92f, 0.52f, 1.0f));
    DrawAesButton(W * 0.5f - 160.0f, H * 0.5f + 78.0f, 320.0f, 38.0f, PC->bVictory ? TEXT("ENTER - VOLTAR AO INICIO") : TEXT("ENTER - CONTINUAR DO SALVO"), true);
    DrawCenteredText(TEXT("ESC - inicio do jogo"), H * 0.5f + 130.0f, 0.78f, FLinearColor(0.78f, 0.76f, 0.68f, 1.0f));
}

void AAesHUD::DrawInterfaceBackdrop()
{
    const float W = Canvas->ClipX;
    const float H = Canvas->ClipY;
    DrawPanel(0, 0, W, H, FLinearColor(0.018f, 0.019f, 0.017f, 1.0f));
    DrawPanel(0, 0, W, H * 0.20f, FLinearColor(0.055f, 0.045f, 0.035f, 0.68f));
    DrawPanel(0, H * 0.78f, W, H * 0.22f, FLinearColor(0.035f, 0.032f, 0.026f, 0.86f));
    for (int32 I = 0; I < 13; ++I)
    {
        const float X = I * W / 12.0f;
        DrawPanel(X - 8.0f, 0.0f, 16.0f, H, FLinearColor(0.0f, 0.16f, 0.12f, 0.12f));
        DrawSegment(X, 0.0f, X + 28.0f, H, FLinearColor(0.0f, 0.72f, 0.48f, 0.055f), 4.0f);
    }
    for (int32 Row = 0; Row < 7; ++Row)
    {
        DrawSegment(0.0f, Row * H / 6.0f, W, Row * H / 6.0f + 14.0f, FLinearColor(0.15f, 0.14f, 0.11f, 0.12f), 1.5f);
    }
    DrawPanel(W * 0.19f, 0.0f, W * 0.62f, H, FLinearColor(0.07f, 0.06f, 0.048f, 0.10f));
}

void AAesHUD::DrawOrnateFrame(float X, float Y, float W, float H, const FString& Title)
{
    const FLinearColor Dark(0.012f, 0.014f, 0.013f, 0.94f);
    const FLinearColor Metal(0.24f, 0.23f, 0.20f, 1.0f);
    const FLinearColor Gold(0.76f, 0.64f, 0.40f, 1.0f);
    const FLinearColor Emerald(0.0f, 0.72f, 0.45f, 0.75f);
    DrawPanel(X - 10.0f, Y - 10.0f, W + 20.0f, H + 20.0f, FLinearColor(0.0f, 0.0f, 0.0f, 0.76f));
    DrawPanel(X - 5.0f, Y - 5.0f, W + 10.0f, H + 10.0f, FLinearColor(0.18f, 0.17f, 0.14f, 1.0f));
    DrawPanel(X, Y, W, H, Dark);
    DrawPanel(X, Y, W, 4.0f, Metal);
    DrawPanel(X, Y + H - 4.0f, W, 4.0f, Metal);
    DrawPanel(X, Y, 4.0f, H, Metal);
    DrawPanel(X + W - 4.0f, Y, 4.0f, H, Metal);
    DrawPanel(X + 4.0f, Y + 4.0f, W - 8.0f, 2.0f, Gold);
    DrawPanel(X + 4.0f, Y + H - 6.0f, W - 8.0f, 2.0f, Gold);
    DrawPanel(X + 4.0f, Y + 4.0f, 2.0f, H - 8.0f, Gold);
    DrawPanel(X + W - 6.0f, Y + 4.0f, 2.0f, H - 8.0f, Gold);
    DrawPanel(X + 7.0f, Y + 7.0f, W - 14.0f, 2.0f, Emerald);
    DrawPanel(X + 7.0f, Y + H - 9.0f, W - 14.0f, 2.0f, Emerald);
    DrawPanel(X + 7.0f, Y + 7.0f, 2.0f, H - 14.0f, Emerald);
    DrawPanel(X + W - 9.0f, Y + 7.0f, 2.0f, H - 14.0f, Emerald);
    DrawSegment(X + 10.0f, Y + 10.0f, X + 34.0f, Y + 10.0f, Gold, 3.0f);
    DrawSegment(X + 10.0f, Y + 10.0f, X + 10.0f, Y + 34.0f, Gold, 3.0f);
    DrawSegment(X + W - 10.0f, Y + 10.0f, X + W - 34.0f, Y + 10.0f, Gold, 3.0f);
    DrawSegment(X + W - 10.0f, Y + 10.0f, X + W - 10.0f, Y + 34.0f, Gold, 3.0f);
    DrawSegment(X + 10.0f, Y + H - 10.0f, X + 34.0f, Y + H - 10.0f, Gold, 3.0f);
    DrawSegment(X + 10.0f, Y + H - 10.0f, X + 10.0f, Y + H - 34.0f, Gold, 3.0f);
    DrawSegment(X + W - 10.0f, Y + H - 10.0f, X + W - 34.0f, Y + H - 10.0f, Gold, 3.0f);
    DrawSegment(X + W - 10.0f, Y + H - 10.0f, X + W - 10.0f, Y + H - 34.0f, Gold, 3.0f);
    if (!Title.IsEmpty())
    {
        DrawPanel(X + W * 0.20f - 10.0f, Y - 7.0f, W * 0.60f + 20.0f, 30.0f, FLinearColor(0.0f, 0.0f, 0.0f, 0.64f));
        DrawPanel(X + W * 0.20f, Y - 3.0f, W * 0.60f, 24.0f, FLinearColor(0.065f, 0.056f, 0.043f, 0.98f));
        DrawSegment(X + W * 0.20f, Y - 3.0f, X + W * 0.80f, Y - 3.0f, Gold, 1.4f);
        DrawSegment(X + W * 0.20f, Y + 21.0f, X + W * 0.80f, Y + 21.0f, Gold, 1.4f);
        float TextW = 0.0f;
        float TextH = 0.0f;
        GetTextSize(Title, TextW, TextH, nullptr, 0.90f);
        DrawText(Title, FLinearColor(0.88f, 0.80f, 0.62f, 1.0f), X + (W - TextW) * 0.5f, Y + 4.0f, nullptr, 0.90f);
    }
}

void AAesHUD::DrawAesButton(float X, float Y, float W, float H, const FString& Label, bool bPrimary)
{
    const FLinearColor Fill = bPrimary ? FLinearColor(0.0f, 0.38f, 0.25f, 0.98f) : FLinearColor(0.23f, 0.13f, 0.07f, 0.98f);
    const FLinearColor Edge = bPrimary ? FLinearColor(0.0f, 0.95f, 0.58f, 1.0f) : FLinearColor(0.83f, 0.69f, 0.38f, 1.0f);
    DrawPanel(X + 10.0f, Y, W - 20.0f, H, Fill);
    DrawSegment(X + 10.0f, Y, X + W - 10.0f, Y, Edge, 2.0f);
    DrawSegment(X + 10.0f, Y + H, X + W - 10.0f, Y + H, Edge, 2.0f);
    DrawSegment(X, Y + H * 0.5f, X + 10.0f, Y, Edge, 2.0f);
    DrawSegment(X, Y + H * 0.5f, X + 10.0f, Y + H, Edge, 2.0f);
    DrawSegment(X + W, Y + H * 0.5f, X + W - 10.0f, Y, Edge, 2.0f);
    DrawSegment(X + W, Y + H * 0.5f, X + W - 10.0f, Y + H, Edge, 2.0f);
    float TextW = 0.0f;
    float TextH = 0.0f;
    GetTextSize(Label, TextW, TextH, nullptr, 0.82f);
    DrawText(Label, FLinearColor::White, X + (W - TextW) * 0.5f, Y + (H - TextH) * 0.5f - 1.0f, nullptr, 0.82f);
}

void AAesHUD::DrawInputField(float X, float Y, float W, const FString& Label, const FString& Value, bool bSecure)
{
    DrawText(Label, FLinearColor(0.82f, 0.78f, 0.66f, 1.0f), X, Y - 17.0f, nullptr, 0.62f);
    DrawPanel(X, Y, W, 22.0f, FLinearColor(0.02f, 0.025f, 0.022f, 1.0f));
    DrawPanel(X + 2.0f, Y + 2.0f, W - 4.0f, 2.0f, FLinearColor(0.0f, 0.75f, 0.47f, 0.85f));
    DrawPanel(X + W - 16.0f, Y + 7.0f, 7.0f, 7.0f, FLinearColor(0.0f, 0.78f, 0.46f, 1.0f));
    DrawText(bSecure ? TEXT("********") : Value, FLinearColor(0.86f, 0.88f, 0.82f, 1.0f), X + 9.0f, Y + 4.0f, nullptr, 0.62f);
}

void AAesHUD::DrawIconSeal(float X, float Y, float Scale, const FLinearColor& Accent)
{
    DrawSegment(X, Y - 28.0f * Scale, X + 18.0f * Scale, Y, Accent, 4.0f * Scale);
    DrawSegment(X + 18.0f * Scale, Y, X, Y + 28.0f * Scale, Accent, 4.0f * Scale);
    DrawSegment(X, Y + 28.0f * Scale, X - 18.0f * Scale, Y, Accent, 4.0f * Scale);
    DrawSegment(X - 18.0f * Scale, Y, X, Y - 28.0f * Scale, Accent, 4.0f * Scale);
    DrawSegment(X, Y - 18.0f * Scale, X, Y + 18.0f * Scale, FLinearColor(0.85f, 0.74f, 0.46f, 1.0f), 2.0f * Scale);
    DrawSegment(X - 12.0f * Scale, Y, X + 12.0f * Scale, Y, FLinearColor(0.85f, 0.74f, 0.46f, 1.0f), 2.0f * Scale);
}

void AAesHUD::DrawPanel(float X, float Y, float W, float H, const FLinearColor& Color)
{
    DrawRect(Color, X, Y, W, H);
}

void AAesHUD::DrawBar(float X, float Y, float W, float H, float Percent, const FString& Label, const FLinearColor& Back, const FLinearColor& Fill)
{
    DrawPanel(X, Y, W, H, Back);
    DrawPanel(X, Y, W * FMath::Clamp(Percent, 0.0f, 1.0f), H, Fill);
    if (!Label.IsEmpty())
    {
        DrawText(Label, FLinearColor::White, X + 8.0f, Y + 2.0f, nullptr, 0.8f);
    }
}

void AAesHUD::DrawCenteredText(const FString& Text, float Y, float Scale, const FLinearColor& Color)
{
    float TextW = 0.0f;
    float TextH = 0.0f;
    GetTextSize(Text, TextW, TextH, nullptr, Scale);
    DrawText(Text, Color, (Canvas->ClipX - TextW) * 0.5f, Y, nullptr, Scale);
}

void AAesHUD::DrawSegment(float X1, float Y1, float X2, float Y2, const FLinearColor& Color, float Thickness)
{
    DrawLine(X1, Y1, X2, Y2, Color, Thickness);
}
