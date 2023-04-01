// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetEditorTemplateCommands.h"
#include "InputCoreTypes.h"

#define LOCTEXT_NAMESPACE "FAssetEditorTemplateCommands"

void FAssetEditorTemplateCommands::RegisterCommands()
{
	UI_COMMAND(FocusViewport, "Focus Viewport", "Focus Viewport on Mesh", EUserInterfaceActionType::Button, FInputChord(EKeys::F));
}

#undef LOCTEXT_NAMESPACE