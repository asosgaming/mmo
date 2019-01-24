// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "CleanThirdPerson.h"
#include "Runtime/Engine/Classes/Engine/GameEngine.h"
#include "MoviePlayer.h"

//void UMyGameInstance::Init()
//{
//	UGameInstance::Init();
//
//	if (!IsRunningDedicatedServer())
//	{
//		FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);		
//	}
//	
//}
//
//void UMyGameInstance::BeginLoadingScreen(const FString& MapName)
//{
//	FLoadingScreenAttributes LoadingScreen;
//	
//	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
//
//	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
//}


void UMyGameInstance::EndLoadingScreen() 
{
	GetMoviePlayer()->StopMovie();

	UGameEngine* GameEngine = Cast<UGameEngine>(GEngine);
	if (GameEngine)
	{
		GameEngine->SwitchGameWindowToUseGameViewport(); 
	}	
}


