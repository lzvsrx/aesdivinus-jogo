#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AesTypes.h"
#include "AesHUD.generated.h"

class AAesPlayerController;

UCLASS()
class AESDIVINUS_API AAesHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

private:
    AAesPlayerController* GetAesController() const;
    void DrawLogin(AAesPlayerController* PC);
    void DrawCreator(AAesPlayerController* PC);
    void DrawLoading(AAesPlayerController* PC);
    void DrawGameplay(AAesPlayerController* PC);
    void DrawEnding(AAesPlayerController* PC);
    void DrawForestScene(AAesPlayerController* PC, float CameraX);
    void DrawWilliam(float X, float FeetY, float Facing, bool bAesBlade, float Scale);
    void DrawCompanionFigure(const FString& RoleName, float X, float FeetY, float Scale);
    void DrawEnemyFigure(const FAesEnemyState& Enemy, float X, float FeetY);
    void DrawForge(float X, float GroundY);
    void DrawAesOreCrystal(float X, float Y, float Scale);
    void DrawAesTool(const FString& ToolName, float X, float Y, float Scale);
    void DrawAesStone(const FString& StoneName, float X, float Y, float Scale);
    void DrawItemCard(const FString& Title, const FString& ItemType, float X, float Y, float W, float H);
    void DrawForestArtPanel(float X, float Y, float W, float H, bool bNight);
    void DrawLibraryArtPanel(float X, float Y, float W, float H);
    void DrawStoryArtPanel(float X, float Y, float W, float H);
    void DrawCreatorShowcase(float X, float Y, float W, float H, AAesPlayerController* PC);
    void DrawBattlePreviewPanel(float X, float Y, float W, float H);
    void DrawInterfaceBackdrop();
    void DrawOrnateFrame(float X, float Y, float W, float H, const FString& Title);
    void DrawAesButton(float X, float Y, float W, float H, const FString& Label, bool bPrimary);
    void DrawInputField(float X, float Y, float W, const FString& Label, const FString& Value, bool bSecure);
    void DrawIconSeal(float X, float Y, float Scale, const FLinearColor& Accent);
    void DrawPanel(float X, float Y, float W, float H, const FLinearColor& Color);
    void DrawBar(float X, float Y, float W, float H, float Percent, const FString& Label, const FLinearColor& Back, const FLinearColor& Fill);
    void DrawCenteredText(const FString& Text, float Y, float Scale, const FLinearColor& Color);
    void DrawSegment(float X1, float Y1, float X2, float Y2, const FLinearColor& Color, float Thickness);
};
