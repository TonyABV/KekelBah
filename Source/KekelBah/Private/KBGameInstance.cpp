// Fill out your copyright notice in the Description page of Project Settings.


#include "KBGameInstance.h"
#include "KBSoundFuncLib.h"

void UKBGameInstance::ToggleMasterSound()
{
    UKBSoundFuncLib::ToggleSoundClass(MasterSoundClass);
}
