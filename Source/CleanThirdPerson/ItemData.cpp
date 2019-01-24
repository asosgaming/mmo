// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemData.h"
#include "CleanThirdPerson.h"


UItemData::UItemData(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Name = FText::FromString(GetName()); //make the human-readable name the same as the asset name
}

void UItemData::PostRename(UObject* OldOuter, const FName OldName)
{
	Name = FText::FromString(GetName()); //make the human-readable name the same as the asset name
}
