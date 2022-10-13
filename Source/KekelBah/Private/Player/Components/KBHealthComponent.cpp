// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/KBHealthComponent.h"


UKBHealthComponent::UKBHealthComponent()
{

}


// Called when the game starts
void UKBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}
