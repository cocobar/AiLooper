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

	// 下面开始针对pSoul这个对象进行循环
	while (pPerception->wState != AiKinetic::WSE_STOPPING) {

		// 开始处理消息消息循环
		// 真正要模拟并行计算有些难度


	}

	// 开始回收垃圾

	//::Sleep(5000);// 用来模拟

	pPerception->setWorkState(AiKinetic::WSE_STOPED);
	AfxEndThread(0, false);		// 这里必须传false获得等待它结束的线程等不到
	return 0;
}
