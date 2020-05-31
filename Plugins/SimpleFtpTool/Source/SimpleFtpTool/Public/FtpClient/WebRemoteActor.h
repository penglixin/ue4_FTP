// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
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
		void Download(const TArray<FString>& InputVal);

	UFUNCTION(BlueprintCallable)
		void asd(const FString& InputVal);

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TestUI;
	
private:
	FString MyPathName;

};
