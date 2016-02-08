#include "AgentManager.h"

CAgentManager::CAgentManager(int NumAgents, int NumAssignments, char* LuaFileName)
{
	mMessegeOut = new CMessenger();
	mSolutionExists = true;
	mSolutionFound = false;
	mLuaState = luaL_newstate();
	luaL_openlibs(mLuaState);
	mLuaFileName = LuaFileName;
	CAgent* lTempAgent;
	for (int i = 0; i < NumAgents; i++)
	{
		lTempAgent = new CAgent(NumAssignments, i, mMessegeOut, mLuaState, mLuaFileName);
		mAgentList.insert(std::make_pair(i, lTempAgent));
	}
}

CAgentManager::~CAgentManager()
{
	if (mMessegeOut != nullptr)
	{
		delete mMessegeOut;
		mMessegeOut = nullptr;
	}
	for (int i = 0; i < mAgentList.size(); i++)
	{
		if (mAgentList[i] != nullptr)
		{
			delete mAgentList[i];
			mAgentList[i] = nullptr;
		}
	}
	mAgentList.clear();
}

bool CAgentManager::UpdateMessages()
{
	if (mMessegeOut->IsMessengerEmpty())
	{
		return true;
	}
	SMessage lTempMessege;
	while (!mMessegeOut->IsMessengerEmpty())
	{
		lTempMessege = mMessegeOut->GetNextMessege();
		switch (lTempMessege.smType)
		{
		case Ok:
			for (int i = lTempMessege.smUIDFrom; i < mAgentList.size(); i++)
			{
				mAgentList[i]->ReciveMessage(&lTempMessege);
			}
			break;
		case NoGood:
			mAgentList[lTempMessege.smUIDTo]->ReciveMessage(&lTempMessege);
			break;
		default:
			break;
		}
	}
	return false;
}

bool CAgentManager::UpdateAgents()
{
	mSolutionFound = UpdateMessages();
	for (int i = 0; i < mAgentList.size() && mSolutionExists&&!mSolutionFound; i++)
	{
		mSolutionExists = mAgentList[i]->FindNewAssignment();
	}
	return mSolutionExists;
}

bool CAgentManager::SolutionFound()
{
	return mSolutionFound;
}

bool CAgentManager::SolutionExists()
{
	return mSolutionExists;
}

void CAgentManager::PrintValues()
{
	for (int i = 0; i < mAgentList.size(); i++)
	{
		std::cout << mAgentList[i]->GetUID() << " with value: " << mAgentList[i]->GetAssignment() << std::endl;
	}
}

int CAgentManager::GetNumAgents()
{
	return mAgentList.size();
}

int CAgentManager::GetAgentAssignment(int UID)
{
	for (int i = 0; i < mAgentList.size(); i++)
	{
		if (mAgentList[i]->GetUID() == UID)
		{
			return mAgentList[i]->GetAssignment();
		}
	}
	return -1;
}

std::map<int, CAgent*>* CAgentManager::GetAgentList()
{
	return &mAgentList;
}

CAgent * CAgentManager::GetAgent(int uid)
{
	return mAgentList[uid];
}
