#include "常规模式.h"
void main_01()
{
	ILift* lift = new Lift;
	lift->getState();
	//首先是电梯门开启，人进去  
	lift->Open();
	//然后电梯门关闭  
	lift->Close();
	//再然后，电梯跑起来，向上或者向下  
	lift->Run();
	//最后到达目的地，电梯挺下来  
	lift->Stop();
}
