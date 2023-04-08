// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/GCObject.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"

class FSimpleAssetPreviewScene;
class SSimpleAssetViewport;
class USimpleAsset;
/**
 * 
 */
class FSimpleAssetEditorToolkit : public FAssetEditorToolkit, public FNotifyHook
{
public:
	FSimpleAssetEditorToolkit();
	virtual ~FSimpleAssetEditorToolkit() override;

	void InitAssetEditor(
		const EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost,
		USimpleAsset* InSimpleAsset);

	/* Simple Asset Editor methods */
	void BindCommands();
	void ExtendToolbars();
	void FocusViewport() const;
	TSharedPtr<FSimpleAssetPreviewScene> CreatePreviewScene();
	/* End Simple Asset Editor methods */
	
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	/** IToolkit interface */
	virtual FName GetToolkitFName() const override { return "SimpleAssetEditor"; };
	virtual FText GetBaseToolkitName() const override { return INVTEXT("Simple Asset Editor"); };
	virtual FString GetWorldCentricTabPrefix() const override { return "Simple Asset "; };
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; };
	/** End IToolkit interface */
	
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args) const;

private:

	USimpleAsset* SimpleAsset;
	TSharedPtr<FSimpleAssetPreviewScene> PreviewScene;
	TSharedPtr<SSimpleAssetViewport> PreviewViewportWidget;
protected:
	void OnClose() override;

};
