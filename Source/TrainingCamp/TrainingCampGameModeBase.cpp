// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrainingCampGameModeBase.h"
#include "Character/CharacterBase.h"

ATrainingCampGameModeBase::ATrainingCampGameModeBase()
{
	DefaultPawnClass = ACharacterBase::StaticClass();
}
