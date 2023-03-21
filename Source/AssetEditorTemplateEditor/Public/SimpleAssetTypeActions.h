// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class ASSETEDITORTEMPLATEEDITOR_API FSimpleAssetTypeActions : public FAssetTypeActions_Base
{
public:
	// IAssetTypeActions Implementation
	virtual FText GetName() const override
	{
		return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_SimpleAsset", "Simple Asset");
	}
	virtual FColor GetTypeColor() const override
	{
		return FColor(255,192,128);
	}
	virtual uint32 GetCategories() override
	{
		return EAssetTypeCategories::Misc;
	}
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;
};
