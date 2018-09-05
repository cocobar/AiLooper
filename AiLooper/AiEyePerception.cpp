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

	// 下面开始针对pSoul这个对象进行循环
	while (pPerception->wState != AiPerception::WSE_STOPPING) {

		// 开始处理消息消息循环
		// 真正要模拟并行计算有些难度


	}

	// 开始回收垃圾

	//::Sleep(5000);// 用来模拟

	pPerception->setWorkState(AiPerception::WSE_STOPED);
	AfxEndThread(0, false);		// 这里必须传false获得等待它结束的线程等不到
	return 0;
}
