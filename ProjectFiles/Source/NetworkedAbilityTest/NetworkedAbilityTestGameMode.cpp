// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetworkedAbilityTestGameMode.h"
#include "NetworkedAbilityTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"
#include "NavigationSystem.h"
#include "AbstractNavData.h"
using namespace FNavigationSystem;
#include "Kismet/KismetMathLibrary.h"

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
		ParallelFor(ActorsToSpawn.Num(), [&](int32 i) {

			if (navSystem->GetRandomReachablePointInRadius(Origin, radius, result)) {
				
				ActorsToSpawn[i]->SetActorLocation(result.Location);
				
			}
		});*/
		for (int i = 0; i <= max - 1; i++)
		{
			if (navSystem->GetRandomReachablePointInRadius(Origin, radius, result)) {
				ActorsToSpawn.Add(
				GetWorld()->SpawnActor<AActor>(ActorToSpawn)); //FTransform(FRotator::Euler(), result.Location, FVector::One));
				ActorsToSpawn[i]->SetReplicates(true);
				ActorsToSpawn[i]->SetReplicateMovement(true);
				ActorsToSpawn[i]->SetActorLocation(result.Location);
			}
		}
	}

}

bool ANetworkedAbilityTestGameMode::RenderBasedOnDistance(FVector PlayerLocation)
{
	ParallelFor(ActorsToSpawn.Num(), [&](int32 i) {
		//for(int i = 0; i <= ActorsToSpawn.Num()-1; i++)
		double distance = FVector::Distance(PlayerLocation, ActorsToSpawn[i]->GetActorLocation());
		ActorsToSpawn[i]->SetActorHiddenInGame(distance > ViewDistance);
		if (distance < 10)
			bIsHiddenByDistance = distance > ViewDistance;
		
	});
	return bIsHiddenByDistance;
}

void ANetworkedAbilityTestGameMode::ControlNonNPC(float Speed, float DeltaSeconds)
{
	if (!ActorsToSpawn.IsEmpty()) {
		FVector NewDir;
		//bool bFoundNewLocation = false;
		float lookAheadDistance = 50;
		UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());//UNavigationSystemV1::GetCurrent(GetWorld());
		FNavLocation result = FNavLocation(ActorsToSpawn[0]->GetActorLocation());
		if (navSystem) {
			ParallelFor(ActorsToSpawn.Num(), [&](int32 i) {
				NewDir = UKismetMathLibrary::RandomUnitVector();
				//FVector(FMath::FRandRange(-1, 1), FMath::FRandRange(-1, 1), 0).GetSafeNormal();
				FVector TestLocation = ActorsToSpawn[i]->GetActorLocation() + NewDir * lookAheadDistance;

				if (navSystem->ProjectPointToNavigation(TestLocation, result))
				{
					//bFoundNewLocation = true;
					ActorsToSpawn[i]->AddActorWorldRotation(NewDir.ToOrientationQuat());
					ActorsToSpawn[i]->AddActorWorldOffset(ActorsToSpawn[i]->GetActorLocation() + ActorsToSpawn[i]->GetActorForwardVector() * Speed * DeltaSeconds);
						//SetActorLocationAndRotation(ActorsToSpawn[i]->GetActorLocation() + ActorsToSpawn[i]->GetActorForwardVector() * Speed * DeltaSeconds,
						//NewDir.ToOrientationQuat());
					/*ActorsToSpawn[i]->SetActorRotation(NewDir.ToOrientationQuat());
					ActorsToSpawn[i]->SetActorLocation(ActorsToSpawn[i]->GetActorLocation() + ActorsToSpawn[i]->GetActorForwardVector() * Speed * DeltaSeconds);*/
				}

				//if (!bFoundNewLocation)
				//{
				//	// If we couldn't find a valid direction, keep the previous direction
				//	NewDir = ActorsToSpawn[i]->GetActorForwardVector();
				//}

				//ActorsToSpawn[i]->SetActorRotation(NewDir.ToOrientationQuat());
				//ActorsToSpawn[i]->SetActorLocation(ActorsToSpawn[i]->GetActorLocation() + ActorsToSpawn[i]->GetActorForwardVector() * Speed * DeltaSeconds);
				},false);
		}
	}
}
