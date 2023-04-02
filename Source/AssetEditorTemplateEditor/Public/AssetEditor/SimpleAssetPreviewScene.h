// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "SimpleAssetEditorToolkit.h"

/**
 * 
 */
class FSimpleAssetPreviewScene : public FAdvancedPreviewScene
{
public:
	FSimpleAssetPreviewScene(ConstructionValues CVS, const TSharedRef<FSimpleAssetEditorToolkit>& EditorToolkit);
	virtual ~FSimpleAssetPreviewScene() override;

	virtual void Tick(float InDeltaTime) override;

	TSharedRef<FSimpleAssetEditorToolkit> GetEditor() const
	{
		return EditorPtr.Pin().ToSharedRef();
	}

	UStaticMeshComponent* PreviewComponent = nullptr;
private:
	TWeakPtr<FSimpleAssetEditorToolkit> EditorPtr;
};
