#include "stdafx.h"
#include "AiSoul.h"


// �����һ����̬����
UINT AiSoul::MainSoilRunningThread(LPVOID lpParam)
{
	AiSoul * pSoul = (AiSoul *)lpParam;

	pSoul->setSoulState(AiSoul::SSE_RUNNING);

	pSoul->earPerception.start();
	pSoul->eyePerception.start();
	pSoul->mouthKinetic.start();

	// ���濪ʼ���pSoul����������ѭ��
	while (pSoul->sState != AiSoul::SSE_STOPPING) {

		// ��ʼ������Ϣ��Ϣѭ��
		// ����Ҫģ�Ⲣ�м�����Щ�Ѷ�


	}
	
	// ��ʼ��������

	//::Sleep(5000);// ����ģ��

	pSoul->mouthKinetic.stop();
	pSoul->eyePerception.stop();
	pSoul->earPerception.stop();
	pSoul->setSoulState(AiSoul::SSE_STOPED);
	AfxEndThread(0, false);		// ������봫false��õȴ����������̵߳Ȳ���
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

void AiSoul::Start()		// ��������Soul
{
	SoilThread = AfxBeginThread(MainSoilRunningThread, this, THREAD_PRIORITY_NORMAL,0,0,NULL);
}
void AiSoul::Sleep()		// ����˯��ģʽ
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
void AiSoul::Wakeup()		// ����
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
void AiSoul::Rebirth()		// ����
{
	Stop();
	Start();
}
void AiSoul::Stop()			// ֹͣ
{
	if (SoilThread != NULL) {
		DWORD ExitCode = 0;
		Wakeup();			// ����
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
