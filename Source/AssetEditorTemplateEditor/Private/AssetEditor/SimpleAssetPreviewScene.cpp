// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetEditor/SimpleAssetPreviewScene.h"

#include "GameFramework/WorldSettings.h"

FSimpleAssetPreviewScene::FSimpleAssetPreviewScene(ConstructionValues CVS, const TSharedRef<FSimpleAssetEditorToolkit>& EditorToolkit)
	: FAdvancedPreviewScene(CVS)
	, EditorPtr(EditorToolkit)
{
	// Disable killing actors outside of the world
	AWorldSettings* WorldSettings = GetWorld()->GetWorldSettings(true);
	WorldSettings->bEnableWorldBoundsChecks = false;

	//Hide default floor
	SetFloorVisibility(false, false);

	UStaticMesh* PreviewMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EngineMeshes/Cube.Cube"), NULL, LOAD_None, NULL);
	FTransform PreviewMeshTransform (FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1.0f, 1.0f, 1.0f ));
	
	{
		PreviewComponent = NewObject<UStaticMeshComponent>(GetTransientPackage());
		PreviewComponent->SetStaticMesh(PreviewMesh);
		PreviewComponent->bSelectable = true;
		
		AddComponent(PreviewComponent, PreviewMeshTransform);
	}
}

FSimpleAssetPreviewScene::~FSimpleAssetPreviewScene()
{
	
}

void FSimpleAssetPreviewScene::Tick(float InDeltaTime)
{
	FAdvancedPreviewScene::Tick(InDeltaTime);

	
}
