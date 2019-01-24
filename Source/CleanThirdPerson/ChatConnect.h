// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChatConnect.generated.h"

UCLASS()
class CLEANTHIRDPERSON_API AChatConnect : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AChatConnect();
		
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	FSocket* Socket;

	UFUNCTION(BluePrintCallable, Category = Chat)
		void ParseSocialCommand(const FString& SourceString);

	UFUNCTION(BluePrintCallable, Category = Chat)
		bool ConnectToSocket(const FString& Address, int32 port);

	UFUNCTION()
		void ProcessMessages(TArray<uint8> ReceivedData);

	UFUNCTION(BluePrintCallable, Category = Chat)
		bool SendMessage(const FString& Message);

	UFUNCTION(BluePrintCallable, Category = Chat)
		bool SendPrivateMessage(const FString& TargetName, const FString& Message);

	UFUNCTION(BluePrintCallable, Category = Chat)
		bool SendGroupMessage(const FString& Message);

	UFUNCTION(BluePrintCallable, Category = Chat)
		bool Login(const FString& Name);

	UFUNCTION(BluePrintCallable, Category = Group)
		bool GroupInvite(const FString& TargetName);
	
	UFUNCTION(BluePrintCallable, Category = Group)
		bool GroupLeave();

	UFUNCTION(BluePrintCallable, Category = Group)
		bool GroupAcceptInvite();

	UFUNCTION(BluePrintCallable, Category = Group)
		bool GroupDeclineInvite();

	UFUNCTION(BluePrintCallable, Category = Group)
		bool GroupKick(const FString& TargetName);
	
	//clan:
	UFUNCTION(BluePrintCallable, Category = Clan)
		bool ClanCreate(const FString& ClanName);

	UFUNCTION(BluePrintCallable, Category = Clan)
		bool ClanInvite(const FString& TargetName);

	UFUNCTION(BluePrintCallable, Category = Clan)
		bool ClanKick(const FString& TargetName);

	UFUNCTION(BluePrintCallable, Category = Clan)
		bool ClanDisband();

	UFUNCTION(BluePrintCallable, Category = Clan)
		bool ClanLeave();


	UFUNCTION(BluePrintCallable, Category = Chat)
		bool SendClanMessage(const FString& Message);

	bool SendData(int32 Command, const FString& Name, const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = Chat)
		void OnMessageReceived(const FText& Name, const FText& Message);
		
	UFUNCTION(BlueprintImplementableEvent, Category = Chat)
		void OnGroupMessageReceived(const FText& Name, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = Clan)
		void OnClanInviteReceived(const FText& Name, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = Chat)
		void OnClanMessageReceived(const FText& Name, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = Chat)
		void OnPrivateMessageReceived(const FText& Name, const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = Group)
		void OnGroupInviteReceived(const FText& Name);

	UFUNCTION(BlueprintImplementableEvent, Category = Group)
		void OnGroupUpdate(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = Group)
		void OnGroupKicked();

	UFUNCTION(BlueprintImplementableEvent, Category = Clan)
		void OnClanUpdate();

	//Timer functions, could be threads
	void TCPSocketListener();		//can thread this eventually
		
	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);	
	
};
