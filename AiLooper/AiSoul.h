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

	// �������������ڽӿ�
	void Start();		// ��������Soul
	void Sleep();		// ����˯��ģʽ
	void Wakeup();		// ����
	void Rebirth();		// ����
	void Stop();		// ֹͣ


};

