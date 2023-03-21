// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetEditorTemplateEditor.h"

#include "SimpleAssetTypeActions.h"
#define LOCTEXT_NAMESPACE "FAssetEditorTemplateModule"

void FAssetEditorTemplateEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	SimpleAssetTypeActions = MakeShared<FSimpleAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(SimpleAssetTypeActions.ToSharedRef());
}

void FAssetEditorTemplateEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	if(!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(SimpleAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetEditorTemplateEditorModule, AssetEditorTemplateEditor)