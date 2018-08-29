#pragma once
class AiSoul
{
public:
	AiSoul();
	virtual ~AiSoul();

	// 完整的生命周期接口
	void Start();		// 启动整个Soul
	void Sleep();		// 进入睡眠模式
	void Wakeup();		// 唤醒
	void Rebirth();		// 重生
	void Stop();		// 停止


};

