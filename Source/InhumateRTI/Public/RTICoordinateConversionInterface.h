// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "RTICoordinateConversionInterface.generated.h"

USTRUCT(BlueprintType)
struct FGeodeticLocation {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, Category="RTI")
    float Longitude;

    UPROPERTY(BlueprintReadWrite, Category="RTI")
    float Latitude;

    UPROPERTY(BlueprintReadWrite, Category="RTI")
    float Altitude;
};

UINTERFACE(MinimalAPI, Blueprintable)
class URTIGeodeticCoordinateConversionInterface : public UInterface
{
    GENERATED_BODY()
};

class INHUMATERTI_API IRTIGeodeticCoordinateConversionInterface
{
    GENERATED_BODY()

    public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = RTI)
    FVector GeodeticToLocal(const FGeodeticLocation &GeodeticLocation);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = RTI)
    FGeodeticLocation LocalToGeodetic(const FVector &XYZ);
};

UINTERFACE(MinimalAPI, Blueprintable)
class URTILocalCoordinateConversionInterface : public UInterface
{
    GENERATED_BODY()
};

class INHUMATERTI_API IRTILocalCoordinateConversionInterface
{
    GENERATED_BODY()

    public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = RTI)
    FVector RTIToLocalLocation(const FVector &RTILocation);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = RTI)
    FVector LocalLocationToRTI(const FVector &LocalLocation);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = RTI)
    FRotator RTIEulerToLocalRotation(const FRotator &RTIEuler);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = RTI)
    FRotator LocalRotationToRTIEuler(const FRotator &LocalRotation);
};
