#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

clock_t Start,End;  //计时工具

int main() 
{   int i;
    int n;
    int *data;
    
    n=1e4;
    Start = clock();  //计时开始 
    data=new int [n+1];
    
    srand((unsigned)time(0)); //利用时间变量来实现数据的随机性 
    for(i=1;i<=n;i++)  
	{
		data[i]=rand();  //生成随机数据 
		//printf("%d,",data[i]);
	}
	delete[]data;
	
	End = clock(); //计时结束 
	printf("计算耗时: %f秒。", (End-Start)/(double)CLK_TCK);  //计算耗时 
	
    return 0; 
} 
