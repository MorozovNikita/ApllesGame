#include "Leaderboard.h"

#include "Constants.h"

namespace ApplesGame
{
    void Leaderboard::generate(int count)
    {
        m_records.clear();

        for (int i{ 0 }; i < std::min(count, MAX_RECORDS); ++i)
            m_records.insert({ "Test"s + std::to_string(i), 10 * i});
    }

    const std::set<Record>& Leaderboard::getRecords() const
    {
        return m_records;
    }

    int Leaderboard::getScoreMinValue() const
    {
        if (m_records.empty())
            return -1;

        return m_records.crbegin()->score;
    }

    void Leaderboard::insertNewRecord(Record record)
    {
        m_records.insert(record);

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