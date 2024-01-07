// Fill out your copyright notice in the Description page of Project Settings.


#include "MetalBox.h"

// Sets default values
AMetalBox::AMetalBox() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>("BoxMesh");
	SetClassReference(this);
	SetRootComponent(BoxMesh);
}

void AMetalBox::SetModifier(EModifier NewModifier) {
	ILightningConductor::SetModifier(NewModifier);
}

EModifier AMetalBox::GetModifier() {
	return ILightningConductor::GetModifier();
}

int32 AMetalBox::GetBaseConductivity() {
	return ILightningConductor::GetBaseConductivity();
}

float AMetalBox::CalculateConductivity() {
	ILightningConductor::CalculateHeightValue(GetActorLocation().Z);
	return ILightningConductor::CalculateConductivity();
}

void AMetalBox::SetBaseConductivity(int32 ConductivityValue) {
	ILightningConductor::SetBaseConductivity(ConductivityValue);
}

void AMetalBox::SetFloorIncrementValue(int32 IncrementValue) {
	ILightningConductor::SetFloorIncrementValue(IncrementValue);
}

void AMetalBox::AddNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor) {
	ILightningConductor::AddNearbyConductor(OtherConductor);
}

void AMetalBox::RemoveNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor) {
	ILightningConductor::RemoveNearbyConductor(OtherConductor);
}

// void AMetalBox::OnLightningStrike_Implementation() {
// 	IEventInitiator::OnLightningStrike_Implementation();
// }

// Called when the game starts or when spawned
void AMetalBox::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AMetalBox::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
