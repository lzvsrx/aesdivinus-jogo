#include "AesGameModeBase.h"
#include "AesCharacter.h"
#include "AesHUD.h"
#include "AesPlayerController.h"

AAesGameModeBase::AAesGameModeBase()
{
    DefaultPawnClass = AAesCharacter::StaticClass();
    HUDClass = AAesHUD::StaticClass();
    PlayerControllerClass = AAesPlayerController::StaticClass();
}
