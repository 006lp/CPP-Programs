#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main()
{
	FILE *fp;
	char str1[10000];
	char*str2;
	int storage=100000;  //存储空间 
	int maxsize=10000000; //最大存储空间 
	
	fp=fopen("呐喊.txt","r");
	str2=(char *)malloc(sizeof(char)*storage);  
	str2[0]='\0';
	
	while((fgets(str1,10000,fp))!=NULL)  //fgets函数每次读取一段文字到str1指向的串中 
	{
	   if(strlen(str1)+strlen(str2)>storage)
	   {
	   if(storage+10000>maxsize)  break;
	   storage+=10000;
	   str2=(char *)realloc(str2,sizeof(char)*storage);
	   }
	   strcat(str2,str1);  //将str1中的文字连接到str2中 
	}
	fclose(fp);
	puts(str2);
	fp=fopen("呐喊.doc","w");
	fputs(str2,fp);
	fclose(fp);
	return 0;
}
