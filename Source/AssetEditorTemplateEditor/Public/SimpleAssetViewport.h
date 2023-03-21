// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"

class USimpleAsset;
class FSimpleAssetPreviewScene;
class FSimpleAssetEditorToolkit;

struct FSimpleAssetViewportRequiredArgs
{
	FSimpleAssetViewportRequiredArgs(
		const TSharedRef<FSimpleAssetEditorToolkit>& InAssetEditor,
		const TSharedRef<FSimpleAssetPreviewScene>& InPreviewScene)
		: AssetEditor(InAssetEditor)
		, PreviewScene(InPreviewScene)
	{
	}

	TSharedRef<FSimpleAssetEditorToolkit> AssetEditor;

	TSharedRef<FSimpleAssetPreviewScene> PreviewScene;
};

class FSimpleAssetViewportClient;
/**
 * 
 */
class SSimpleAssetViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(SSimpleAssetViewport) {}
	SLATE_END_ARGS()

	virtual ~SSimpleAssetViewport() override;
	
	void Construct(const FArguments& InArgs, const FSimpleAssetViewportRequiredArgs& InRequiredArgs);
	
	// SEditorViewport interface
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual void BindCommands() override;
	virtual void OnFocusViewportToSelection() override;
	// End of SEditorViewport interface

	// ICommonEditorViewportToolbarInfoProvider interface
	virtual TSharedRef<SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
	// End of ICommonEditorViewportToolbarInfoProvider interface
	
	TSharedPtr<FSimpleAssetViewportClient> TypedViewportClient;
	int32 TabIndex;
	
};
