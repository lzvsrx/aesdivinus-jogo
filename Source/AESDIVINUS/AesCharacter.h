#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AesCharacter.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UAesStatsComponent;

UCLASS()
class AESDIVINUS_API AAesCharacter : public APawn
{
    GENERATED_BODY()

public:
    AAesCharacter();

    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* Capsule;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* SideCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAesStatsComponent* StatsComponent;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    FVector2D BoardPosition = FVector2D(80.0f, 550.0f);

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    FVector2D Velocity = FVector2D::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    float Facing = 1.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bGrounded = true;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    float AttackCooldown = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    float DodgeCooldown = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    float InvulnerableTime = 0.0f;

    void MoveOnBoard(float AxisValue, float Speed, float DeltaSeconds);
    void JumpOnBoard();
    void DodgeOnBoard(float Agility);
    void SetBoardPosition(float X, float Z);
};
