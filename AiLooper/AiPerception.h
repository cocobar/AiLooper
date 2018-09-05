#pragma once
class AiPerception	// ¸ÐÖªÆ÷
{
public:
	enum WorkStateEnum
	{
		WSE_INITED = 0,
		WSE_RUNNING,
		WSE_STOPPING,
		WSE_SLEEP,
		WSE_STOPED,
	};

private:
	CRITICAL_SECTION gCrit;
	CWinThread * WorkThread;
	

public:
	volatile WorkStateEnum wState;
	void setWorkState(WorkStateEnum wse);
	AFX_THREADPROC pThreadProc;
	AiPerception();
	virtual ~AiPerception();
	virtual void start();
	virtual void pause();
	virtual void resue();
	virtual void stop();
};

