// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAssetPreviewScene.h"

#include "GameFramework/WorldSettings.h"

FSimpleAssetPreviewScene::FSimpleAssetPreviewScene(ConstructionValues CVS, const TSharedRef<FSimpleAssetEditorToolkit>& EditorToolkit)
	: FAdvancedPreviewScene(CVS)
	, EditorPtr(EditorToolkit)
{
	// Disable killing actors outside of the world
	AWorldSettings* WorldSettings = GetWorld()->GetWorldSettings(true);
	WorldSettings->bEnableWorldBoundsChecks = false;
}

FSimpleAssetPreviewScene::~FSimpleAssetPreviewScene()
{
	
}

void FSimpleAssetPreviewScene::Tick(float InDeltaTime)
{
	FAdvancedPreviewScene::Tick(InDeltaTime);

	
}
