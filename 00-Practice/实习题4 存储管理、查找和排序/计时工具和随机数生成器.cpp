#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

clock_t Start,End;  //��ʱ����

int main() 
{   int i;
    int n;
    int *data;
    
    n=1e4;
    Start = clock();  //��ʱ��ʼ 
    data=new int [n+1];
    
    srand((unsigned)time(0)); //����ʱ�������ʵ�����ݵ������ 
    for(i=1;i<=n;i++)  
	{
		data[i]=rand();  //����������� 
		//printf("%d,",data[i]);
	}
	delete[]data;
	
	End = clock(); //��ʱ���� 
	printf("�����ʱ: %f�롣", (End-Start)/(double)CLK_TCK);  //�����ʱ 
	
    return 0; 
} 
