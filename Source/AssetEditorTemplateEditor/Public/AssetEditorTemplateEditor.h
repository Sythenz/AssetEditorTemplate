// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSimpleAssetTypeActions;

class FAssetEditorTemplateEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	virtual TSharedPtr<class FExtensibilityManager> GetEditorToolbarExtensibilityManager() { return ToolbarExtensibilityManager; }

private:
	TSharedPtr<FSimpleAssetTypeActions> SimpleAssetTypeActions;
	TSharedPtr<FExtensibilityManager> ToolbarExtensibilityManager;
};
