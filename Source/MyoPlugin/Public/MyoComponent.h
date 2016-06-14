#pragma once

#include "MyoPluginPrivatePCH.h"
#include "MyoEnum.h"
#include "MyoComponent.generated.h"

//TODO: multicast delegates here

UCLASS(ClassGroup="Input Controller", meta=(BlueprintSpawnableComponent))
class MYOPLUGIN_API UMyoComponent : public UActorComponent //delegate here
{
	GENERATED_UCLASS_BODY()

public:

	//Callable Blueprint functions - Need to be defined for direct access
	/**
	* Check if Myo Hub is enabled, if its not it will remain so until restart.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = MyoFunctions)
	bool IsHubEnabled();

	/**
	* Set the Locking Policy of the Myo Hub see myo documentation for details.
	*/
	UFUNCTION(BlueprintCallable, Category = MyoFunctions)
	void SetLockingPolicy(TEnumAsByte<EMyoLockingPolicy> policy);

	//Convenience Methods - Get
	/**
	*	Obtain controller pointer to current left arm myo if attached, otherwise returns none.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = MyoFunctions)
	UMyoController* LeftMyo();

	/**
	*	Obtain controller pointer to current right arm myo if attached, otherwise returns none.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = MyoFunctions)
	UMyoController* RightMyo();
	
	/**
	*	Obtain controller pointer to any last paired myo, if you only have one myo and just want the primary myo, use this.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = MyoFunctions)
	UMyoController* PrimaryMyo();

	/**
	*	Utility function to convert between UE and Myo space, call this on raw values to get them back in Myo space.
	*/
	UFUNCTION(BlueprintCallable, Category = MyoUtilityFunctions)
	void ConvertToMyoOrientationSpace(FRotator orientation, FRotator& converted);

	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};