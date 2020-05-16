// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SimpleFtpToolCommands.h"

#define LOCTEXT_NAMESPACE "FSimpleFtpToolModule"

void FSimpleFtpToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "SimpleFtpTool", "Bring up SimpleFtpTool window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
