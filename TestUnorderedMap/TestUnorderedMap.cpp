// TestUnorderedMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <chrono>

#include <unordered_map>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
// class WriteTime - отображение времени
class ElapsedTimeHelper
{
public:

	ElapsedTimeHelper(int nStartIndex)
		: m_startIndex(nStartIndex),
		  m_startTime(std::chrono::high_resolution_clock::now())
	{
		std::cout << m_startIndex << "......processing.....";
	}

	~ElapsedTimeHelper()
	{
		const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = std::chrono::high_resolution_clock::now();

		auto elapsedTine = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - m_startTime).count();

		std::cout << m_startIndex << " : " << elapsedTine << " (ms);\n";
	}

private:

	const int                                                         m_startIndex;
	const std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
};

int main()
{
	using TMap = std::unordered_map<int, int>;
	TMap map;

	std::unique_ptr<ElapsedTimeHelper> pElapsedTimeHelper = std::make_unique<ElapsedTimeHelper>(0);

	for (int i = 0; i < 10000000; ++i)
	{
		if ((i % 1000) == 0)
		{
			pElapsedTimeHelper.reset();
			pElapsedTimeHelper = std::make_unique<ElapsedTimeHelper>(i);
		}

		map.insert(TMap::value_type(i, i));
	}

	pElapsedTimeHelper.reset();

    return 0;
}

