#include "Agent.h"

void CAgent::AddToAgentView(const SAgentV &newView)
{
	bool FoundInList = false;
	if (mAgentView.size() != 0)
	{
		for (int i = 0; i < mAgentView.size() && !FoundInList; i++)
		{
			if (mAgentView[i].UID == newView.UID)
			{
				mAgentView[i].Value == newView.Value;
				FoundInList = true;
			}
		}
	}
	mAgentView.push_back(newView);
}

void CAgent::RemoveFromAgentView(int agent)
{
	std::vector<SAgentV> mAgentViewTemp;
	for (int i = 0; i < mAgentView.size(); i++)
	{
		if (mAgentView[i].UID != agent)
		{
			mAgentViewTemp.push_back(mAgentView[i]);
		}
	}
	mAgentView.clear();
	mAgentView = mAgentViewTemp;
}

bool CAgent::CheckIfAgentConsistent(const SAgentV * agent)
{
	//load lua
	luaL_dofile(mLuaState, mLuaFileName);
	lua_getglobal(mLuaState, mLuaFunctionName);

	bool lConsistent = false;
	//check if function exists
	if (lua_isnil(mLuaState, -1))
	{
		std::cout << "Funtion does not exist" << std::endl;
		lua_pop(mLuaState, 1);
	}
	else
	{
		std::cout << "yay" << std::endl;
		lua_pushnumber(mLuaState, mUID);
		lua_pushnumber(mLuaState, mAssaignment);
		lua_pushnumber(mLuaState, agent->UID);
		lua_pushnumber(mLuaState, agent->Value);
		lua_pcall(mLuaState, 6, 1, 0);
		lConsistent = lua_toboolean(mLuaState, -1);
		lua_pop(mLuaState, 1);

	}
	return lConsistent;
}

CAgent::CAgent(int NumAssignments, int UID, CMessenger * messenger, lua_State * LuaState, char* LuaScriptName)
	:mLuaFunctionName("gfCheckValid")
{
	mNumPosibleAssignments = NumAssignments;
	mUID = UID;
	mMessengerOut = messenger;
	mAssaignment = 0;

	std::vector<SAgentV> temp;
	SAgentV tempA;

	tempA.UID = mUID;
	tempA.Value = mAssaignment;
	temp.push_back(tempA);
	mMessengerOut->AddMessage(mUID, mUID, temp, Ok);

	mLuaState = LuaState;
	mLuaFileName = LuaScriptName;
}

CAgent::~CAgent()
{
}

bool CAgent::CheckConsistent()
{
	CheckConsistent(mAssaignment);
	return false;
}

bool CAgent::CheckConsistent(int i)
{
	lua_State* test;
	test = luaL_newstate();
	luaL_openlibs(test);
	luaL_dofile(test, "nQueens.lua");
	lua_getglobal(test, "gfCheckValid");
	if (lua_isnil(test, -1))
	{
		std::cout << "Funtion does not exist" << std::endl;
		lua_pop(test, 1);
	}
	else
	{
		for (int i = 0; i < mAgentView.size(); i++)
		{
			std::cout << "Yeah" << std::endl;
			lua_pushnumber(test, mUID);
			lua_pushnumber(test, i);
			lua_pushnumber(test, mAgentView[i].UID);
			lua_pushnumber(test, mAgentView[i].Value);
			lua_pcall(test, 6, 1, 0);
			if (!lua_toboolean(test, -1))
			{
				lua_pop(test, 1);
				return false;
			}
			lua_pop(test, 1);
		}
	}
	return true;
}

bool CAgent::GenerateNoGood()
{
	//find the the lowest priority agent whose assignment is inconsistent with this agents
	//current assignment, then remove that agent from the agent view list.
	bool lNoGoodFound = false;
	std::vector<SAgentV> NoGoodList;
	if (mAgentView.size() != 0)
	{
		int lLowestPriorityNogood=0;
		for (int i = mAgentView.size()-1; i >=0&&!lNoGoodFound; i--)
		{
			if (!CheckIfAgentConsistent(&mAgentView[i]))
			{
				lLowestPriorityNogood = i;
				lNoGoodFound = true;
			}
		}
		if (lNoGoodFound)
		{
			for (int i = 0; i <= lLowestPriorityNogood; i++)
			{
				NoGoodList.push_back(mAgentView[i]);
			}
			mMessengerOut->AddMessage(NoGoodList[NoGoodList.size() - 1].UID, mUID, NoGoodList, NoGood);
			RemoveFromAgentView(NoGoodList[NoGoodList.size() - 1].UID);
		}
	}
	return lNoGoodFound;
}

bool CAgent::FindNewAssignment()
{
	//if current assignment is problamatic, check all possible assignemts untill one is found
	//which is consistent with its agentview/nogoodlist. if no such assignment can be found,
	//generate a nogood and check again. if a noggod cannot be generated (e.g. the agent list is empty)
	//then return false to indicate there is no solution
	bool lViableAssignment;
	if (CheckConsistent())
	{
		return true;
	}

	for (int i = 0; i < mNumPosibleAssignments; i++)
	{
		lViableAssignment = true;
		//check new assignment against the nogood list
		for (int j = 0; j < mNoGoodsList.size() && lViableAssignment; j++)
		{
			if (cmnfnc::CompareSAgentVVector(mAgentView, mNoGoodsList[j]))
			{
				if (i == mNoGoodsList[j][mNoGoodsList[j].size() - 1].Value)
				{
					lViableAssignment = false;
				}
			}
		}

		//check the new assignment against the list of other assignments
		if (lViableAssignment)
		{
			lViableAssignment = CheckConsistent(i);
		}

		//if new assignment was consistent with both the no good list and the other agents,
		//set it as the new assignment and send a message to the other agents of the new assignment
		//otherwise, generate a noggood and try again
		if (lViableAssignment)
		{
			mAssaignment = i;
			std::vector<SAgentV> temp;
			SAgentV tempA;
			tempA.UID = mUID;
			tempA.Value = mAssaignment;
			temp.push_back(tempA);
			mMessengerOut->AddMessage(mUID, mUID, temp, Ok);
			return true;
		}
	}
	if (GenerateNoGood())
	{
		return FindNewAssignment();
	}
	else return false;
}

void CAgent::ReciveMessage(const SMessage * message)
{
	switch (message->smType)
	{
	case Ok:
		AddToAgentView(message->smMessage[0]);
		break;
	case NoGood:
		mNoGoodsList.push_back(message->smMessage);
		break;
	default:
		break;
	}
}

int CAgent::GetUID()
{
	return mUID;
}

int CAgent::GetAssignment()
{
	return mAssaignment;
}

