// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;

UENUM()
enum class EMoveDirection {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

UCLASS()
class SNAKE_20_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeElementBase> SnakeElementClass;
	UPROPERTY(EditDefaultsOnly)
		float ElementSize;
	UPROPERTY()
		TArray<ASnakeElementBase*> SnakeElements;
	UPROPERTY(EditDefaultsOnly)
		float MoveSpeed;
	UPROPERTY()
		EMoveDirection LastMoveDirection;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddSnakeElement(int ElementsNum = 1);
	void Move(float DeltaTime);
};