#pragma once

#include "KBPlayerState.h"

class KBUtils
{
public:

	template<typename T>
    static T* GetPlayerComponent(AActor* Pawn)
	{
        if (!Pawn) return nullptr;

        const auto ActorComponent = Pawn->GetComponentByClass(T::StaticClass());
        return  Cast<T>(ActorComponent);
	}

    bool static AreEnemies(const AController* Controller1, const AController* Controller2)
	{
        if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		const AKBPlayerState* State1 = Cast<AKBPlayerState>(Controller1->PlayerState);
        const AKBPlayerState* State2 = Cast<AKBPlayerState>(Controller2->PlayerState);

	    return State1 && State2 && State1->GetTeamID() != State2->GetTeamID();
	}
};
