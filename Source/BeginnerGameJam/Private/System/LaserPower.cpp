// Fill out your copyright notice in the Description page of Project Settings.


#include "System/LaserPower.h"

// Sets default values
ALaserPower::ALaserPower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ALaserPower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserPower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

