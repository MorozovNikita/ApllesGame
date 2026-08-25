#pragma once

#include "LeaderboardBase.h"

namespace ApplesGame
{
    class GlobalLeaderboard : public LeaderboardBase
    {
    public:
        GlobalLeaderboard(int size);
        ~GlobalLeaderboard() override;

        void insertNewRecord(Record record) override;

        const std::set<Record>& getRecords() const override;
        int getScoreMinValue() const override;
        size_t size() const noexcept override;
        
    private:
        std::set<Record> m_records;
    };
}