#include <stdio.h>
int main(void)
{
	int i1=30;
	int i2=40;
	const int * pi=&i1;
	pi=&i2;    //4.ע�����pi����������ʱ�����¸�ֵһ�����ڴ��ַ
	i2=80;    //5.���뿴����������*pi=80;�������𣿵�Ȼ����
	printf("%d", *pi );  //6.�����80
	return 0;
}