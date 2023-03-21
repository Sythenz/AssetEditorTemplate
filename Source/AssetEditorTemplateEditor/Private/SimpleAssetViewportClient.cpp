// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAssetViewportClient.h"

FSimpleAssetViewportClient::FSimpleAssetViewportClient(int32 InTabIndex)
	: FEditorViewportClient(nullptr, nullptr, nullptr)
{
	SetViewModes(VMI_Lit, VMI_Lit);
	
	MyBGColor = FLinearColor::Black;

	SetRealtime(false);

	PreviewScene = &OwnedPreviewScene;

	EngineShowFlags.Selection = true;
	EngineShowFlags.SelectionOutline = true;
	EngineShowFlags.Grid = false;
}

bool FSimpleAssetViewportClient::InputKey(const FInputKeyEventArgs& InEventArgs)
{
	return FEditorViewportClient::InputKey(InEventArgs);
}

FLinearColor FSimpleAssetViewportClient::GetBackgroundColor() const
{
	return FEditorViewportClient::GetBackgroundColor();
}

void FSimpleAssetViewportClient::ResetCameraView()
{
	UWorld* World = OwnedPreviewScene.GetWorld();

	if (World->EditorViews.IsValidIndex(GetViewportType()))
	{
		FLevelViewportInfo& ViewportInfo = World->EditorViews[GetViewportType()];
		SetInitialViewTransform(
			GetViewportType(),
			ViewportInfo.CamPosition,
			ViewportInfo.CamRotation,
			ViewportInfo.CamOrthoZoom);
	}
}
