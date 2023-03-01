// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetworkedAbilityTestGameMode.h"
#include "NetworkedAbilityTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"
#include "NavigationSystem.h"
#include "AbstractNavData.h"
using namespace FNavigationSystem;

ANetworkedAbilityTestGameMode::ANetworkedAbilityTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ANetworkedAbilityTestGameMode::FillWorld(TSubclassOf<AActor> ActorToSpawn, int max, FVector Origin, float radius)
{
	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());//UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation result = FNavLocation(Origin);
	
	if (navSystem) {

	
	/*	for (int i = 0; i < max; i++)
		{
			ActorsToSpawn.Add(GetWorld()->SpawnActor<AActor>(ActorToSpawn));
		}
		ParallelFor(ActorsToSpawn.Num(), [&](int32 Idx) {

			if (navSystem->GetRandomReachablePointInRadius(Origin, radius, result)) {
				
				ActorsToSpawn[Idx]->SetActorLocation(result.Location);
				
			}
		});*/
		for (int i = 0; i <= max - 1; i++)
		{
			if (navSystem->GetRandomReachablePointInRadius(Origin, radius, result)) {
				ActorsToSpawn.Add(
				GetWorld()->SpawnActor<AActor>(ActorToSpawn)); //FTransform(FRotator::Euler(), result.Location, FVector::One));
				ActorsToSpawn[i]->SetActorLocation(result.Location);
			}
		}
	}

}

void ANetworkedAbilityTestGameMode::RenderBasedOnDistance(FVector PlayerLocation)
{
	for(int i = 0; i <= ActorsToSpawn.Num()-1; i++)
	{
		double distance = FVector::Distance(PlayerLocation, ActorsToSpawn[i]->GetActorLocation());
		if ( distance > viewDistance)
		{
			ActorsToSpawn[i]->SetActorHiddenInGame(true);
		}
	}
}
