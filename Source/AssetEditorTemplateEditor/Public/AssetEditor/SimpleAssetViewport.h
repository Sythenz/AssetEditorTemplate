// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"

class USimpleAsset;
class FSimpleAssetPreviewScene;
class FSimpleAssetEditorToolkit;

struct FSimpleAssetViewportRequiredArgs
{
	FSimpleAssetViewportRequiredArgs(const TSharedRef<class FSimpleAssetPreviewScene>& InPreviewScene, TSharedRef<class FAssetEditorToolkit> InAssetEditorToolkit, int32 InViewportIndex)
	: PreviewScene(InPreviewScene)
	, AssetEditorToolkit(InAssetEditorToolkit)
	, ViewportIndex(InViewportIndex)
	{
	}


	TSharedRef<class FSimpleAssetPreviewScene> PreviewScene;
	TSharedRef<class FAssetEditorToolkit> AssetEditorToolkit;
	int32 ViewportIndex;
};

class FSimpleAssetViewportClient;
/**
 * 
 */
class SSimpleAssetViewport : public SEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider
{
public:

	SLATE_BEGIN_ARGS(SSimpleAssetViewport) {}
	SLATE_END_ARGS()

	/** The scene for this viewport. */
	TSharedPtr<FSimpleAssetPreviewScene> PreviewScene;

	void Construct(const FArguments& InArgs, TSharedPtr<FSimpleAssetEditorToolkit> InShowcaseAssetEditor, TSharedPtr<FSimpleAssetPreviewScene> InPreviewScene);
	virtual ~SSimpleAssetViewport() override;

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override {}

	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
	
	virtual void OnFocusViewportToSelection() override;

	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

	TSharedPtr<class FSimpleAssetViewportClient> GetViewportClient() { return TypedViewportClient; };
	
	//Shared ptr to the client
	TSharedPtr<class FSimpleAssetViewportClient> TypedViewportClient;

	//Toolkit Pointer
	TSharedPtr<FSimpleAssetEditorToolkit> EditorPtr;
	
};
