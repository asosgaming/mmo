// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketConnect.h"
#include "CleanThirdPerson.h"
#include "TimerManager.h"
#include <string>
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "SharedPointer.h"

// Sets default values
ASocketConnect::ASocketConnect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASocketConnect::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASocketConnect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASocketConnect::ConnectToSocket(const FString& Address, int32 port)
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString address = Address;

	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	TGraphTask<FConnectTask>::CreateTask().ConstructAndDispatchWhenReady(this, Socket, addr);

	//Start a timer to check when the thread is done

	GetWorldTimerManager().SetTimer(CheckTimer, this, &ASocketConnect::CheckThreadsDone, 1, true);
}

void ASocketConnect::CheckThreadsDone()
{
	//Check all thread completion events
	for (int32 Index = 0; Index < Tasks.Num(); Index++)
	{
		//If  ! IsComplete()
		if (!Tasks[Index]->IsComplete())
		{
			break; //not complete
		}
	}

	//complete, clear timer:

	GetWorldTimerManager().ClearTimer(CheckTimer);

	if (isConnected) OnConnect();
	else OnConnectFailed();
}

void ASocketConnect::TCPSocketListener()
{

}

FString ASocketConnect::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());

	return FString(UTF8_TO_TCHAR(cstr.c_str()));
}

void ASocketConnect::OnConnect()
{
	FTimerHandle SocketTimer;

	GetWorldTimerManager().SetTimer(SocketTimer, this,
		&ASocketConnect::TCPSocketListener, 0.01, true);
}
