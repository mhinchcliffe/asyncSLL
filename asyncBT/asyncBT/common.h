#pragma once

#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include"lua.hpp"
#include<cmath>
#include<math.h>
struct SAgentV
{
	int UID;
	int Value;
};
namespace cmnfnc
{
	inline bool CompareSAgentV(const SAgentV &a, const SAgentV &b)
	{
		if (a.UID == b.UID&&a.Value == b.Value) return true;
		else return false;
	}

	inline bool CompareSAgentVVector(std::vector<SAgentV> &a, std::vector<SAgentV> &b)
	{
		std::vector<SAgentV> lSmall, lLarge;
		if (a.size() < b.size())
		{
			lSmall = a;
			lLarge = b;
		}
		else
		{
			lSmall = b;
			lLarge = a;
		}

		for (int i = 0; i < lSmall.size(); i++)
		{
			if (!cmnfnc::CompareSAgentV(lSmall[i], lLarge[i])) return false;
		}
		return true;
	}
}