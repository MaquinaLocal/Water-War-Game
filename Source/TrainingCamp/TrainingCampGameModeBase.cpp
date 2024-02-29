// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrainingCampGameModeBase.h"
#include "Character/CharacterBase.h"

ATrainingCampGameModeBase::ATrainingCampGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BPs/FP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
