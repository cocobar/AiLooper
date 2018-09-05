#include "stdafx.h"
#include "AiSoul.h"


// 这个是一个静态函数
UINT AiSoul::MainSoilRunningThread(LPVOID lpParam)
{
	AiSoul * pSoul = (AiSoul *)lpParam;

	pSoul->setSoulState(AiSoul::SSE_RUNNING);

	pSoul->earPerception.start();
	pSoul->eyePerception.start();
	pSoul->mouthKinetic.start();

	// 下面开始针对pSoul这个对象进行循环
	while (pSoul->sState != AiSoul::SSE_STOPPING) {

		// 开始处理消息消息循环
		// 真正要模拟并行计算有些难度


	}
	
	// 开始回收垃圾

	//::Sleep(5000);// 用来模拟

	pSoul->mouthKinetic.stop();
	pSoul->eyePerception.stop();
	pSoul->earPerception.stop();
	pSoul->setSoulState(AiSoul::SSE_STOPED);
	AfxEndThread(0, false);		// 这里必须传false获得等待它结束的线程等不到
	return 0;
}

void AiSoul::setSoulState(SoulStateEnum sse) {
	EnterCriticalSection(&gCrit);
	sState = sse;
	LeaveCriticalSection(&gCrit);
}

AiSoul::AiSoul()
{
	SoilThread = NULL;
	sState = AiSoul::SSE_INITED;
	InitializeCriticalSection(&gCrit);
}


AiSoul::~AiSoul()
{
	Stop();
}

void AiSoul::Start()		// 启动整个Soul
{
	SoilThread = AfxBeginThread(MainSoilRunningThread, this, THREAD_PRIORITY_NORMAL,0,0,NULL);
}
void AiSoul::Sleep()		// 进入睡眠模式
{
	if (SoilThread != NULL) {
		if (sState == AiSoul::SSE_RUNNING) {
			SoilThread->SuspendThread();
			setSoulState(AiSoul::SSE_SLEEP);

			this->eyePerception.pause();
			this->earPerception.pause();
			this->mouthKinetic.pause();
		}
	}
}
void AiSoul::Wakeup()		// 唤醒
{
	if (SoilThread != NULL) {
		if (sState == AiSoul::SSE_SLEEP) {
			SoilThread->ResumeThread();
			setSoulState(AiSoul::SSE_RUNNING);

			this->mouthKinetic.resue();
			this->eyePerception.resue();
			this->earPerception.resue();
		}
	}
}
void AiSoul::Rebirth()		// 重生
{
	Stop();
	Start();
}
void AiSoul::Stop()			// 停止
{
	if (SoilThread != NULL) {
		DWORD ExitCode = 0;
		Wakeup();			// 唤醒
		setSoulState(AiSoul::SSE_STOPPING);

		while (WaitForSingleObject(SoilThread->m_hThread, 0) != WAIT_OBJECT_0) {};

		GetExitCodeThread(SoilThread->m_hThread, &ExitCode);

		EnterCriticalSection(&gCrit);
		delete SoilThread;
		SoilThread = NULL;
		sState = AiSoul::SSE_INITED;
		LeaveCriticalSection(&gCrit);
	}
}
