// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemData.h"
#include "Engine/DataAsset.h"
#include "Quest.generated.h"

USTRUCT(Blueprintable)
struct FQuestTaskBring
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Task)
		UItemData* ItemToBring;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Task)
		int32 AmountToBring = 1;
		
};  

USTRUCT(Blueprintable)
struct FQuestTaskKill
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Task)
	UClass* CharacterToKill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Task)
	int32 NumberOfKills;

};

UCLASS(Blueprintable, BlueprintType)
class CLEANTHIRDPERSON_API UQuest : public UDataAsset
{
	GENERATED_BODY()
	
	public:

	UQuest(const FObjectInitializer& ObjectInitializer);

	virtual void PostRename(UObject* OldOuter, const FName OldName) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText TextOffered;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText TextObjectives;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText TextRemind;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText TextCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	int32 MinLevel;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	TArray<FQuestTaskBring> BringTasks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	TArray<FQuestTaskKill> KillTasks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	TArray<UItemData*> Rewards;
	
};
