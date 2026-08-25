#include "PersonalBestLeaderboard.h"

#include <random>

#include "Constants.h"

namespace ApplesGame
{
	ApplesGame::PersonalBestLeaderboard::PersonalBestLeaderboard(int size)
		: LeaderboardBase()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(15, 40);

		for (int i{ 0 }; i < std::min(size, MAX_RECORDS); ++i)
			m_records.insert({ "Test"s + std::to_string(i), dist(gen) });

		rebuildSorted();
	}

	PersonalBestLeaderboard::~PersonalBestLeaderboard()
	{
	}

	void PersonalBestLeaderboard::insertNewRecord(Record record)
	{
		auto it = m_records.find(record.name);
		if (it == m_records.end())
			m_records[record.name] = record.score;
		else
		{
			if (record.score > it->second)
				it->second = record.score;
		}

		trimToMax();
		rebuildSorted();
	}

	const std::set<Record>& PersonalBestLeaderboard::getRecords() const
	{
		return m_recordsSorted;
	}

	int PersonalBestLeaderboard::getScoreMinValue() const
	{
		if (m_records.empty())
			return -1;

		return m_recordsSorted.crbegin()->score;
	}

	size_t PersonalBestLeaderboard::size() const noexcept
	{
		return m_records.size();
	}

	void PersonalBestLeaderboard::trimToMax()
	{
		if (m_records.size() <= MAX_RECORDS)
			return;

		auto worst = std::min_element(m_records.begin(), m_records.end(), 
									  [](const auto& a, const auto& b) 
									  { 
									       return a.second < b.second; 
									  });

		if (worst != m_records.end())
			m_records.erase(worst);
	}

	void PersonalBestLeaderboard::rebuildSorted()
	{
		m_recordsSorted.clear();

		for (const auto& [name, score] : m_records)
			m_recordsSorted.insert({ name, score });
	}
}