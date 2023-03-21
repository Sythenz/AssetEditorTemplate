// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAssetFactory.h"
#include "SimpleAsset.h"

USimpleAssetFactory::USimpleAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = USimpleAsset::StaticClass();
	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* USimpleAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<USimpleAsset>(InParent, Name, Flags);
}
