// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureAIController.h"
#include "NavigationSystem.h"
#include "AbstractNavData.h"
using namespace FNavigationSystem;

void ACreatureAIController::BeginPlay()
{
	RunBehaviorTree(BT_CreatureRef);
	
}

void ACreatureAIController::MoveMeToLocation()
{
	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());//UNavigationSystemV1::GetCurrent(GetWorld());
	FVector Origin = this->K2_GetActorLocation();
	FNavLocation result = FNavLocation(Origin);
	FTransform SpawnTransform;
	if (navSystem) {
		if (navSystem->GetRandomReachablePointInRadius(Origin, 100.0f, result)) {
			auto moveRes = MoveToLocation(result.Location,5);
		}
	}
}
