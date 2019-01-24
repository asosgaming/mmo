// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "HotbarObject.generated.h"


UCLASS(Blueprintable, BlueprintType)
class CLEANTHIRDPERSON_API UHotbarObject : public UDataAsset
{
	GENERATED_BODY()
	
	public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = General)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = General)
	TAssetPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = General)
	FText Description;
};
