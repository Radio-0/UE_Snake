// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MoveSpeed = 10.f;
	LastMoveDirection = EMoveDirection::UP;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++) {
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		SnakeElements.Add(NewSnakeElem);
	}
}

void ASnakeBase::Move(float DeltaTime)
{
	FVector MoveVector(FVector::ZeroVector);
	float MoveSpeedDelta = MoveSpeed * DeltaTime;
	switch (LastMoveDirection) {
	case EMoveDirection::UP:
		MoveVector.X += MoveSpeedDelta;
		break;
	case EMoveDirection::DOWN:
		MoveVector.X -= MoveSpeedDelta;
		break;
	case EMoveDirection::RIGHT:
		MoveVector.Y -= MoveSpeedDelta;
		break;
	case EMoveDirection::LEFT:
		MoveVector.Y += MoveSpeedDelta;
		break;
	}
	AddActorWorldOffset(MoveVector);
}