#pragma once
#include"Common.h"
#include"AgentManager.h"

class CAsyncBacktackAlg
{
private:
	char *mLuaScriptName;
	CAgentManager *mpAgentManager;
public:
	CAsyncBacktackAlg(char *ScriptName, int NumAgents, int NumAssignments);
	~CAsyncBacktackAlg();
	void StartAlgorhythm();
};

