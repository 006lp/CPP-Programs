#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int coef, exp;
	struct node *next;
} JD;

void add_poly(JD *pa, JD *pb) // ����ʽ�ļӷ�
{
	JD *p, *q, *u, *pre;
	int x;

	p = pa->next;
	q = pb->next;
	pre = pa;
	while ((p != NULL) && (q != NULL))
	{
		if (p->exp < q->exp)
		{
			pre = p;
			p = p->next;
		}
		else if (p->exp == q->exp)
		{
			x = p->coef + q->coef;
			if (x != 0)
			{
				p->coef = x;
				pre = p;
			}
			else
			{
				pre->next = p->next;
				free(p);
			}
			p = pre->next;
			u = q;
			q = q->next;
			free(u);
		}
		else
		{
			u = q->next;
			q->next = p;
			pre->next = q;
			pre = q;
			q = u;
		}
	}
	if (q != NULL)
		pre->next = q;
	pb->next = NULL;
}

bool write(JD *pa) // �������ʽpa
{
	JD *p;

	if (pa == NULL)
	{
		printf("0\n");
		return 0;
	}
	else
	{
		p = pa;
		while (p != NULL)
		{
			if (p->exp >= 0)
				break;
			else
				p = p->next;
		}
		if (p == NULL)
		{
			printf("0\n");
			return 0;
		}
		printf("%dx^%d", p->coef, p->exp);
		p = p->next;
		while (p != NULL)
		{
			if (p->coef >= 0)
				printf("+%dx^%d", p->coef, p->exp);
			else
				printf("-%dx^%d", -p->coef, p->exp);
			p = p->next;
		}
		printf("\n");
		return 1;
	}
}

void delnext(JD *p) // �ͷ������ڽڵ�p�Ժ�����нڵ�
{
	if (p == NULL)
		return;
	if (p->next != NULL)
	{
		delnext(p->next); // Ϊ���ͷ�p->next->next
		free(p->next);	  // �ͷ�p->next
		p->next = NULL;
	}
}

bool construct(JD *head) // ����һ���µĶ���ʽ
{
	JD *p, *p1;
	int n;
	char c;

	p = head;
	if (head == NULL)
		return 0;
	if (head->next != NULL)
		delnext(head); // ���head�Ѿ�����һ������ʽ�������ͷ�
	while (1)
	{
		printf("����ʽ�Ƿ���y/n?\n");
		scanf("%c", &c);
		getchar();
		if (c == 'n' || c == 'N')
			break;
		else if (c != 'y' && c != 'Y')
			continue;
		p1 = (JD *)malloc(sizeof(JD));
		p1->next = NULL;
		printf("����=");
		scanf("%d", &n);
		getchar();
		if (n <= p->exp)
		{
			printf("��Ч�Ĵ���");
			free(p1);
			continue;
		} // ����ʽ�Ĺ�������������׵ķ�ʽ
		else
			p1->exp = n;
		printf("ϵ��=");
		scanf("%d", &p1->coef);
		getchar(); // �������ʽϵ��
		p->next = p1;
		p = p1;
	}
}

int main()
{
	JD *Ahead, *Bhead;

	Ahead = (JD *)malloc(sizeof(JD));
	Ahead->exp = -1;
	Ahead->next = NULL;
	printf("�������ʽA(x):\n");
	construct(Ahead);

	Bhead = (JD *)malloc(sizeof(JD));
	Bhead->exp = -1;
	Bhead->next = NULL;
	printf("�������ʽB(x):\n");
	construct(Bhead);

	printf("\n����֮ǰ,  A(x)=");
	write(Ahead);
	add_poly(Ahead, Bhead);
	printf("\n����֮��,  A(x)=");
	write(Ahead);

	delnext(Ahead);
	free(Ahead);
	Ahead = NULL;
	delnext(Bhead);
	free(Bhead);
	Bhead = NULL; // ����β�����ͷ��ڴ�

	getchar();
	return 0;
}
