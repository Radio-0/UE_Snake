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
	SetActorTickInterval(MoveSpeed);
	AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++) {
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if (ElemIndex == 0) {
			NewSnakeElem->SetFirstElementType();
		}
	}
}

void ASnakeBase::Move()
{
	FVector MoveVector(FVector::ZeroVector);
	float MoveSpeedEl = ElementSize;
	switch (LastMoveDirection) {
	case EMoveDirection::UP:
		MoveVector.X += MoveSpeedEl;
		break;
	case EMoveDirection::DOWN:
		MoveVector.X -= MoveSpeedEl;
		break;
	case EMoveDirection::RIGHT:
		MoveVector.Y += MoveSpeedEl;
		break;
	case EMoveDirection::LEFT:
		MoveVector.Y -= MoveSpeedEl;
		break;
	}
	//AddActorWorldOffset(MoveVector);

	for (int i = SnakeElements.Num() - 1; i > 0; i--) {
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevElementLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevElementLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MoveVector);
}