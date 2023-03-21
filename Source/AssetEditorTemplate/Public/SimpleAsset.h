// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SimpleAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ASSETEDITORTEMPLATE_API USimpleAsset : public UObject
{
	GENERATED_BODY()
	
public:
	USimpleAsset();
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* PreviewMesh;
	
};
