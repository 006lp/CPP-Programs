#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "���ݽṹ";
	unsigned long long int code;
	unsigned int n;
	int i, k;
	char *p;

	k = strlen(str);

	code = 0;
	for (i = 0; i < 8; i++)
	{
		if (i < k)
		{
			n = (unsigned char)str[i];
			printf("��%dλ��ʮ���������%d\n", i, n); // ʵ��д����ʱ����Ҫ���
			printf("��%dλ��16���������%x\n", i, n);
		}
		else
			n = 0;
		code = code * 256 + n;
	}

	printf("������ʮ���Ʊ��������%llu\n", code);
	printf("������16���Ʊ��������%llx\n", code);

	return 0;
}
