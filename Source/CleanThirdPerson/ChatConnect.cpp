// Fill out your copyright notice in the Description page of Project Settings.

#include "ChatConnect.h"
#include "CleanThirdPerson.h"

#include "TimerManager.h"
#include <string>
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "SharedPointer.h"

AChatConnect::AChatConnect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AChatConnect::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChatConnect::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AChatConnect::ParseSocialCommand(const FString& SourceString)
{
	TArray<FString> Words;

	FString Delimiter = TEXT(" ");

	if (SourceString.Len() == 0)
		return;

	SourceString.ParseIntoArray(Words, *Delimiter, true);

	if (Words.Num() == 0)
		return;

	FString Command = Words[0];
	
	UE_LOG(LogTemp, Log, TEXT("command: %s"), *Command);

	if (Words.Num() > 1)
	{
		FString Target = Words[1];

		if (Command == TEXT("/w")) //send a private message
		{
			FString Message = SourceString.RightChop(Command.Len() + Target.Len() + 2); // 2 stands for 2 empty spaces that come from command and target
			
			if (!Message.IsEmpty())
			{
				SendPrivateMessage(Target, Message);
			}		

			return;
		}
	
		else if (Command == TEXT("/invite") || Command == TEXT("/inv")) //invite a player to the group
		{
			GroupInvite(Target);

			return;
		}
		else if (Command == TEXT("/kick")) //kick a player from the group
		{
			GroupKick(Target);

			return;
		}
		else if (Command == TEXT("/gcreate")) //create a clan
		{
			for (int i = 2; i < Words.Num(); i++)
			{
				Target += " " + Words[i];
			}

			if (Target.Len() > 23)
			{
				Target = Target.LeftChop(Target.Len() - 23); // allows 23 character long clan names
			}
				
			ClanCreate(Target);

			return;
		}
		else if (Command == TEXT("/ginvite")) //invite a player to the clan
		{
			ClanInvite(Target);

			return;
		}
		else if (Command == TEXT("/gkick")) //kick a player from the clan
		{
			ClanKick(Target);

			return;
		}
	}

	if (Command == TEXT("/p")) //send group message
	{
		FString Message = SourceString.RightChop(Command.Len() + 1);
		
		if (!Message.IsEmpty())
		{
			SendGroupMessage(Message);
		}

		return;
	}
	else if (Command == TEXT("/g")) //send clan message
	{
		FString Message = SourceString.RightChop(Command.Len() + 1);
		
		if (!Message.IsEmpty())
		{
			SendClanMessage(Message);
		}

		return;
	}
	if (Command == TEXT("/leave")) //leave the group
	{		
		GroupLeave();
		return;
	}
	else if (Command == TEXT("/gquit")) //leave the clan
	{
		ClanLeave();
		return;
	}
	else if (Command == TEXT("/gdisband")) //disband the clan
	{
		ClanDisband();
		return;
	}

	SendMessage(SourceString); //send global message
	
}


bool AChatConnect::ConnectToSocket(const FString& Address, int32 port)
{
	
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	
	FString address = Address;

	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	bool connected = Socket->Connect(*addr);

	if (connected)
	{
		FTimerHandle SocketTimer;

		GetWorldTimerManager().SetTimer(SocketTimer, this,
			&AChatConnect::TCPSocketListener, 0.01, true);
	}

	return connected;

}

bool AChatConnect::Login(const FString& Name)
{
	return SendData(0, Name, "");
}

bool AChatConnect::SendMessage(const FString& Message)
{
	return SendData(2, "", Message);
}

bool AChatConnect::SendPrivateMessage(const FString& TargetName, const FString& Message)
{
	return SendData(3, TargetName, Message);
}

bool AChatConnect::SendGroupMessage(const FString& Message)
{
	return SendData(9, "", Message);
}

bool AChatConnect::GroupInvite(const FString& TargetName)
{
	return SendData(4, TargetName, "");
}

bool AChatConnect::GroupLeave()
{
	return SendData(5, "", "");
}

bool AChatConnect::GroupAcceptInvite()
{
	return SendData(7, "", "");
}

bool AChatConnect::GroupDeclineInvite()
{
	return SendData(8, "", "");
}

bool AChatConnect::GroupKick(const FString& TargetName)
{
	return SendData(10, TargetName, "");
}

//clan:

bool AChatConnect::ClanLeave()
{
	return SendData(11, "", "");
}

bool AChatConnect::ClanInvite(const FString& TargetName)
{
	return SendData(12, TargetName, "");
}

bool AChatConnect::SendClanMessage(const FString& Message)
{
	return SendData(15, "", Message);
}

bool AChatConnect::ClanKick(const FString& TargetName)
{
	return SendData(16, TargetName, "");
}

bool AChatConnect::ClanCreate(const FString& ClanName)
{
	return SendData(18, ClanName, "");
}

bool AChatConnect::ClanDisband()
{
	return SendData(19, "", "");
}

