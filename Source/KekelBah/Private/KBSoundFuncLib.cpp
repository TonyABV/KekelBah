// Fill out your copyright notice in the Description page of Project Settings.


#include "KBSoundFuncLib.h"
#include "Sound/SoundClass.h"

void UKBSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if (SoundClass)
    {
        SoundClass->Properties.Volume = Volume;
    }
}

void UKBSoundFuncLib::ToggleSoundClass(USoundClass* SoundClass)
{
    if (SoundClass)
    {
        SoundClass->Properties.Volume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
    }
}
