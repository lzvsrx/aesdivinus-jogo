#include "AesCharacter.h"
#include "AesStatsComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAesCharacter::AAesCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    RootComponent = Capsule;
    Capsule->SetCapsuleHalfHeight(88.0f);
    Capsule->SetCapsuleRadius(28.0f);

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 900.0f;
    CameraBoom->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
    CameraBoom->bDoCollisionTest = false;

    SideCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideCamera"));
    SideCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    StatsComponent = CreateDefaultSubobject<UAesStatsComponent>(TEXT("StatsComponent"));
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AAesCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AttackCooldown = FMath::Max(0.0f, AttackCooldown - DeltaSeconds);
    DodgeCooldown = FMath::Max(0.0f, DodgeCooldown - DeltaSeconds);
    InvulnerableTime = FMath::Max(0.0f, InvulnerableTime - DeltaSeconds);
    SetActorLocation(FVector(BoardPosition.X, 0.0f, BoardPosition.Y));
}

void AAesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAesCharacter::MoveOnBoard(float AxisValue, float Speed, float DeltaSeconds)
{
    Velocity.X = AxisValue * Speed;
    if (!FMath::IsNearlyZero(AxisValue))
    {
        Facing = FMath::Sign(AxisValue);
    }

    Velocity.Y += 1450.0f * DeltaSeconds;
    BoardPosition.X = FMath::Clamp(BoardPosition.X + Velocity.X * DeltaSeconds, 30.0f, 1240.0f);
    BoardPosition.Y += Velocity.Y * DeltaSeconds;
    if (BoardPosition.Y >= 550.0f)
    {
        BoardPosition.Y = 550.0f;
        Velocity.Y = 0.0f;
        bGrounded = true;
    }
}

void AAesCharacter::JumpOnBoard()
{
    if (bGrounded)
    {
        Velocity.Y = -560.0f;
        bGrounded = false;
    }
}

void AAesCharacter::DodgeOnBoard(float Agility)
{
    if (DodgeCooldown > 0.0f)
    {
        return;
    }

    DodgeCooldown = 0.75f;
    InvulnerableTime = 0.28f;
    BoardPosition.X += Facing * (96.0f + Agility * 3.0f);
}

void AAesCharacter::SetBoardPosition(float X, float Z)
{
    BoardPosition = FVector2D(X, Z);
    Velocity = FVector2D::ZeroVector;
    bGrounded = true;
}
