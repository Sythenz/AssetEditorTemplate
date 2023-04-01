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

 virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
 virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

 virtual FName GetToolkitFName() const override { return "SimpleAssetEditor"; };
 virtual FText GetBaseToolkitName() const override { return INVTEXT("Simple Asset Editor"); };
 virtual FString GetWorldCentricTabPrefix() const override { return "Simple Asset "; };
 virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; };

 TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args) const;
 
private:
 
 USimpleAsset* SimpleAsset;
 TSharedPtr<FSimpleAssetPreviewScene> PreviewScene;
 TSharedPtr<SSimpleAssetViewport> PreviewWidget;
};
