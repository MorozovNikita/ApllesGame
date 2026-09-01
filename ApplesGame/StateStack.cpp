#include "StateStack.h"

#include <cassert>

namespace ApplesGame
{

    StateStack::StateStack(State::Context context)
        : mContext(context)
    {
    }

    void StateStack::update(sf::Time dt)
    {
        for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
        {
            if (!(*itr)->update(dt))
                break;
        }

        applyPendingChanges();
    }

    void StateStack::draw()
    {
        for (auto& state : mStack)
            state->draw();
    }

    void StateStack::handleEvent(const sf::Event& event)
    {
        for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
        {
            if (!(*itr)->handleEvent(event))
                break;
        }

        applyPendingChanges();
    }

    void StateStack::pushState(States::ID id)
    {
        mPendingList.push_back({ Action::Push, id });
    }

    void StateStack::popState()
    {
        mPendingList.push_back({ Action::Pop, States::None });
    }

    void StateStack::clearStates()
    {
        mPendingList.push_back({ Action::Clear, States::None });
    }

    bool StateStack::isEmpty() const
    {
        return mStack.empty();
    }

    State::Ptr StateStack::createState(States::ID id)
    {
        auto found = mFactories.find(id);
        assert(found != mFactories.end());
        return found->second();
    }

    void StateStack::applyPendingChanges()
    {
        for (const PendingChange& change : mPendingList)
        {
            switch (change.action)
            {
            case Action::Push:
                mStack.push_back(createState(change.stateID));
                break;

            case Action::Pop:
                if (!mStack.empty())
                    mStack.pop_back();
                break;

            case Action::Clear:
                mStack.clear();
                break;
            }
        }

        mPendingList.clear();
    }

}