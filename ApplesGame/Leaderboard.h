#pragma once

#include <vector>
#include <string>
#include <set>

namespace ApplesGame
{
    struct Record
    {
        std::string name;
        int score;

        bool operator<(const Record& other) const;
    };

    class Leaderboard
    {
    public:
        Leaderboard(int size);
        ~Leaderboard() = default;

        const std::set<Record>& getRecords() const;
        int getScoreMinValue() const;

        void insertNewRecord(Record record);

    private:
        std::set<Record> m_records;
    };
}