#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main()
{
	FILE *fp;
	char str1[10000];
	char*str2;
	int storage=100000;  //�洢�ռ� 
	int maxsize=10000000; //���洢�ռ� 
	
	fp=fopen("�ź�.txt","r");
	str2=(char *)malloc(sizeof(char)*storage);  
	str2[0]='\0';
	
	while((fgets(str1,10000,fp))!=NULL)  //fgets����ÿ�ζ�ȡһ�����ֵ�str1ָ��Ĵ��� 
	{
	   if(strlen(str1)+strlen(str2)>storage)
	   {
	   if(storage+10000>maxsize)  break;
	   storage+=10000;
	   str2=(char *)realloc(str2,sizeof(char)*storage);
	   }
	   strcat(str2,str1);  //��str1�е��������ӵ�str2�� 
	}
	fclose(fp);
	puts(str2);
	fp=fopen("�ź�.doc","w");
	fputs(str2,fp);
	fclose(fp);
	return 0;
}
