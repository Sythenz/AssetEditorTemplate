// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetEditor/SimpleAssetEditorToolkit.h"

#include "AssetEditorTemplate.h"
#include "AssetEditorTemplateCommands.h"
#include "AssetEditorTemplateEditor.h"
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
	BindCommands();
	
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
	PreviewViewportWidget = SNew(SSimpleAssetViewport);
	
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
	
	//Add buttons to the Asset Editor
	ExtendToolbars();
}

void FSimpleAssetEditorToolkit::BindCommands()
{
	FAssetEditorTemplateCommands::Register();
	
	const FAssetEditorTemplateCommands& Commands = FAssetEditorTemplateCommands::Get();
	
	ToolkitCommands->MapAction(Commands.FocusViewport,
	FExecuteAction::CreateSP(this, &FSimpleAssetEditorToolkit::FocusViewport));
}

void FSimpleAssetEditorToolkit::ExtendToolbars()
{
	struct Local
	{
		static void FillToolbar(FToolBarBuilder& ToolbarBuilder)
		{
			ToolbarBuilder.BeginSection("ExtendToolbarItem");
			{
				ToolbarBuilder.AddToolBarButton(
					FAssetEditorTemplateCommands::Get().FocusViewport,
					NAME_None,
					LOCTEXT("FocusViewport", "Focus Viewport"),
					LOCTEXT("FocusViewportTooltip", "Focuses Viewport on selected Mesh"),
					FSlateIcon()
				);
				
			}
			ToolbarBuilder.EndSection();
		}
	};
	
	//Register Toolbar Extenders
	const TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	
	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateStatic(&Local::FillToolbar)
	);
	
	AddToolbarExtender(ToolbarExtender);
	
	FAssetEditorTemplateEditorModule* AssetEditorTemplateModule = &FModuleManager::LoadModuleChecked<FAssetEditorTemplateEditorModule>("AssetEditorTemplateEditor");
	AddToolbarExtender(AssetEditorTemplateModule->GetEditorToolbarExtensibilityManager()->GetAllExtenders());

	RegenerateMenusAndToolbars();
}

void FSimpleAssetEditorToolkit::FocusViewport() const
{
	if(PreviewViewportWidget.IsValid())
	{
		PreviewViewportWidget->OnFocusViewportToSelection();
	}
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

	if (PreviewViewportWidget.IsValid())
	{
		SpawnedTab->SetContent(PreviewViewportWidget.ToSharedRef());
	}

	return SpawnedTab;
}

#undef LOCTEXT_NAMESPACE