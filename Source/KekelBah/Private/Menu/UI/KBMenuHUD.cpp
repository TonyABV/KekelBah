// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/KBMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AKBMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass);
    if (MenuWidget)
    {
        MenuWidget->AddToViewport();
    }
}
