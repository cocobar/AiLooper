#include "stdafx.h"
#include "AiEarPerception.h"


AiEarPerception::AiEarPerception()
{
	pThreadProc = &WorkThread;
}


AiEarPerception::~AiEarPerception()
{
}

UINT AiEarPerception::WorkThread(LPVOID param) {
	AiEarPerception * pPerception = (AiEarPerception *)param;

	pPerception->setWorkState(AiPerception::WSE_RUNNING);

	// ���濪ʼ���pSoul����������ѭ��
	while (pPerception->wState != AiPerception::WSE_STOPPING) {

		// ��ʼ������Ϣ��Ϣѭ��
		// ����Ҫģ�Ⲣ�м�����Щ�Ѷ�


	}

	// ��ʼ��������

	//::Sleep(5000);// ����ģ��

	pPerception->setWorkState(AiPerception::WSE_STOPED);
	AfxEndThread(0, false);		// ������봫false��õȴ����������̵߳Ȳ���
	return 0;
}
