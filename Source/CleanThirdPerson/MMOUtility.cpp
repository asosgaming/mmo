// Fill out your copyright notice in the Description page of Project Settings.

#include "MMOUtility.h"
#include "CleanThirdPerson.h"
#include "ItemData.h"
#include "Quest.h"
#include "Ability.h"
#include "Runtime/Engine/Classes/Engine/ObjectLibrary.h"
#include "CanvasPanelSlot.h"

UMMOUtility::UMMOUtility(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FVector2D UMMOUtility::ClampVector2D(FVector2D Target, FVector2D Min, FVector2D Max)
{
	return FVector2D(
		FMath::Clamp(Target.X, Min.X, Max.X),
		FMath::Clamp(Target.Y, Min.Y, Max.Y)
		);
	
}


FVector2D UMMOUtility::GetSize(UCanvasPanelSlot* Target)
{
	FVector2D Output;
	Output.X = Target->LayoutData.Offsets.Right;
	Output.Y = Target->LayoutData.Offsets.Bottom;

	return Output;
}

UMaterialInterface* UMMOUtility::GetMaterial(FSkeletalMaterial Target)
{
	return Target.MaterialInterface;
}

void UMMOUtility::SetMousePosition(float PosX, float PosY, APlayerController* Target)
{

	FViewport* v = CastChecked<ULocalPlayer>(Target->Player)->ViewportClient->Viewport;
	
	int intX = (int)PosX;
	int intY = (int)PosY;

	v->SetMouse(intX, intY);

}


bool UMMOUtility::CheckCommandLine(FString Parameter)
{

	if (FParse::Param(FCommandLine::Get(), *Parameter))
	{
		return true;
	}

	return false;

}



bool UMMOUtility::InPIEWorld(UObject* WorldContextObject)
{
	if (!WorldContextObject) return false;
	
	UWorld* const World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	if (!World) return false;

	return (World->WorldType == EWorldType::PIE);
}

FString UMMOUtility::AddLineBreak(FString String)
{

	return String + "\n";

}

UItemData* UMMOUtility::LoadItemDataFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	

	return Cast<UItemData>(StaticLoadObject(UItemData::StaticClass(), NULL, *Path.ToString()));
}

UAbility* UMMOUtility::LoadAbilityFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;


	return Cast<UAbility>(StaticLoadObject(UAbility::StaticClass(), NULL, *Path.ToString()));
}

UQuest* UMMOUtility::LoadQuestFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;


	return Cast<UQuest>(StaticLoadObject(UQuest::StaticClass(), NULL, *Path.ToString()));
}

void UMMOUtility::LoadItemIcons(const FString& Path)
{
	
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UTexture2D::StaticClass(), false, GIsEditor);
	ObjectLibrary->AddToRoot();
	
	ObjectLibrary->LoadAssetDataFromPath(Path);
	
	ObjectLibrary->LoadAssetsFromAssetData();
	
}


FName UMMOUtility::GetObjPath(const UObject* Obj)
{
	if (!Obj) return NAME_None;
	if (!Obj->IsValidLowLevel()) return NAME_None;
	//~

	FStringAssetReference ThePath = FStringAssetReference(Obj);

	if (!ThePath.IsValid()) return NAME_None;

	//The Class FString Name For This Object
	FString Str = Obj->GetClass()->GetDescription();

	Str += "'";
	Str += ThePath.ToString();
	Str += "'";

	return FName(*Str);
}