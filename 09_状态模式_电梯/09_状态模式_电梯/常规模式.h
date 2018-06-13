#pragma once
#include <iostream>
#include "ILift.h"
using namespace std;

//״̬ģʽ
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
		cout << "��ǰ״̬:" << m_LIFE_STATE << endl;;
		return m_LIFE_STATE;
	}
	virtual void SetState(LIFT_STATE STATE) = 0;//���õ���״̬
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

		printf("�����Ŵ򿪣�\n");
	}
	virtual void Close()
	{
		printf("�����Źرգ�\n");
	}
	virtual void Run()
	{
		printf("�����������У�\n");
	}
	virtual void Stop()
	{
		printf("����ֹͣ��\n");
	}
	void SetState(LIFT_STATE STATE)
	{
		m_LIFE_STATE = STATE;
	}
};
void main_01();
