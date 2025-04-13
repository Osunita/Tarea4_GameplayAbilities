// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GameplayBaseStateTags.generated.h"


UCLASS()
class UTHUB_GAS2025_API UGameplayBaseStateTags : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Tag_Alive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Tag_Dead;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Tag_DeParranda;	
};
