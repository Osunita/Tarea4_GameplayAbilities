// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GAS2025.h"

#include "GameplayStatesManager.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogUTHUB_GAS2025)
IMPLEMENT_MODULE(FUTHUB_GAS2025Module, UTHUBGASModule)

void FUTHUB_GAS2025Module::StartupModule()
{
	UGameplayTagsManager::OnLastChanceToAddNativeTags().AddLambda([]()
	{
		FGameplayStatesManager::Get().InitGameplayTags();		
	});	
}

void FUTHUB_GAS2025Module::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}
