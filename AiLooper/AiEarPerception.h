#pragma once
#include "AiPerception.h"
class AiEarPerception :
	public AiPerception
{
public:
	AiEarPerception();
	virtual ~AiEarPerception();

private:
	static UINT WorkThread(LPVOID param);
};

