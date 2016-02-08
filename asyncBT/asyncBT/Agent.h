#pragma once
#include "Messenger.h"
#include "Common.h"
//class used to represent any actor in a multiagent system
//behaviour defined by scripts provided

class CAgent
{
private:
	// - Lua - //
	lua_State *mLuaState;
	const char *mLuaFunctionName;
	char *mLuaFileName;

	// - view of other agents - //
	std::vector<SAgentV> mAgentView;  // What this agent thinks the other agents assignments are
	std::vector<std::vector<SAgentV>> mNoGoodsList;	  // Values that are incopmpatible with lower priority agent
	
	// - agent identity - //
	int mUID;

	// - assignemnt - //
	int mAssaignment;			//interpreted by scripts into actual assignment
	int mNumPosibleAssignments;

	// - messenger - //
	CMessenger* mMessengerOut;


	// - Update Agent Constraints - //
	void AddToAgentView(const SAgentV &newView);
	void RemoveFromAgentView(int agent);
	bool CheckIfAgentConsistent(const SAgentV *agent);//checks to see if an agents assignment is incompatible with this agents values

public:
	CAgent(int NumAssignments, int UID, CMessenger* messenger, lua_State *LuaState,char* LuaScriptName);
	~CAgent();

	bool CheckConsistent();
	bool CheckConsistent(int i);
	bool GenerateNoGood();
	bool FindNewAssignment();
	void ReciveMessage(const SMessage *message);

	// - Getters - //
	int GetUID();
	int GetAssignment();
};


