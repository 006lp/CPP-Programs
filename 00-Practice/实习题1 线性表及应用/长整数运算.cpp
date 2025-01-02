#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<conio.h>
#include<windows.h>

/**双向循环链表的结构体定义**/
typedef struct Node{
    int data;
    struct Node *pre,*next;
}Node,*LinkList;

void InitList(LinkList &L)//初始化一个双向循环链表
{
	//表头结点数据域的符号代表长整数的符号
	//其绝对值表示元素结点数目
	L=(LinkList)malloc(sizeof(Node));
	L->data=0;
	L->next=L;
	L->pre=L;
}

void ListInsert(LinkList &L,int x)//在链表尾部插入一个值为x的结点
{
	LinkList p=(LinkList)malloc(sizeof(Node));
	LinkList q=L->pre;
	p->data=x;
	p->next=L;
	p->pre=q;
	q->next=p;
	L->pre=p;
	if(L->data>=0)L->data++;
	else L->data--;
}

void ListDelete(LinkList &L)//删去链表尾节点即高位
{
	if(L->data==0)return;
	LinkList p=L->pre;
	LinkList q=p->pre;
	q->next=L;
	L->pre=q;
	free(p);
	if(L->data>=0)L->data--;
	else L->data++;
}

void Adjust(LinkList &L)//对一个链表进行调整
{
	LinkList p=L->next;
 for (LinkList p = L->next; p != L; p = p->next) // 遍历链表
    {
		while(p->data>9999)//处理进位
		{
			if(p->next==L)ListInsert(L,0);
			p->next->data+=p->data/10000;
			p->data%=10000;
		}
	}
	while(L->pre->data==0&&abs(L->data)>1)ListDelete(L);//处理前导零
}	

int Compare(LinkList a,LinkList b)//比较两个数的绝对值大小a>b返回1 a=b返回2 a<b返回0
{
	if(abs(a->data)!=abs(b->data))
	{
		if(abs(a->data)>abs(b->data))return 1;
		else return 0;
	}
	LinkList p=a->pre,q=b->pre;
	while(p!=a&&q!=b)
	{
		if(p->data!=q->data)
		{
			if(p->data>q->data)return 1;
			else return 0;
		}
		p=p->pre;
		q=q->pre;
	}
	return 2;
}	

void Add(LinkList a, LinkList b, LinkList &c) // a + b = c
{
    if (a->data * b->data > 0) // ab同号
    {
        LinkList p = a->next, q = b->next;
        while (p != a && q != b)
        {
            ListInsert(c, p->data + q->data);
            p = p->next;
            q = q->next;
        }
        while (p != a)
        {
            ListInsert(c, p->data);
            p = p->next;
        }
        while (q != b)
        {
            ListInsert(c, q->data);
            q = q->next;
        }
        if (a->data < 0) c->data = -c->data;
    }
    else // ab异号
    {
        if (Compare(a, b) == 2) // a == b
        {
            ListInsert(c, 0);
            return;
        }
        else if (Compare(a, b) == 1) // a > b
        {
            LinkList p = a->next, q = b->next;
            while (p != a && q != b)
            {
                if (p->data < q->data) // 不够减则向上借位
                {
                    p->next->data--;
                    p->data += 10000;
                }
                ListInsert(c, p->data - q->data);
                p = p->next;
                q = q->next;
            }
            while (p != a)
            {
                ListInsert(c, p->data);
                p = p->next;
            }
            if (a->data < 0) c->data = -c->data; // 绝对值较大者确定符号
        }
        else if (Compare(a, b) == 0) // a < b
        {
            LinkList p = a->next, q = b->next;
            while (p != a && q != b)
            {
                if (q->data < p->data) // 不够减则向上借位
                {
                    q->next->data--;
                    q->data += 10000;
                }
                ListInsert(c, q->data - p->data);
                p = p->next;
                q = q->next;
            }
            while (q != b)
            {
                ListInsert(c, q->data);
                q = q->next;
            }
            if (b->data < 0) c->data = -c->data;
        }
    }
    Adjust(c); // 处理进位
}

void Sub(LinkList a,LinkList b,LinkList &c)//a-b=a+(-b)=c
{
	b->data=-b->data;
	Add(a,b,c);
	b->data=-b->data;
}

int GetNum(LinkList &L)//读取一个数
{
	char a[100000];
	int sum=0;
	scanf("%[^\n]",a);
	getchar();
	// 检查输入是否合法
	for(int i=0;i<strlen(a);i++) // 允许第一个字符为正负号，其余必须为数字
		if(!(i==0&&(a[0]=='-'||a[0]=='+'))&&(!(a[i]>='0'&&a[i]<='9')))
			return 0;
	int j=0;// 记录当前数字段的位数
    int i = strlen(a) - 1; // 初始化 i
    do
    {
        if (a[i] >= '0' && a[i] <= '9')
        {
            j++;
            if (j == 4 || i == 0 || (i == 1 && a[0] == '-'))
            {
                int num = 0; // 记录当前数字段的值
                for (int k = i; k < i + j; k++)
                    num = 10 * num + (a[k] - '0');
                ListInsert(L, num);
                j = 0;
            }
        }
        i--; // 移动到下一个字符
    } while (i >= 0);

    if (a[0] == '-') // 处理负数输入
        L->data = -L->data;

    if (L->data == 0) return 0;
    Adjust(L);
    return 1;
}

void Output(LinkList &L)//输出长整数
{
	LinkList p=L->pre;
	if(L->data<0)printf("-");
   for (bool first = true; p != L; p = p->pre) // 使用 for 循环遍历链表
    {
        if (!first) printf(","); // 在非第一个元素前打印逗号
        if (p->next != L) printf("%04d", p->data); 
        else printf("%d", p->data); 
        first = false; 
	}
	printf("\n");
}

int main()
{
    LinkList a,b,c;
    InitList(a);
    InitList(b);
    InitList(c);
    printf("Input number_A, end with ENTER\n");
    if(!GetNum(a)){printf("EORROR:wrong number\n");return 0;}
	//debug(a);
	//Output(a);
    printf("Input number_B, end with ENTER\n");
    if(!GetNum(b)){printf("EORROR:wrong number\n");return 0;}
    printf("Select an operation\n");
	printf("[1] +\n[2] -\n");
	char op=getch();
    if (op == '1')
	{printf("A + B = ");
    Add(a, b, c);
    Output(c);
     } 
    else if (op == '2')
	{printf("A - B = ");
    Sub(a, b, c);
    Output(c);
    } 
    else {
    printf("ERROR: wrong operation\n");
    return 0;
    }
	system("pause");//暂停程序查看结果
	return 0;
	
}
