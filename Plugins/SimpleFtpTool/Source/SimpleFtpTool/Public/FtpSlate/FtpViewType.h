#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ProceduralMeshComponent.h"



DECLARE_DELEGATE_OneParam(FSimpleOneParamDelegate, const TArray<FString>&);


extern FSimpleOneParamDelegate SimpleOneParamDelegate;
extern UStaticMeshComponent* GMeshComponent;
extern UProceduralMeshComponent* GProceduralMeshComponent;