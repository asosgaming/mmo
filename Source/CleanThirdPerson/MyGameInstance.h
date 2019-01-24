// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class CLEANTHIRDPERSON_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/*virtual void Init() override;

	UFUNCTION()
		 virtual void BeginLoadingScreen(const FString& MapName);*/

	UFUNCTION(BlueprintCallable, Category = "Game")
		 virtual void EndLoadingScreen();
		
};
