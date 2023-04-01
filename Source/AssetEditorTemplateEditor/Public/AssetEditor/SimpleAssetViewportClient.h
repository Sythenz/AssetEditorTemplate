// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "Editor/UnrealEd/Public/SCommonEditorViewportToolbarBase.h"

class FSimpleAssetPreviewScene;
class FSimpleAssetEditorToolkit;
class SSimpleAssetViewport;
/**
 * 
 */
class FSimpleAssetViewportClient : public FEditorViewportClient
{
public:

	/** Pointer back to the Editor Viewport */
	TWeakPtr<class SEditorViewport> ViewportPtr;

	//Constructor and destructor
	FSimpleAssetViewportClient(const TSharedRef<SEditorViewport>& InThumbnailViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);

	/** Stored pointer to the preview scene in which the static mesh is shown */
	FAdvancedPreviewScene* AdvancedPreviewScene;
};
