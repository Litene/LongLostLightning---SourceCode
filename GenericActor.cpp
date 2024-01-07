// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericActor.h"
#include "EngineUtils.h"
#include "LongLostLightning/MusicManager.h"

// Sets default values
AGenericActor::AGenericActor() {
	PrimaryActorTick.bCanEverTick = true;
	SetClassReference(this);
}

void AGenericActor::SetModifier(EModifier NewModifier) {
	ILightningConductor::SetModifier(NewModifier);
}

EModifier AGenericActor::GetModifier() {
	return ILightningConductor::GetModifier();
}

int32 AGenericActor::GetBaseConductivity() {
	return ILightningConductor::GetBaseConductivity();
}

float AGenericActor::CalculateConductivity() {
	ILightningConductor::CalculateHeightValue(GetActorLocation().Z);
	return ILightningConductor::CalculateConductivity();
}

void AGenericActor::SetBaseConductivity(int32 ConductivityValue) {
	ILightningConductor::SetBaseConductivity(ConductivityValue);
}

void AGenericActor::SetFloorIncrementValue(int32 IncrementValue) {
	ILightningConductor::SetFloorIncrementValue(IncrementValue);
}

void AGenericActor::SetFloorHeight(int32 FloorHeightValue) {
	ILightningConductor::SetFloorHeight(FloorHeightValue);
}

void AGenericActor::AddNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor) {
	ILightningConductor::AddNearbyConductor(OtherConductor);
}

void AGenericActor::RemoveNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor) {
	ILightningConductor::RemoveNearbyConductor(OtherConductor);
}

void AGenericActor::SetSharedValue(int32 SharedValue) {
	ILightningConductor::SetSharedValue(SharedValue);
}

void AGenericActor::ChanceModifier(int PercentChance, TEnumAsByte<EOutcomePins>& Outcome) {
	IEventInitiator::ChanceModifier(PercentChance, Outcome);
}

void AGenericActor::RepeatingModifier(int TimesToRepeat, float TimeInBetween) {
	IEventInitiator::RepeatingModifier(TimesToRepeat, TimeInBetween);
}

void AGenericActor::OnCalled_Implementation(AGenericActor* CallingActor) {
	IEventListener::OnCalled_Implementation(CallingActor);
}

void AGenericActor::OnUnsubscribe_Implementation(AGenericActor* CallingActor) {
	IEventListener::OnUnsubscribe_Implementation(CallingActor);
}

void AGenericActor::OnNoStormMusic_Implementation() {
	IEventListener::OnNoStormMusic_Implementation();
}

void AGenericActor::OnLowStormMusic_Implementation() {
	IEventListener::OnLowStormMusic_Implementation();
}

void AGenericActor::OnMediumStormMusic_Implementation() {
	IEventListener::OnMediumStormMusic_Implementation();
}

void AGenericActor::OnHighStormMusic_Implementation() {
	IEventListener::OnHighStormMusic_Implementation();
}

void AGenericActor::SetProperties(bool Conductor, bool Initiator, bool Listener) {
	ConductorActive = Conductor;
	EventListenerActivated = Listener;
	EventInitiatorActivated = Initiator;
}

void AGenericActor::BeginPlay() {
	Super::BeginPlay();

	if (ObjectsToAffectRef.Num() > 0) 
		for (auto ObjectToAffectRef : ObjectsToAffectRef) 
			ObjectsToAffect.Add(TScriptInterface<IEventListener>(ObjectToAffectRef));
	
	for (TActorIterator<AMusicManager> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator) 
		MusicListenerActor = *ActorIterator;
	
	MusicEventListener = TScriptInterface<IEventListener>(MusicListenerActor);
}

void AGenericActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
