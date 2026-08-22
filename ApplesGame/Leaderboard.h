#pragma once

#include <vector>
#include <string>

namespace ApplesGame
{
    struct Record
    {
        std::string name;
        int score;
    };

    class Leaderboard
    {
    public:
        void generate(int npcCount);
        const std::vector<Record>& getRecords() const;

    private:
        std::vector<Record> m_entries;
    };
}