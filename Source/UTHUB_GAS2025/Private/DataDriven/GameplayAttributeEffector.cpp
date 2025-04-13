// Fill out your copyright notice in the Description page of Project Settings.


#include "DataDriven/GameplayAttributeEffector.h"

#include "CoreAttributeSet.h"
#include "GameplayEffectExtension.h"

void UGameplayAttributeEffector::ApplyAttributeEffector(const FOnAttributeChangeData& InChangeData)
{
	// InChangeData.GEModData->EffectSpec.GetContext().GetSourceObject()
	ReceiveApplyAttributeEffector(InChangeData.GEModData->Target.GetOwner());
}
