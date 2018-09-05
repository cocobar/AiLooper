#pragma once
#include "AiPerception.h"
class AiEyePerception :
	public AiPerception
{
public:
	AiEyePerception();
	virtual ~AiEyePerception();

private:
	static UINT WorkThread(LPVOID param);
};

