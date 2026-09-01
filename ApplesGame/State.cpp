#include "State.h"

namespace ApplesGame
{
    State::State(StateStack& stack, Context context)
        : mStack(stack)
        , mContext(context)
    {
    }
}