#pragma once
#include "common.h"
//used to store messenges for the entity manager
enum eMessegeType
{
	Ok,
	NoGood
};

struct SMessage
{
	int smUIDTo;
	int smUIDFrom;
	std::vector<SAgentV> smMessage;
	eMessegeType smType;
};

class CMessenger
{
private:
	std::deque<SMessage*> mMessageList;
public:
	CMessenger();

	void AddMessage(int UIDTo, int UIDFrom, std::vector<SAgentV> Message, eMessegeType type);
	void ClearMessegeList();
	bool IsMessengerEmpty();

	SMessage GetNextMessege();
};

