// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "UTHUB_ASC.h"
#include "GameFramework/Character.h"
#include "UTHUB_GAS2025Character.generated.h"

class UCoreAttributeSet;
class UGameplayBaseStateTags;

USTRUCT()
struct FCharacterAttributes : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)	FGameplayTag CharacterClassTag;
	UPROPERTY(EditAnywhere)	float Health;
	UPROPERTY(EditAnywhere) float AttackStrength;
	UPROPERTY(EditAnywhere)	float Speed;
	UPROPERTY(EditAnywhere)	UAnimMontage* AttackAnimation;
};

UCLASS(Blueprintable)
class AUTHUB_GAS2025Character : public ACharacter, public IAbilitySystemInterface, public IGameplayTagCustomInterface
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(AllowPrivateAccess))
	FGameplayTag CharacterClassTag;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(AllowPrivateAccess))
	FCharacterAttributes* Attributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(AllowPrivateAccess))
	UDataTable* CharacterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> SampleEffect;
	
	UPROPERTY()
	UCoreAttributeSet* CoreAttributeSet;
	
public:
	AUTHUB_GAS2025Character();
		
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual void AddTag(const FGameplayTag& InTag) override;
	virtual void RemoveTag(const FGameplayTag& InTag) override;

	UFUNCTION(CallInEditor)
	void ApplyGameplayEffect();
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ActiveEventTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer GameplayStates; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameplayBaseStateTags* CharacterStates;

protected:

	virtual void BeginPlay() override;

	virtual void SetupAttributeCallbacks();
	
	virtual void PreInitializeComponents() override;
	
	virtual void Jump() override;
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UUTHUB_ASC* ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UGASDataComponent* GASDataComponent;
	
private:

	void InitializeCharacter();
};