bool AChatConnect::SendData(int32 Command, const FString& Name, const FString& Message)
{
	//format:
	// first 4 bytes - command
	// next 4 bytes - length of name
	// next 4 bytes - length of message
	// name
	// message
	int32 sent = 0;

	FString myname = Name;
	FString mymessage = Message;
	//determine the length of name:


	TCHAR *namearray = myname.GetCharArray().GetData();

	uint8* name = (uint8*)TCHAR_TO_UTF8(namearray);

	FTCHARToUTF8 Convert(*myname);
	int namelength = Convert.Length(); //length of the utf-8 string in bytes

	//determine the length of message:
	TCHAR *messagearray = mymessage.GetCharArray().GetData();

	uint8* message = (uint8*)TCHAR_TO_UTF8(messagearray);

	FTCHARToUTF8 ConvertMessage(*mymessage);
	int messagelength = ConvertMessage.Length(); //length of the utf-8 string in bytes

	TArray<uint8> TotalMessage;

	//add command:
	TotalMessage.Add((uint8)Command);
	TotalMessage.Add(0);
	TotalMessage.Add(0);
	TotalMessage.Add(0);

	int index = 4;

	//add name length:
	for (int i = 0; i < 4; i++)
	{
		TotalMessage.Add(namelength >> i * 8);
		index++;
	}
	// add message length:
	for (int i = 0; i < 4; i++)
	{
		TotalMessage.Add(messagelength >> i * 8);
		index++;
	}
	// add name:
	for (int i = 0; i < namelength; i++)
	{
		TotalMessage.Add(name[i]);
		index++;
	}
	//add message:
	for (int i = 0; i < messagelength; i++)
	{
		TotalMessage.Add(message[i]);
		index++;
	}

	bool successful = Socket->Send(TotalMessage.GetData(), TotalMessage.Num(), sent);

	return successful;
}


void AChatConnect::TCPSocketListener()
{
	if (!Socket) return;

	TArray<uint8> ReceivedData;

	uint32 Size;
	while (Socket->HasPendingData(Size))
	{
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

		int32 Read = 0;
		Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);	
	}

	if (ReceivedData.Num() <= 0) return;	//No Data Received
	
	ProcessMessages(ReceivedData);
}

void AChatConnect::ProcessMessages(TArray<uint8> ReceivedData)
{
	while (ReceivedData.Num() > 0)
	{
		uint8 Command = ReceivedData[0];
		ReceivedData.RemoveAt(0, 4, true); // cut the first 4 bytes, which is Command

		int32 namelength = int32(
			(unsigned char)(ReceivedData[3]) << 24 |
			(unsigned char)(ReceivedData[2]) << 16 |
			(unsigned char)(ReceivedData[1]) << 8 |
			(unsigned char)(ReceivedData[0])
		);
		ReceivedData.RemoveAt(0, 4, true); // cut the next 4 bytes, which is NameLength

		int32 messageLength = int32(
			(unsigned char)(ReceivedData[3]) << 24 |
			(unsigned char)(ReceivedData[2]) << 16 |
			(unsigned char)(ReceivedData[1]) << 8 |
			(unsigned char)(ReceivedData[0])
		);
		ReceivedData.RemoveAt(0, 4, true); // cut the next 4 bytes, which is MessageLength

		TArray<uint8> NameAsArray = TArray<uint8>(ReceivedData);
		NameAsArray.RemoveAt(namelength, ReceivedData.Num() - namelength);
		const FString ReceivedUE4String = StringFromBinaryArray(NameAsArray);
		const FText ReceivedName = FText::AsCultureInvariant(ReceivedUE4String);
		ReceivedData.RemoveAt(0, namelength, true);

		TArray<uint8> MessageAsArray = TArray<uint8>(ReceivedData);
		MessageAsArray.RemoveAt(messageLength, ReceivedData.Num() - messageLength);
		const FString ReceivedMessageString = StringFromBinaryArray(MessageAsArray);
		const FText ReceivedMessage = FText::AsCultureInvariant(ReceivedMessageString);
		ReceivedData.RemoveAt(0, messageLength, true);

		switch (Command)
		{
		case 2: //message
			OnMessageReceived(ReceivedName, ReceivedMessage);
			break;
		case 3: //private message
			OnPrivateMessageReceived(ReceivedName, ReceivedMessage);
			break;
		case 4: //group invite
			OnGroupInviteReceived(ReceivedName);
			break;
		case 6: //group update
			OnGroupUpdate(ReceivedMessageString);
			break;
		case 9: //group message
			OnGroupMessageReceived(ReceivedName, ReceivedMessage);
			break;
		case 10: //kicked from the group
			OnGroupKicked();
			break;
		case 17: //clan update
			OnClanUpdate();
			break;
		case 12: //clan invite
			OnClanInviteReceived(ReceivedName, ReceivedMessage);
			break;
		case 15: //clan message
			OnClanMessageReceived(ReceivedName, ReceivedMessage);
			break;
		}
	}
}


//Rama's String From Binary Array
//This function requires 
//		#include <string>
FString AChatConnect::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	//Create a string from a byte array!
	std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());

	//FString temp = FString(cstr.c_str()); //in utf8

	return FString(UTF8_TO_TCHAR(cstr.c_str()));
}