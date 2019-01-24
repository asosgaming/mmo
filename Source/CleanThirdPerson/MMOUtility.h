// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemData.h"
#include "Quest.h"
#include "CanvasPanelSlot.h"
#include "MMOUtility.generated.h"


UENUM(BlueprintType)       //"BlueprintType" is essential to include
enum class CharacterClass : uint8
{
	Warrior		UMETA(DisplayName = "Warrior"),
	Rogue    UMETA(DisplayName = "Rogue"),
	Mage     UMETA(DisplayName = "Mage"),
	
};

UCLASS()
class CLEANTHIRDPERSON_API UMMOUtility : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
		
	UFUNCTION(BlueprintPure, Category = "MMO Utility")
	static FVector2D ClampVector2D(FVector2D Target, FVector2D Min, FVector2D Max); //useful for clamping UI popups so they don't exceed the screen

	UFUNCTION(BlueprintPure, Category = "MMO Utility")
	static FVector2D GetSize(UCanvasPanelSlot* Target);

	UFUNCTION(BlueprintPure, Category = "MMO Utility")
	static UMaterialInterface* GetMaterial(FSkeletalMaterial Target);

	UFUNCTION(BlueprintCallable, Category = "MMO Utility")
	static void SetMousePosition(float PosX, float PosY, APlayerController* Target);
	
	UFUNCTION(BlueprintCallable, Category = "MMO Utility")
	static bool CheckCommandLine(FString Parameter);

	UFUNCTION(BlueprintPure, Category = "MMO Utility")
	static FString AddLineBreak(FString String);

	UFUNCTION(BlueprintCallable, Category = "MMO Utility")
	static bool InPIEWorld(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MMO Utility")
	static UItemData* LoadItemDataFromPath(const FName& Path);
	
	UFUNCTION(BlueprintCallable, Category = "MMO Utility")
	static UAbility* LoadAbilityFromPath(const FName& Path);
	
	UFUNCTION(BlueprintCallable, Category = "MMO Utility")
	static UQuest* LoadQuestFromPath(const FName& Path);

	UFUNCTION(BlueprintCallable, Category = "MMO Utility")
	static void LoadItemIcons(const FString& Path);

	UFUNCTION(BlueprintPure, Category = "MMO Utility")
	static FName GetObjPath(const UObject* Obj);


};
