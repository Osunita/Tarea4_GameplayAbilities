// Fill out your copyright notice in the Description page of Project Settings.

#include "UTHUB_ASC.h"

#include "CoreAttributeSet.h"
#include "NativeGameplayTags.h"
#include "DataDriven/GASDataComponent.h"

// Sets default values for this component's properties
UUTHUB_ASC::UUTHUB_ASC()
{
	// Set this component to be initialized when the game starts, and to be ticked
	// every frame.  You can turn these features off to improve performance if you
	// don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UUTHUB_ASC::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo(GetOwner(), GetOwner());

	// InitializeAttributes(GetOwner());
}

void UUTHUB_ASC::InitializeAttributes(AActor* InOwnerActor)
{
	if (UCoreAttributeSet* CoreAttributes = GetAttributeSetFromOwner<UCoreAttributeSet>())
	{
		if (UGASDataComponent* DataComponent = InOwnerActor->FindComponentByClass<UGASDataComponent>())
		{
			if(DataComponent->DT_CoreStats)
			{
				// UCoreAttributeSet* CoreSet = const_cast<UCoreAttributeSet*>(GetSet<UCoreAttributeSet>());			
				auto InitializeAttribute = [this, CoreAttributes](const FName& RowName, const FGameplayCoreAttribute& Row)
				{
					float NewValue = Row.AttributeBaseValue;
					Row.Attribute.SetNumericValueChecked(NewValue, CoreAttributes);
				};
			
				DataComponent->DT_CoreStats->ForeachRow<FGameplayCoreAttribute>(TEXT(""), InitializeAttribute);
			}
		}
	}
}

void UUTHUB_ASC::ApplyEffectFromClass(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle Spec = MakeOutgoingSpec(EffectClass, 1, EffectContext);
	
	ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
}

void UUTHUB_ASC::InitializeAttributesFromEffects()
{
	// Init attributes
	if(UGASDataComponent* DataComponent = GetOwner()->FindComponentByClass<UGASDataComponent>())
	{
		for (const auto& EffectClass : DataComponent->AttributeInitializers)
		{
			ApplyEffectFromClass(EffectClass);
		}
	}
}

void UUTHUB_ASC::AddAbilityFromClass(const TSubclassOf<UGameplayAbility>& InGameplayAbilityClass)
{
	FGameplayAbilitySpec Spec(InGameplayAbilityClass, 1,0);
	GiveAbility(Spec);
}

void UUTHUB_ASC::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	InitializeAttributesFromEffects();

	UGASDataComponent* DataComponent = GetOwner()->FindComponentByClass<UGASDataComponent>();
	if(DataComponent)
	{
		AddAbilityFromClass(DataComponent->DefaultAbility);
	}
	
	// INIT EFFECT
	// INI ATTRIBS
	// INIT SKILLS
}

// Called every frame
void UUTHUB_ASC::TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
