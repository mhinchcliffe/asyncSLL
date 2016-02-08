#include "Messenger.h"



CMessenger::CMessenger()
{
}

void CMessenger::AddMessage(int UIDTo, int UIDFrom, std::vector<SAgentV> Message, eMessegeType type)
{
	SMessage* lTemp = new SMessage;
	lTemp->smUIDTo = UIDTo;
	lTemp->smUIDFrom = UIDFrom;
	lTemp->smMessage = Message;
	lTemp->smType = type;
	mMessageList.push_back(lTemp);
}

void CMessenger::ClearMessegeList()
{
	for (int i = 0; i < mMessageList.size(); i++)
	{
		delete mMessageList[i];
	}
	mMessageList.clear();
}

bool CMessenger::IsMessengerEmpty()
{
	if (mMessageList.size() == 0)
	{
		return true;
	}
	else return false;
}

SMessage CMessenger::GetNextMessege()
{
	if (mMessageList.size() != 0)
	{
		SMessage temp;
		temp = *mMessageList[0];
		delete mMessageList[0];
		mMessageList.pop_front();
		return temp;
	}
	else return SMessage();
}
