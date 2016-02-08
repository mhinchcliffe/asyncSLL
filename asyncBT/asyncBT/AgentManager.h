#pragma once
#include "Common.h"
#include "Agent.h"
#include "Messenger.h"
//holds all the agents, and sens messeges to them. also used to gain access to agents directly.

class CAgentManager
{
private:
	std::map<int, CAgent*> mAgentList;
	std::map<int, CAgent*>::iterator mIttAL;
	CMessenger* mMessegeOut;
	lua_State *mLuaState;
	char* mLuaFileName;
	bool mSolutionExists;
	bool mSolutionFound;
public:
	//should only recive lua script name
	CAgentManager(int NumAgents, int NumAssignments,char* LuaFileName);
	~CAgentManager();

	// - Update Agents - //
	bool UpdateMessages();
	bool UpdateAgents();
	bool SolutionFound();
	bool SolutionExists();

	// -Print values - //
	void PrintValues();

	// - Getters - //
	int GetNumAgents();
	int GetAgentAssignment(int UID);
	std::map<int, CAgent*>* GetAgentList();
	CAgent* GetAgent(int uid);
};

