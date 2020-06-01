// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebRemoteActor.generated.h"


UCLASS()
class SIMPLEFTPTOOL_API AWebRemoteActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWebRemoteActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	FString GetMyPathName();

	UFUNCTION(BlueprintCallable)
		void asd(const TArray<FString>& InputVal);

	void ShowWeb();

public:

	class UDownloadWidget* DownloadUI;
	
private:
	FString MyPathName;
	FString WebURL;

};
