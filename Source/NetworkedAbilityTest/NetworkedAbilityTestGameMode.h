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
	void FillWorld(TSubclassOf< AActor> ActorToSpawn, int max, FVector Origin, float radius);
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = UI)
		int maxActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = UI)
		int currentActors;*/
};



