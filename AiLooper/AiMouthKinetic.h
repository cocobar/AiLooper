#pragma once
#include "AiKinetic.h"
class AiMouthKinetic :
	public AiKinetic
{
public:
	AiMouthKinetic();
	virtual ~AiMouthKinetic();

private:
	static UINT WorkThread(LPVOID param);
};
