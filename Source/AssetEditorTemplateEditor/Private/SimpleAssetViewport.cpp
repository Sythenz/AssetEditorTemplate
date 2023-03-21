// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAssetViewport.h"

#include "SimpleAsset.h"
#include "SimpleAssetViewportClient.h"

SSimpleAssetViewport::~SSimpleAssetViewport()
{
	TypedViewportClient = nullptr;
}

void SSimpleAssetViewport::Construct(const FArguments& InArgs, const FSimpleAssetViewportRequiredArgs& InRequiredArgs)
{
	TypedViewportClient = MakeShareable(new FSimpleAssetViewportClient(TabIndex));
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedPtr<SWidget> SSimpleAssetViewport::MakeViewportToolbar()
{
	return SEditorViewport::MakeViewportToolbar();
}

TSharedRef<FEditorViewportClient> SSimpleAssetViewport::MakeEditorViewportClient()
{
	return TypedViewportClient.ToSharedRef();
}

void SSimpleAssetViewport::BindCommands()
{
	SEditorViewport::BindCommands();
	TSharedRef<FSimpleAssetViewportClient> EditorViewportClientRef = TypedViewportClient.ToSharedRef();
	
}

void SSimpleAssetViewport::OnFocusViewportToSelection()
{
	SEditorViewport::OnFocusViewportToSelection();
}

TSharedRef<SEditorViewport> SSimpleAssetViewport::GetViewportWidget()
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
}
