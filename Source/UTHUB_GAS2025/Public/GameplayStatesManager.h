#pragma once
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"


class FGameplayStatesManager : public FNoncopyable 
{
	static FGameplayStatesManager* Singleton;

public:
	
	// Lazy load
	static FGameplayStatesManager& Get()
	{
		if (!Singleton)
			Singleton = new FGameplayStatesManager();

		return *Singleton;
	}

	void InitGameplayTags()
	{
		Tag_InteractEnabled = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GameStates.CanInteract"));
	}

public:

	FGameplayTag Tag_InteractEnabled;	
};
