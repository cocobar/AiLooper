#include "stdafx.h"
#include "AiEyePerception.h"


AiEyePerception::AiEyePerception()
{
	pThreadProc = &WorkThread;
}


AiEyePerception::~AiEyePerception()
{
}

UINT AiEyePerception::WorkThread(LPVOID param) {
	AiEyePerception * pPerception = (AiEyePerception *)param;

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
