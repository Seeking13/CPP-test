#include <iostream>
#include "ILift.h"
#include "常规模式.h"
using namespace std;

//状态模式
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
//子类定义
//子类具体实现时会互相调用，故必须提前声明
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
//子类实现
void StoppingState::Close(Context* context)
{
	//停止状态，可以转为运行状态，或者打开状态
	if (context->getCommand() == RUN_COMMAND)
	{
		printf("由停止状态  转为  运行状态！\n");
		context->setLiftState(new RunningState());
		context->getLiftState();
	}
	else if (context->getCommand() == OPEN_COMMAND)
	{
		printf("由停止状态  转为  打开状态！\n");
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
	//运行状态，只能转为停止状态，不能开门
	if (context->getCommand() == STOP_COMMAND)
	{
		printf("由运行状态  转为  停止状态！\n");
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
	//关闭状态，可以开门，可以移动
	if (context->getCommand() == OPEN_COMMAND)
	{
		printf("由关闭状态  转为  打开状态！\n");
		context->setLiftState(new OpenningState());
		context->getLiftState();
	}
	else if (context->getCommand() == RUN_COMMAND)
	{
		printf("由关闭状态  转为  运行状态！\n");
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
	//打开状态，只能关闭，不能移动
	if (context->getCommand() == CLOSE_COMMAND)
	{
		printf("由打开状态  转为  关闭状态！\n");
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

	liftstate = new StoppingState;//初始化在停止模式
	context = new Context(liftstate);

	//运行
	context->setCommand(RUN_COMMAND);
	context->getLiftState();			//①该步骤已经将liftstate的内存空间释放掉了

	//停止
	context->setCommand(STOP_COMMAND);
	context->getLiftState();
	//开门
	context->setCommand(OPEN_COMMAND);
	context->getLiftState();
	//关门
	context->setCommand(CLOSE_COMMAND);
	context->getLiftState();
	//运行
	context->setCommand(RUN_COMMAND);
	context->getLiftState();
	//测试在运行时能不能转换为开门状态
	context->setCommand(OPEN_COMMAND);
	context->getLiftState();

	printf("\n运行完毕\n");
	//delete liftstate;//该内存空间已经在①将内存释放掉了，不能再次释放
	delete context;
	printf("\n运行完毕\n");
}

int main()
{
	//main_01();
	main_02();
	system("pause");
	return 0;
}