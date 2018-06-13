#pragma once
#include <iostream>
#include "ILift.h"
using namespace std;

//状态模式
class ILift
{
public:
	ILift()
	{
		m_LIFE_STATE = STOP_STATE;
	}
public:
	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Run() = 0;
	virtual void Stop() = 0;
	LIFT_STATE getState()
	{
		cout << "当前状态:" << m_LIFE_STATE << endl;;
		return m_LIFE_STATE;
	}
	virtual void SetState(LIFT_STATE STATE) = 0;//设置电梯状态
protected:
	LIFT_STATE m_LIFE_STATE;
};

class Lift :public ILift
{
public:
	Lift() :ILift()
	{}
public:
	virtual void Open()
	{
		switch (m_LIFE_STATE)
		{
		case OPEN_STATE:
			//...
		case CLOSE_STATE:
			//...
			break;
		}

		printf("电梯门打开！\n");
	}
	virtual void Close()
	{
		printf("电梯门关闭！\n");
	}
	virtual void Run()
	{
		printf("电梯正在运行！\n");
	}
	virtual void Stop()
	{
		printf("电梯停止！\n");
	}
	void SetState(LIFT_STATE STATE)
	{
		m_LIFE_STATE = STATE;
	}
};
void main_01();
