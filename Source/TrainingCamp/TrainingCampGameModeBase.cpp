// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrainingCampGameModeBase.h"
#include "Character/CharacterBase.h"
#include "FirstPersonPC.h"

ATrainingCampGameModeBase::ATrainingCampGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BPs/BP_PistolCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass = AFirstPersonPC::StaticClass();
}
