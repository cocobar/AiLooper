#pragma once

#include "AiEarPerception.h"
#include "AiEyePerception.h"
#include "AiMouthKinetic.h"

class AiSoul
{
public:
	enum SoulStateEnum
	{
		SSE_INITED = 0,
		SSE_RUNNING,
		SSE_STOPPING,
		SSE_SLEEP,
		SSE_STOPED,
	};


private:
	CRITICAL_SECTION gCrit;
	SoulStateEnum sState;
	CWinThread * SoilThread;
	void setSoulState(SoulStateEnum sse);
	static UINT MainSoilRunningThread(LPVOID lpParam);

	AiEarPerception earPerception;
	AiEyePerception eyePerception;
	AiMouthKinetic  mouthKinetic;


public:
	AiSoul();
	virtual ~AiSoul();

	// 完整的生命周期接口
	void Start();		// 启动整个Soul
	void Sleep();		// 进入睡眠模式
	void Wakeup();		// 唤醒
	void Rebirth();		// 重生
	void Stop();		// 停止


};

