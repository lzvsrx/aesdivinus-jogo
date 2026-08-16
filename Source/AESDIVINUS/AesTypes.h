#pragma once

#include "CoreMinimal.h"
#include "AesTypes.generated.h"

UENUM(BlueprintType)
enum class EAesBrand : uint8
{
    None UMETA(DisplayName = "Nenhuma"),
    Gloregni UMETA(DisplayName = "Marca de Gloregni"),
    Iusdicta UMETA(DisplayName = "Marca de Iusdicta"),
    Satiae UMETA(DisplayName = "Marca de Satiae"),
    Thofestoe UMETA(DisplayName = "Marca de Thofestoe"),
    Miseritae UMETA(DisplayName = "Marca de Miseritae")
};

UENUM(BlueprintType)
enum class EArchetypePersonality : uint8
{
    Bravura UMETA(DisplayName = "Bravura"),
    Autocrata UMETA(DisplayName = "Autocrata"),
    Prudente UMETA(DisplayName = "Prudente"),
    Perfeccionista UMETA(DisplayName = "Perfeccionista")
};

UENUM(BlueprintType)
enum class EAesScreen : uint8
{
    Login,
    Register,
    Creator,
    Loading,
    Gameplay,
    Ending
};

UENUM(BlueprintType)
enum class EAesSquadOrder : uint8
{
    Shield,
    Archers,
    Charge
};

USTRUCT(BlueprintType)
struct FAesAttributes
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float Forca = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float Agilidade = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float Coragem = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float Percepcao = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float Inspiracao = 10.0f;
};

USTRUCT(BlueprintType)
struct FAesRoute
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Weapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Trait;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAesAttributes Mods;
};

USTRUCT(BlueprintType)
struct FAesEnemyState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float X = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Speed = 40.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCorrupted = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bBoss = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAlive = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HitFlash = 0.0f;
};
