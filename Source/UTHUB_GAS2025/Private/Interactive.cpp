// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive.h"

#include "GameplayStatesManager.h"
#include "UTHUB_GAS2025/UTHUB_GAS2025Character.h"


// Sets default values
AInteractive::AInteractive()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractive::CheckTagCondition(AActor* TagOwner)
{
	if (UUTHUB_ASC* ASC = TagOwner->FindComponentByClass<UUTHUB_ASC>())
	{		
		ASC->AddLooseGameplayTag(ConditionTag);
	}
	
	// if (IGameplayTagAssetInterface* TagAssetInterface = Cast<IGameplayTagAssetInterface>(TagOwner))
	// {
	// 	FGameplayTagContainer CharacterTags;
	// 	TagAssetInterface->GetOwnedGameplayTags(CharacterTags);
	// 	
	// 	if(!CharacterTags.HasTag(FGameplayStatesManager::Get().Tag_InteractEnabled)) return; 
	//
	// 	if (CharacterTags.HasTag(ConditionTag))
	// 	{
	// 		ExecuteAction();
	// 	}
	// }
}

// Called when the game starts or when spawned
void AInteractive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

