#include "����ģʽ.h"
void main_01()
{
	ILift* lift = new Lift;
	lift->getState();
	//�����ǵ����ſ������˽�ȥ  
	lift->Open();
	//Ȼ������Źر�  
	lift->Close();
	//��Ȼ�󣬵��������������ϻ�������  
	lift->Run();
	//��󵽴�Ŀ�ĵأ�����ͦ����  
	lift->Stop();
}
