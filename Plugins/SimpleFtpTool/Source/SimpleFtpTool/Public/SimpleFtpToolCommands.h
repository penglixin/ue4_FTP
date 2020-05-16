// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SimpleFtpToolStyle.h"

class FSimpleFtpToolCommands : public TCommands<FSimpleFtpToolCommands>
{
public:

	FSimpleFtpToolCommands()
		: TCommands<FSimpleFtpToolCommands>(TEXT("SimpleFtpTool"), NSLOCTEXT("Contexts", "SimpleFtpTool", "SimpleFtpTool Plugin"), NAME_None, FSimpleFtpToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};