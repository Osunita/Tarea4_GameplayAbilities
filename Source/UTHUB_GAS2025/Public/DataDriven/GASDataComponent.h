// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "GASDataComponent.generated.h"


class UInputAbilityMapping;
class UGameplayAttributeEffector;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTHUB_GAS2025_API UGASDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGASDataComponent();

	UPROPERTY(EditAnywhere, Category ="Data", meta = (AllowPrivateAccess = true))
	UDataTable* DT_CoreStats;
	
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<class UGameplayEffect>> AttributeInitializers;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	TMap<FGameplayAttribute, TSubclassOf<UGameplayAttributeEffector>> AttributeEffectors;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UGameplayAbility> DefaultAbility;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	UInputAbilityMapping* InputAbilityMapping;
};
