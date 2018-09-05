#include "stdafx.h"
#include "AiKinetic.h"


AiKinetic::AiKinetic()
{
	pThreadProc = NULL;
	WorkThread = NULL;
	wState = AiKinetic::WSE_INITED;
	InitializeCriticalSection(&gCrit);
}


AiKinetic::~AiKinetic()
{
	stop();
}


void AiKinetic::setWorkState(WorkStateEnum wse) {
	EnterCriticalSection(&gCrit);
	wState = wse;
	LeaveCriticalSection(&gCrit);
}

void AiKinetic::start() {
	if (pThreadProc) {
		WorkThread = AfxBeginThread(pThreadProc, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	}
}

void AiKinetic::pause() {
	if (WorkThread != NULL) {
		if (wState == AiKinetic::WSE_RUNNING) {
			WorkThread->SuspendThread();
			setWorkState(AiKinetic::WSE_SLEEP);
		}
	}
}

void AiKinetic::resue() {
	if (WorkThread != NULL) {
		if (wState == AiKinetic::WSE_SLEEP) {
			WorkThread->ResumeThread();
			setWorkState(AiKinetic::WSE_RUNNING);
		}
	}
}

void AiKinetic::stop() {
	if (WorkThread != NULL) {
		DWORD ExitCode = 0;
		resue();			// »½ÐÑ
		setWorkState(AiKinetic::WSE_STOPPING);

		while (WaitForSingleObject(WorkThread->m_hThread, 0) != WAIT_OBJECT_0) {};

		GetExitCodeThread(WorkThread->m_hThread, &ExitCode);

		EnterCriticalSection(&gCrit);
		delete WorkThread;
		WorkThread = NULL;
		wState = AiKinetic::WSE_INITED;
		LeaveCriticalSection(&gCrit);
	}
}

