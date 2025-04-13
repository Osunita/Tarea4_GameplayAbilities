// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interactive.generated.h"

UCLASS()
class UTHUB_GAS2025_API AInteractive : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractive();

	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteAction();

	UFUNCTION(BlueprintCallable)
	void CheckTagCondition(AActor* TagOwner);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag ConditionTag;

protected:
		
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
