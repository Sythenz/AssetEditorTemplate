// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Styling/AppStyle.h"
#include "Framework/Commands/Commands.h"
#include "Templates/SharedPointer.h"

class FUICommandInfo;

class FAssetEditorTemplateCommands : public TCommands<FAssetEditorTemplateCommands>
{
public:
	/** Constructor */
	FAssetEditorTemplateCommands() 
		: TCommands<FAssetEditorTemplateCommands>("AssetEditorTemplateEditor", NSLOCTEXT("Contexts", "AssetTemplateEditor", "Asset Editor Template Editor"), NAME_None, FAppStyle::GetAppStyleSetName())
	{
		
	}
	
	/** Focuses Viewport on Mesh */
	TSharedPtr<FUICommandInfo> FocusViewport;
	
	/** Initialize commands */
	virtual void RegisterCommands() override;
};
