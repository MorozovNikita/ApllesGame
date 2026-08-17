#pragma once

#include <cstdint>

namespace ApplesGame
{
    enum class GameMode : uint32_t
    {
        None = 0,                       // 0000 0000
        FiniteApples = 1 << 0,          // 0000 0001
        InfiniteApples = 1 << 1,        // 0000 0010
        WithAcceleration = 1 << 2,      // 0000 0100
        WithoutAcceleration = 1 << 3,   // 0000 1000
    };

    inline GameMode operator|(GameMode a, GameMode b)
    {
        return static_cast<GameMode>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    inline GameMode operator&(GameMode a, GameMode b)
    {
        return static_cast<GameMode>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    inline bool hasFlag(GameMode mode, GameMode flag)
    {
        return (mode & flag) == flag;
    }

} // namespace ApplesGame