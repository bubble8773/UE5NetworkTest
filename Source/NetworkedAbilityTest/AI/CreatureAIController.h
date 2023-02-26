// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CreatureAIController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKEDABILITYTEST_API ACreatureAIController : public AAIController
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, Category = BehaviorTree, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BT_CreatureRef;
protected:
	virtual void BeginPlay();

public:
	UFUNCTION(BlueprintCallable)
	void MoveMeToLocation();
};
