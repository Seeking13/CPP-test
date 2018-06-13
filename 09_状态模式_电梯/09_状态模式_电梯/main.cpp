#include <iostream>
#include "ILift.h"
#include "����ģʽ.h"
using namespace std;

//״̬ģʽ
class Context;
class LiftState
{
public:
	virtual void Open() {};
	virtual void Close() {};
	virtual void Run() {};
	virtual void Stop() {};
	virtual void CurrentState(Context* context) = 0;
};

class Context
{
public:
	Context(LiftState *liftstate)
		:m_liftstate(liftstate), m_LIFECOMMAND(STOP_COMMAND)
	{

	}
	~Context()
	{
		delete m_liftstate;
	}
	LIFT_COMMAND getCommand()
	{
		return m_LIFECOMMAND;
	}
	void setCommand(LIFT_COMMAND command)
	{
		m_LIFECOMMAND = command;
	}

	void setLiftState(LiftState *liftstate)
	{
		delete m_liftstate;
		m_liftstate = liftstate;
	}
	void getLiftState()
	{
		m_liftstate->CurrentState(this);
	}
private:
	LiftState		*m_liftstate;
	LIFT_COMMAND	m_LIFECOMMAND;
};
 

//----------------------------------------------
//���ඨ��
//�������ʵ��ʱ�ụ����ã��ʱ�����ǰ����
class StoppingState :public LiftState
{
public:
	void Close(Context* context);
	virtual void CurrentState(Context* context);
};

class RunningState :public LiftState
{
public:
	void Run(Context* context);
	virtual void CurrentState(Context* context);
};

class ClosingState :public LiftState
{
public:
	void Close(Context* context);
	virtual void CurrentState(Context* context);
};

class OpenningState :public LiftState
{
public:
	void Open(Context* context);
	virtual void CurrentState(Context* context);
};

//-------------------------------------------------
//����ʵ��
void StoppingState::Close(Context* context)
{
	//ֹͣ״̬������תΪ����״̬�����ߴ�״̬
	if (context->getCommand() == RUN_COMMAND)
	{
		printf("��ֹͣ״̬  תΪ  ����״̬��\n");
		context->setLiftState(new RunningState());
		context->getLiftState();
	}
	else if (context->getCommand() == OPEN_COMMAND)
	{
		printf("��ֹͣ״̬  תΪ  ��״̬��\n");
		context->setLiftState(new OpenningState());
		context->getLiftState();
	}
}

void StoppingState::CurrentState(Context* context)
{
	Close(context);
}


void RunningState::Run(Context* context)
{
	//����״̬��ֻ��תΪֹͣ״̬�����ܿ���
	if (context->getCommand() == STOP_COMMAND)
	{
		printf("������״̬  תΪ  ֹͣ״̬��\n");
		context->setLiftState(new StoppingState());
		context->getLiftState();
	}
}
void RunningState::CurrentState(Context* context)
{
	Run(context);
}


void ClosingState::Close(Context* context)
{
	//�ر�״̬�����Կ��ţ������ƶ�
	if (context->getCommand() == OPEN_COMMAND)
	{
		printf("�ɹر�״̬  תΪ  ��״̬��\n");
		context->setLiftState(new OpenningState());
		context->getLiftState();
	}
	else if (context->getCommand() == RUN_COMMAND)
	{
		printf("�ɹر�״̬  תΪ  ����״̬��\n");
		context->setLiftState(new RunningState());
		context->getLiftState();
	}
}
void ClosingState::CurrentState(Context* context)
{
	Close(context);
}

void OpenningState::Open(Context* context)
{
	//��״̬��ֻ�ܹرգ������ƶ�
	if (context->getCommand() == CLOSE_COMMAND)
	{
		printf("�ɴ�״̬  תΪ  �ر�״̬��\n");
		context->setLiftState(new ClosingState());
		context->getLiftState();
	}
}
void OpenningState::CurrentState(Context* context)
{
	Open(context);
}

void main_02()
{
	Context		*context = NULL;
	LiftState	*liftstate = NULL;

	liftstate = new StoppingState;//��ʼ����ֹͣģʽ
	context = new Context(liftstate);

	//����
	context->setCommand(RUN_COMMAND);
	context->getLiftState();			//�ٸò����Ѿ���liftstate���ڴ�ռ��ͷŵ���

	//ֹͣ
	context->setCommand(STOP_COMMAND);
	context->getLiftState();
	//����
	context->setCommand(OPEN_COMMAND);
	context->getLiftState();
	//����
	context->setCommand(CLOSE_COMMAND);
	context->getLiftState();
	//����
	context->setCommand(RUN_COMMAND);
	context->getLiftState();
	//����������ʱ�ܲ���ת��Ϊ����״̬
	context->setCommand(OPEN_COMMAND);
	context->getLiftState();

	printf("\n�������\n");
	//delete liftstate;//���ڴ�ռ��Ѿ��ڢٽ��ڴ��ͷŵ��ˣ������ٴ��ͷ�
	delete context;
	printf("\n�������\n");
}

int main()
{
	//main_01();
	main_02();
	system("pause");
	return 0;
}