// Fill out your copyright notice in the Description page of Project Settings.


#include "System/PowerNodeDoor.h"

// Sets default values
APowerNodeDoor::APowerNodeDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = DoorMesh;

}

// Called when the game starts or when spawned
void APowerNodeDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerNodeDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

