#include "stdafx.h"
#include "AiMouthKinetic.h"


AiMouthKinetic::AiMouthKinetic()
{
	pThreadProc = &WorkThread;
}


AiMouthKinetic::~AiMouthKinetic()
{
}


UINT AiMouthKinetic::WorkThread(LPVOID param) {
	AiMouthKinetic * pPerception = (AiMouthKinetic *)param;

	pPerception->setWorkState(AiKinetic::WSE_RUNNING);

	// ���濪ʼ���pSoul����������ѭ��
	while (pPerception->wState != AiKinetic::WSE_STOPPING) {

		// ��ʼ������Ϣ��Ϣѭ��
		// ����Ҫģ�Ⲣ�м�����Щ�Ѷ�


	}

	// ��ʼ��������

	//::Sleep(5000);// ����ģ��

	pPerception->setWorkState(AiKinetic::WSE_STOPED);
	AfxEndThread(0, false);		// ������봫false��õȴ����������̵߳Ȳ���
	return 0;
}
