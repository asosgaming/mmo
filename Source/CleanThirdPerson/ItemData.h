// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HotbarObject.h"
#include "ItemData.generated.h"


UENUM(BlueprintType)       //"BlueprintType" is essential to include
enum class ItemQuality : uint8
{
	Poor     UMETA(DisplayName = "Poor"),
	Common    UMETA(DisplayName = "Common"),
	Uncommon     UMETA(DisplayName = "Uncommon"),
	Rare   UMETA(DisplayName = "Rare"),
	Epic   UMETA(DisplayName = "Epic"),
	Legendary   UMETA(DisplayName = "Legendary")

};

UCLASS(Blueprintable, BlueprintType)
class CLEANTHIRDPERSON_API UItemData : public UHotbarObject
{
	GENERATED_BODY()
	
	public:
	
	UItemData(const FObjectInitializer& ObjectInitializer);

	virtual void PostRename(UObject* OldOuter, const FName OldName) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	ItemQuality Quality;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	bool isStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	bool Droppable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	USoundWave* PickSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	USoundWave* PlaceSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	UStaticMesh* Mesh;
};
