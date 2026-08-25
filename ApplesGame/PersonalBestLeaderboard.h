#pragma once

#include <unordered_map>

#include "LeaderboardBase.h"

namespace ApplesGame
{
    class PersonalBestLeaderboard : public LeaderboardBase
    {
    public:
        PersonalBestLeaderboard(int size);
        ~PersonalBestLeaderboard() override;

        void insertNewRecord(Record record) override;

        const std::set<Record>& getRecords() const override;
        int getScoreMinValue() const override;
        size_t size() const noexcept override;

    private:
        void trimToMax();
        void rebuildSorted();

        std::unordered_map<std::string, int> m_records;
        std::set<Record> m_recordsSorted;
    };
}