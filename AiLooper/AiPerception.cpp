#include "stdafx.h"
#include "AiPerception.h"


AiPerception::AiPerception()
{
	pThreadProc = NULL;
	WorkThread = NULL;
	wState = AiPerception::WSE_INITED;
	InitializeCriticalSection(&gCrit);
}


AiPerception::~AiPerception()
{
	stop();
}

void AiPerception::setWorkState(WorkStateEnum wse) {
	EnterCriticalSection(&gCrit);
	wState = wse;
	LeaveCriticalSection(&gCrit);
}

void AiPerception::start() {
	if (pThreadProc) {
		WorkThread = AfxBeginThread(pThreadProc, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	}
}

void AiPerception::pause() {
	if (WorkThread != NULL) {
		if (wState == AiPerception::WSE_RUNNING) {
			WorkThread->SuspendThread();
			setWorkState(AiPerception::WSE_SLEEP);
		}
	}
}

void AiPerception::resue() {
	if (WorkThread != NULL) {
		if (wState == AiPerception::WSE_SLEEP) {
			WorkThread->ResumeThread();
			setWorkState(AiPerception::WSE_RUNNING);
		}
	}
}

void AiPerception::stop() {
	if (WorkThread != NULL) {
		DWORD ExitCode = 0;
		resue();			// »½ÐÑ
		setWorkState(AiPerception::WSE_STOPPING);

		while (WaitForSingleObject(WorkThread->m_hThread, 0) != WAIT_OBJECT_0) {};

		GetExitCodeThread(WorkThread->m_hThread, &ExitCode);

		EnterCriticalSection(&gCrit);
		delete WorkThread;
		WorkThread = NULL;
		wState = AiPerception::WSE_INITED;
		LeaveCriticalSection(&gCrit);
	}
}


