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

    class LeaderboardBase
    {
    public:
        virtual ~LeaderboardBase() = default;

        LeaderboardBase(const LeaderboardBase&) = delete;
        LeaderboardBase& operator=(const LeaderboardBase&) = delete;

        LeaderboardBase(LeaderboardBase&&) = default;
        LeaderboardBase& operator=(LeaderboardBase&&) = default;

        virtual void insertNewRecord(Record record) = 0;

        [[nodiscard]] virtual const std::set<Record>& getRecords() const = 0;
        [[nodiscard]] virtual int getScoreMinValue() const = 0;
        [[nodiscard]] virtual size_t size() const noexcept = 0;

    protected:
        LeaderboardBase() = default;
    };

}