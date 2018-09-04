#pragma once
class AiSoul
{
public:
	enum SoulStateEnum
	{
		SSE_INITED = 0,
		SSE_RUNNING,
		SSE_STOPPING,
		SSE_SLEEP,
		SSE_STOPED,
	};


private:
	CRITICAL_SECTION gCrit;
	CWinThread * SoilThread;
	volatile SoulStateEnum sState;
	void setSoulState(SoulStateEnum sse);

	static UINT MainSoilRunningThread(LPVOID lpParam);



public:
	AiSoul();
	virtual ~AiSoul();

	// �������������ڽӿ�
	void Start();		// ��������Soul
	void Sleep();		// ����˯��ģʽ
	void Wakeup();		// ����
	void Rebirth();		// ����
	void Stop();		// ֹͣ


};

