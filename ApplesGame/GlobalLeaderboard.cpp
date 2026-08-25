#include "GlobalLeaderboard.h"

#include <random>

#include "Constants.h"

namespace ApplesGame
{
    GlobalLeaderboard::GlobalLeaderboard(int size)
        : LeaderboardBase()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(15, 40);

        for (int i{ 0 }; i < std::min(size, MAX_RECORDS); ++i)
            m_records.insert({ "Test"s + std::to_string(i), dist(gen) });
    }

    GlobalLeaderboard::~GlobalLeaderboard()
    {
    }

    const std::set<Record>& GlobalLeaderboard::getRecords() const
    {
        return m_records;
    }

    int GlobalLeaderboard::getScoreMinValue() const
    {
        if (m_records.empty())
            return -1;

        return m_records.crbegin()->score;
    }

    size_t GlobalLeaderboard::size() const noexcept
    {
        return m_records.size();
    }

    void GlobalLeaderboard::insertNewRecord(Record record)
    {
        m_records.insert(std::move(record));

        while (m_records.size() > MAX_RECORDS)
        {
            m_records.erase(std::prev(m_records.end()));
        }
    }

    bool Record::operator<(const Record& other) const
    {
        if (score != other.score)
            return score > other.score;
        return name < other.name;
    }
}