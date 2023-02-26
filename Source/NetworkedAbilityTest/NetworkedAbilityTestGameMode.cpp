// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetworkedAbilityTestGameMode.h"
#include "NetworkedAbilityTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
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
	FTransform SpawnTransform;
	if (navSystem){
		for (int i = 0; i <= max-1; i++)
		{
			if (navSystem->GetRandomReachablePointInRadius(Origin, radius, result)) {
				SpawnTransform.SetLocation(result.Location);
				SpawnTransform.SetRotation(FQuat::Identity);
				SpawnTransform.SetScale3D(FVector::One());
				GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform);
			}
		}
	}
	
}

