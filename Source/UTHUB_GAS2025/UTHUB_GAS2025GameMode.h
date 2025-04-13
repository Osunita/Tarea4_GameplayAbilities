// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "UTHUB_GAS2025GameMode.generated.h"

UCLASS(minimalapi)
class AUTHUB_GAS2025GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUTHUB_GAS2025GameMode();

protected:
	UFUNCTION()
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:

	UFUNCTION()
	void CharacterIsAllowedToInteract(const FGameplayTag GameplayTag, int Count);

	void OnPlayerEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);
	
private:

	FDelegateHandle Handle_TagAddedDelegate;
	TArray<class UGameStates*> GameStates;
};



