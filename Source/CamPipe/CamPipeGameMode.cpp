// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CamPipeGameMode.h"
#include "CamPipePawn.h"
#include "CamPipeHud.h"

ACamPipeGameMode::ACamPipeGameMode()
{
	DefaultPawnClass = ACamPipePawn::StaticClass();
	HUDClass = ACamPipeHud::StaticClass();
}
