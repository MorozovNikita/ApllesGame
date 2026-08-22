#include "Leaderboard.h"

namespace ApplesGame
{
    void Leaderboard::generate(int count)
    {
        m_entries.clear();

        for (int i{ 0 }; i < count; ++i)
            m_entries.push_back({ "Test", 120 });
    }

    const std::vector<Record>& Leaderboard::getRecords() const
    {
        return m_entries;
    }
}