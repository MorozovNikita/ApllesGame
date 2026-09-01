#pragma once

#include <vector>
#include <map>
#include <functional>
#include <cassert>

#include "State.h"

namespace ApplesGame
{
    class StateStack
    {
    public:
        enum class Action { Push, Pop, Clear };

        explicit StateStack(State::Context context);

        template <typename T>
        void registerState(States::ID id)
        {
            assert(mFactories.find(id) == mFactories.end());
            mFactories[id] = [this]() -> State::Ptr
                {
                    return std::make_unique<T>(*this, mContext);
                };
        }

        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);

        void pushState(States::ID id);
        void popState();
        void clearStates();

        bool isEmpty() const;

    private:
        State::Ptr createState(States::ID id);
        void applyPendingChanges();

    private:
        std::vector<State::Ptr> mStack;

        struct PendingChange
        {
            Action action;
            States::ID stateID = States::None;
        };

        std::vector<PendingChange> mPendingList;
        std::map<States::ID, std::function<State::Ptr()>> mFactories;
        State::Context mContext;
    };

} // namespace ApplesGame