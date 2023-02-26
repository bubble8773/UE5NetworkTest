// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractWithObjects.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteractWithObjects : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NETWORKEDABILITYTEST_API IIInteractWithObjects
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Interact();
};
