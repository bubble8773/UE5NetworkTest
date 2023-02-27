// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkedAbilityTestGameMode.generated.h"

UCLASS(minimalapi)
class ANetworkedAbilityTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANetworkedAbilityTestGameMode();
	UFUNCTION(BlueprintCallable)
	void FillWorld(TSubclassOf <AActor> ActorToSpawn, int max, FVector Origin, float radius);

	UFUNCTION(BlueprintCallable)
	int GetCurrentActor_p();
	UFUNCTION(BlueprintCallable)
	void SetCurrentActor_p(int value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = UI)
	int MaxActors;

private:
	//UPROPERTY( Replicated, Category = UI)
	int CurrentActors;
};



