// Fill out your copyright notice in the Description page of Project Settings.


#include "LongLostLightning/Public/ILightningConductor.h"
#include "LongLostLightning/Public/FConductivityModStruct.h"

ILightningConductor::ILightningConductor(): BaseConductivity(0),
											Conductivity(0),
											ConductivitySharedValue(0),
                                            NearbyConductivity(0),
											HeightValue(0),
                                            IsPlayer(false) {
	CurrentModifier = EModifier::None;
	FloorIncrementValue = 5;
	FloorHeight = 100;
}

void ILightningConductor::SetClassReference(const TObjectPtr<AActor> Self) {
	ClassReference = Self;
}

void ILightningConductor::SetBaseConductivity(const int32 ConductivityValue) {
	BaseConductivity = ConductivityValue;
}

void ILightningConductor::SetSharedValue(const int32 SharedValue) {
	ConductivitySharedValue = SharedValue;
}

void ILightningConductor::SetModifier(const EModifier NewModifier) {
	CurrentModifier = NewModifier;
}

void ILightningConductor::SetFloorHeight(const int32 FloorHeightValue) {
	FloorHeight = FloorHeightValue;
}

void ILightningConductor::SetFloorIncrementValue(const int32 IncrementValue) {
	FloorIncrementValue = IncrementValue;
}

bool ILightningConductor::IsPlayerConductor() {
	return IsPlayer;
}

EModifier ILightningConductor::GetModifier() {
	return CurrentModifier;
}

int32 ILightningConductor::GetBaseConductivity() {
	return BaseConductivity;
}



float ILightningConductor::CalculateConductivity() {
	CalculateHeightValue(ClassReference->GetActorLocation().Z);
	if (static_cast<uint8>(CurrentModifier) == 0) {
		Conductivity = BaseConductivity + HeightValue + NearbyConductivity;
		return Conductivity;
	}
	Conductivity = BaseConductivity * static_cast<float>(static_cast<uint8>(CurrentModifier))
	/ 10 + HeightValue + NearbyConductivity;
	return Conductivity;
}

void ILightningConductor::CalculateHeightValue(const float ActorZ) {
	if (FloorHeight == 0) return;

	const int32 MidBounds = FMath::FloorToInt(ActorZ / FloorHeight);
	const int32 UpperBounds = FMath::FloorToInt((ActorZ + FloorOffset) / FloorHeight);
	if (MidBounds == UpperBounds) HeightValue = MidBounds * FloorIncrementValue; 
	else HeightValue = UpperBounds * FloorIncrementValue; 
}

void ILightningConductor::AddNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor) {
	ILightningConductor* OtherInterface = OtherConductor.GetInterface();
	if (!NearbyConductors.Contains(OtherInterface)) {
		NearbyConductors.Add(OtherInterface);
		NearbyConductivity += OtherInterface->ConductivitySharedValue;
	}
}

void ILightningConductor::RemoveNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor) {
	ILightningConductor* OtherInterface = OtherConductor.GetInterface();
	if (NearbyConductors.Contains(OtherInterface)) {
		NearbyConductors.Remove(OtherInterface);
		NearbyConductivity -= OtherInterface->ConductivitySharedValue;
	}
}
