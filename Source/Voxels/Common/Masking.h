#pragma once
#include "CoreMinimal.h"

template <typename E>
bool IsSet(E value, E mask)
{
    return (value & mask) == mask;
}

template <typename E>
bool IsSet(TEnumAsByte<E> value, E mask)
{
    return IsSet<E>(value.GetValue(), mask);
}
