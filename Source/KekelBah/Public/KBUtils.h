#pragma once

class KBUtils
{
public:

	template<typename T>
    static T* GetPlayerComponent(APawn* Pawn)
	{
        if (!Pawn) return nullptr;

        const auto ActorComponent = Pawn->GetComponentByClass(T::StaticClass());
        return  Cast<T>(ActorComponent);
	}

};
