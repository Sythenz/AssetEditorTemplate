// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetTypeActions/SimpleAssetTypeActions.h"
#include "AssetEditor/SimpleAssetEditorToolkit.h"
#include "SimpleAsset.h"

UClass* FSimpleAssetTypeActions::GetSupportedClass() const
{
	return USimpleAsset::StaticClass();
}

void FSimpleAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode =
		EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (USimpleAsset* PoseSearchDb = Cast<USimpleAsset>(*ObjIt))
		{
			const TSharedRef<FSimpleAssetEditorToolkit> NewEditor(new FSimpleAssetEditorToolkit());
			NewEditor->InitAssetEditor(Mode, EditWithinLevelEditor, PoseSearchDb);
		}
	}
}
