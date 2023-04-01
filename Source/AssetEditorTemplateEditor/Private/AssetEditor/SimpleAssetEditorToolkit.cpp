// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetEditor/SimpleAssetEditorToolkit.h"

#include "SimpleAsset.h"
#include "AssetEditor/SimpleAssetPreviewScene.h"
#include "AssetEditor/SimpleAssetViewport.h"

#define LOCTEXT_NAMESPACE "SimpleAssetEditor"

FSimpleAssetEditorToolkit::FSimpleAssetEditorToolkit()
{
	
}

FSimpleAssetEditorToolkit::~FSimpleAssetEditorToolkit()
{
}

void FSimpleAssetEditorToolkit::InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, USimpleAsset* InSimpleAsset)
{
	SimpleAsset = Cast<USimpleAsset>(InSimpleAsset);
	
	// Create Preview Scene
	if (!PreviewScene.IsValid())
	{
		PreviewScene = MakeShareable(
			new FSimpleAssetPreviewScene(
				FPreviewScene::ConstructionValues()
				.AllowAudioPlayback(true)
				.ShouldSimulatePhysics(true)
				.ForceUseMovementComponentInNonGameWorld(true),
				StaticCastSharedRef<FSimpleAssetEditorToolkit>(AsShared())));
	}
	
	// Create viewport widget
	PreviewWidget = SNew(SSimpleAssetViewport);
	
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("SimpleAssetEditorLayoutv1.0")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.6f)
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.8f)
				->AddTab("SimpleAssetViewportTab", ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab("SimpleAssetDetailsTab", ETabState::OpenedTab)
			)
		)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.4f)
			->AddTab("OutputLog", ETabState::OpenedTab)
		)
	);
	
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, {}, "SimpleAssetEditor", Layout, true, true, InSimpleAsset);
}

void FSimpleAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	//Register Viewport
	InTabManager->RegisterTabSpawner(
	"SimpleAssetViewportTab",
	FOnSpawnTab::CreateSP(this, &FSimpleAssetEditorToolkit::SpawnTab_Viewport))
	.SetDisplayName(LOCTEXT("PreviewSceneViewport", "Preview Viewport"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef())
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));
	
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("Simple Asset Editor"));
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	
	TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObjects(TArray<UObject*>{ SimpleAsset });
	
	InTabManager->RegisterTabSpawner("SimpleAssetDetailsTab", FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)
		[
			DetailsView
		];
	}))
	.SetDisplayName(INVTEXT("Details"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	
}

void FSimpleAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner("SimpleAssetDetailsTab");
	InTabManager->UnregisterTabSpawner("SimpleAssetViewportTab");
}

TSharedRef<SDockTab> FSimpleAssetEditorToolkit::SpawnTab_Viewport(const FSpawnTabArgs& Args) const
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab).Label(LOCTEXT("ViewportTab_Title", "Viewport"));

	if (PreviewWidget.IsValid())
	{
		SpawnedTab->SetContent(PreviewWidget.ToSharedRef());
	}

	return SpawnedTab;
}

#undef LOCTEXT_NAMESPACE