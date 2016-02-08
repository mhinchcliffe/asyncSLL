#pragma once

#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include"lua.hpp"
struct SAgentV
{
	int UID;
	int Value;
};

bool CompareSAgentV(const SAgentV &a, const SAgentV &b)
{
	if (a.UID == b.UID&&a.Value == b.Value) return true;
	else return false;
}

bool CompareSAgentVVector(std::vector<SAgentV> &a, std::vector<SAgentV> &b)
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

	bool lHitFound = false;
	for (int i = 0; i < lSmall.size()-1; i++)
	{
		lHitFound = false;
		for (int j = 0; j < lLarge.size() && lHitFound == false; j++)
		{
			if (CompareSAgentV(lSmall[i], lLarge[j])) lHitFound = true;
		}
		if (!lHitFound) return false;
	}
	return true;
}