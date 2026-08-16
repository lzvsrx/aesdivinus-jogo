#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AesTypes.h"
#include "AesStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrandActivated, EAesBrand, Brand);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoyaltyBroken, AActor*, DesertingActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AESDIVINUS_API UAesStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAesStatsComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FAesAttributes BaseAttributes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
    float CurrentHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float MaxCourage = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
    float CurrentCourage = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0", ClampMax = "100.0"))
    float Loyalty = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Personality")
    EArchetypePersonality Personality = EArchetypePersonality::Bravura;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
    bool bHasPhysicalTrauma = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
    bool bHasPsychologicalTrauma = false;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnBrandActivated OnBrandActivated;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLoyaltyBroken OnLoyaltyBroken;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ApplyDamage(float DamageAmount, bool bIsAesDivinusWeapon, bool bIsCorruptedTarget);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ReduceCourage(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Brands")
    void ActivateBrand(EAesBrand BrandToActivate);

protected:
    virtual void BeginPlay() override;

private:
    void HandleCourageCollapse();
};
