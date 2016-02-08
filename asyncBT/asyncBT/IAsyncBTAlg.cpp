// AsyncBtrackAIdll.cpp : Defines the exported functions for the DLL application.
//
#include "IAsyncBTAlg.h"

CAsyncBacktackAlg::CAsyncBacktackAlg(char *ScriptName, int NumAgents, int NumAssignments)
{
	mLuaScriptName = ScriptName;
	mpAgentManager = new CAgentManager(NumAgents, NumAssignments, ScriptName);
}

CAsyncBacktackAlg::~CAsyncBacktackAlg()
{
	if (mpAgentManager != nullptr)
	{
		delete mpAgentManager;
	}
	mpAgentManager = nullptr;
}

void CAsyncBacktackAlg::StartAlgorhythm()
{
	int count = 0;
	while (mpAgentManager->UpdateAgents() && !mpAgentManager->SolutionFound())
	{
		std::cout << "<<-iter" << count << "->>" << std::endl;
		count++;
	}
	if (mpAgentManager->SolutionFound())
	{
		std::cout << "solutuon found!!" << std::endl;
		mpAgentManager->PrintValues();
	}
	else
	{
		std::cout << "shit" << std::endl;
		mpAgentManager->PrintValues();
	}
	if (mpAgentManager)
	{
		delete mpAgentManager;
	}
	mpAgentManager = 0;
}




