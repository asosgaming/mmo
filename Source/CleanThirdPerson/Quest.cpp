// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest.h"
#include "CleanThirdPerson.h"

UQuest::UQuest(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Name = FText::FromString(GetName()); //make the human-readable name the same as the asset name
}

void UQuest::PostRename(UObject* OldOuter, const FName OldName)
{
	Name = FText::FromString(GetName()); //make the human-readable name the same as the asset name
}


