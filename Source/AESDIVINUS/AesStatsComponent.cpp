#include "AesStatsComponent.h"

UAesStatsComponent::UAesStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAesStatsComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
    CurrentCourage = MaxCourage;
}

void UAesStatsComponent::ApplyDamage(float DamageAmount, bool bIsAesDivinusWeapon, bool bIsCorruptedTarget)
{
    float FinalDamage = DamageAmount;
    if (bIsAesDivinusWeapon && bIsCorruptedTarget)
    {
        FinalDamage *= 1.8f;
    }

    CurrentHealth = FMath::Clamp(CurrentHealth - FinalDamage, 0.0f, MaxHealth);
    if (CurrentHealth <= 0.0f && !bHasPhysicalTrauma)
    {
        bHasPhysicalTrauma = true;
        Loyalty = FMath::Clamp(Loyalty - 20.0f, 0.0f, 100.0f);
    }
}

void UAesStatsComponent::ReduceCourage(float Amount)
{
    CurrentCourage = FMath::Clamp(CurrentCourage - Amount, 0.0f, MaxCourage);
    if (CurrentCourage <= 0.0f)
    {
        HandleCourageCollapse();
    }
}

void UAesStatsComponent::HandleCourageCollapse()
{
    if (Personality == EArchetypePersonality::Bravura)
    {
        CurrentCourage = MaxCourage * 0.5f;
        BaseAttributes.Forca += 2.0f;
        bHasPsychologicalTrauma = false;
    }
    else
    {
        bHasPsychologicalTrauma = true;
        Loyalty = FMath::Clamp(Loyalty - 30.0f, 0.0f, 100.0f);
        if (Loyalty < 50.0f)
        {
            OnLoyaltyBroken.Broadcast(GetOwner());
        }
    }
}

void UAesStatsComponent::ActivateBrand(EAesBrand BrandToActivate)
{
    switch (BrandToActivate)
    {
    case EAesBrand::Gloregni:
        BaseAttributes.Inspiracao += 5.0f;
        Loyalty = FMath::Clamp(Loyalty + 25.0f, 0.0f, 100.0f);
        break;
    case EAesBrand::Iusdicta:
        BaseAttributes.Forca += 3.0f;
        BaseAttributes.Percepcao += 3.0f;
        break;
    case EAesBrand::Satiae:
        BaseAttributes.Percepcao += 5.0f;
        break;
    case EAesBrand::Thofestoe:
        BaseAttributes.Inspiracao += 2.0f;
        break;
    case EAesBrand::Miseritae:
        CurrentHealth = FMath::Clamp(CurrentHealth + 35.0f, 0.0f, MaxHealth);
        break;
    default:
        break;
    }

    OnBrandActivated.Broadcast(BrandToActivate);
}
