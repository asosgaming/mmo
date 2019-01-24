// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "SocketConnect.generated.h"

UCLASS()
class CLEANTHIRDPERSON_API ASocketConnect : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASocketConnect();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FSocket* Socket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sockets)
		bool isConnected;

	UFUNCTION(BluePrintCallable, Category = Sockets)
		void ConnectToSocket(const FString& Address, int32 port);

	//Timer functions, could be threads
	virtual void TCPSocketListener();		//can thread this eventually

											//based on Rama's StringFromBinaryArray
	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);

	void OnConnect();

	UFUNCTION(BlueprintImplementableEvent, Category = Sockets)
		void OnConnectFailed();
	void CheckThreadsDone();

private:
	FGraphEventArray		Tasks;
	FTimerHandle CheckTimer;

	class FConnectTask
	{
		ASocketConnect* socketConnect;
		FSocket* Socket;
		TSharedRef<FInternetAddr> addr;

	public:

		FConnectTask(ASocketConnect* InSocketConnect, FSocket* InSocket, TSharedRef<FInternetAddr> InAddr)
			:socketConnect(InSocketConnect),
			Socket(InSocket),
			addr(InAddr)
		{ }

		static ESubsequentsMode::Type GetSubsequentsMode()
		{
			return ESubsequentsMode::TrackSubsequents;
		}

		FORCEINLINE static TStatId GetStatId()
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTestTask, STATGROUP_TaskGraphTasks);
		}

		static ENamedThreads::Type GetDesiredThread()
		{
			return ENamedThreads::AnyThread;
		}

		void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
		{
			bool connected = Socket->Connect(*addr);

			UE_LOG(LogTemp, Warning, TEXT("connect status: %d"), connected);

			socketConnect->isConnected = connected;

		}

	};	
	
};
