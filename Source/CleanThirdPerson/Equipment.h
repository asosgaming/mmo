// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemData.h"
#include "Equipment.generated.h"


UENUM(BlueprintType)       //"BlueprintType" is essential to include

enum class EquipmentType : uint8
{
	Head     UMETA(DisplayName = "Head"),
	Torso    UMETA(DisplayName = "Chest"),
	Legs     UMETA(DisplayName = "Legs"),
	Hands   UMETA(DisplayName = "Hands"),
	Feet   UMETA(DisplayName = "Feet"),
	Weapon   UMETA(DisplayName = "Weapon"),
	WeaponSecondary   UMETA(DisplayName = "WeaponSecondary")
};

UCLASS()
class CLEANTHIRDPERSON_API UEquipment : public UItemData
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	EquipmentType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment)
	int32 Armor = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	USkeletalMesh* EquippedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	UMaterialInstance* MaterialOverride; //When provided, overrides the default material of the mesh
	
	
};
