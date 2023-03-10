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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	int MaxActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actors)
	int CollectedActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actors)
	double ViewDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actors)
	TArray<AActor*> ActorsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actors)
	bool bIsHiddenByDistance;

	UFUNCTION(BlueprintCallable)
	void FillWorld(TSubclassOf <AActor> ActorToSpawn, int max, FVector Origin, float radius);
	
	UFUNCTION(BlueprintCallable)
	bool RenderBasedOnDistance(FVector PlayerLocation);
		
	UFUNCTION(BlueprintCallable)
	void ControlNonNPC(float Speed, float DeltaSeconds);

};



