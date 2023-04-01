// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetEditor/SimpleAssetViewport.h"

#include "SimpleAsset.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#include "AssetEditor/SimpleAssetPreviewScene.h"
#include "AssetEditor/SimpleAssetViewportClient.h"
#include "CompGeom/DiTOrientedBox.h"

//Just create the advnaced preview scene and initiate components
SSimpleAssetViewport::SSimpleAssetViewport() : PreviewScene(MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues())))
{

}

SSimpleAssetViewport::~SSimpleAssetViewport()
{
	if (TypedViewportClient.IsValid())
	{
		TypedViewportClient->Viewport = nullptr;
	}
}

TSharedRef<class SEditorViewport> SSimpleAssetViewport::GetViewportWidget()
{
	return SharedThis(this);
}
TSharedPtr<FExtender> SSimpleAssetViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}
void SSimpleAssetViewport::OnFloatingButtonClicked()
{
	// Nothing
}

void SSimpleAssetViewport::OnFocusViewportToSelection()
{
	SEditorViewport::OnFocusViewportToSelection();
	
	/* TODO: Replace with PreviewMeshComponent->Bounds */
	const FBoxSphereBounds Bounds = FBoxSphereBounds();
	TypedViewportClient->FocusViewportOnBounds( Bounds, false );
}

void SSimpleAssetViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<FEditorViewportClient> SSimpleAssetViewport::MakeEditorViewportClient()
{
	TypedViewportClient = MakeShareable(new FSimpleAssetViewportClient(SharedThis(this), PreviewScene.ToSharedRef()));
	return TypedViewportClient.ToSharedRef();
}

