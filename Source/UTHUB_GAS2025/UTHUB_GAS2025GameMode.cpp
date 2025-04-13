// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GAS2025GameMode.h"

#include "GameplayStatesManager.h"
#include "UTHUB_GAS2025PlayerController.h"
#include "UTHUB_GAS2025Character.h"
#include "UObject/ConstructorHelpers.h"

AUTHUB_GAS2025GameMode::AUTHUB_GAS2025GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUTHUB_GAS2025PlayerController::StaticClass();
		
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AUTHUB_GAS2025GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	
	APawn* PlayerPawn = NewPlayer->GetPawn();
	ensureMsgf(PlayerPawn, TEXT("%s We don't have a proper pawn initialized yet... Oh boy"), ANSI_TO_TCHAR(__FUNCTION__));
	
	UUTHUB_ASC* ASC = PlayerPawn->FindComponentByClass<UUTHUB_ASC>();
	if (ASC)
	{
		auto& OnTagRegistered = ASC->RegisterGameplayTagEvent(FGameplayStatesManager::Get().Tag_InteractEnabled);
		Handle_TagAddedDelegate = OnTagRegistered.AddUObject(this, &ThisClass::CharacterIsAllowedToInteract);
	}
}

void AUTHUB_GAS2025GameMode::CharacterIsAllowedToInteract(const FGameplayTag GameplayTag, int Count)
{
	UE_LOG(LogTemp, Display, TEXT("Now I can interact!!!!"))
}

void AUTHUB_GAS2025GameMode::OnPlayerEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	if (UUTHUB_ASC* ASC = Actor->FindComponentByClass<UUTHUB_ASC>())
	{
		ASC->UnregisterGameplayTagEvent(Handle_TagAddedDelegate, FGameplayStatesManager::Get().Tag_InteractEnabled);
	}
}
