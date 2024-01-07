#pragma once
#include "CoreMinimal.h"
#include "FConductivityModStruct.h"
#include "ILightningConductor.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class ULightningConductor : public UInterface {
	GENERATED_BODY()
};

class LONGLOSTLIGHTNING_API ILightningConductor {
	GENERATED_BODY()

public:
	ILightningConductor();

	TArray<ILightningConductor*> NearbyConductors;
	int32 BaseConductivity;
	float Conductivity;
	int32 ConductivitySharedValue;
	int32 NearbyConductivity;
	int32 HeightValue;
	int32 FloorIncrementValue;
	int32 FloorHeight;
	bool IsPlayer;

	bool operator <(const ILightningConductor& OtherConductor) const { 
		if (Conductivity > OtherConductor.Conductivity) return true;
		return false;
	}
	
	TObjectPtr<AActor> ClassReference;
	
	void SetClassReference(TObjectPtr<AActor> Self);
	
	virtual void SetBaseConductivity(int32 ConductivityValue);
	virtual void SetSharedValue(int32 SharedValue);
	virtual void SetModifier(EModifier NewModifier);
	virtual void SetFloorHeight(int32 FloorHeightValue);
	virtual void SetFloorIncrementValue(int32 IncrementValue);
	virtual bool IsPlayerConductor();
	virtual EModifier GetModifier();
	virtual int32 GetBaseConductivity();
	virtual float CalculateConductivity();
	virtual void CalculateHeightValue(float ActorZ);
	virtual void AddNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor);
	virtual void RemoveNearbyConductor(TScriptInterface<ILightningConductor> OtherConductor);

protected:
	EModifier CurrentModifier;
	const float FloorOffset = 5.0;
};
