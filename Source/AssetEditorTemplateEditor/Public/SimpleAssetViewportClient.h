// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "Editor/UnrealEd/Public/SCommonEditorViewportToolbarBase.h"

/**
 * 
 */
class FSimpleAssetViewportClient : public FEditorViewportClient
{
public:
	FSimpleAssetViewportClient(int32 InTabIndex);
	
	// FViewportClient interface
	virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;
	// End of FViewportClient interface

	// FEditorViewportClient interface
	virtual FLinearColor GetBackgroundColor() const override;
	// End of FEditorViewportClient interface
	
	void SetOwnerWidget(const TWeakPtr<SEditorViewport> OwnerPtr)
	{
		EditorViewportWidget = OwnerPtr;
	}

	void ResetCameraView();
	
private:
	int32 TabIndex;

	// The preview scene
	FPreviewScene OwnedPreviewScene;

	FAssetData SourceWorldAsset;
	FLinearColor MyBGColor;
};
