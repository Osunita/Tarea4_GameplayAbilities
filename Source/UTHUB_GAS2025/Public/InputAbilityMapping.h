// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "InputAbilityMapping.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UInputAbilityMapping : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category=Mappings)
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> Mappings;
};
