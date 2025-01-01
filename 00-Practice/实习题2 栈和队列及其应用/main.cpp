#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 2  // ͣ��������
#define MAX_QUEUE_SIZE 100  // ����������

typedef struct {
    int license_plate;
    int arrival_time;
} Car;// ���������ƺ͵���ʱ�� 

typedef struct {
    Car cars[MAX_CAPACITY];
    int top;
} Stack;

typedef struct {
    Car cars[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initStack(Stack *s) {
    s->top = -1;
}//ջ��ʼ�� 

int isStackFull(Stack *s) {
    return s->top == MAX_CAPACITY - 1;
}//�ж�ջ�Ƿ��� 

int isStackEmpty(Stack *s) {
    return s->top == -1;
}//�ж�ջ�Ƿ�� 

void push(Stack *s, Car car) {
    if (!isStackFull(s)) {
        s->cars[++s->top] = car;
    }
}//�������� 

Car pop(Stack *s) {
    if (!isStackEmpty(s)) {
        return s->cars[s->top--];
    }//������ȥ 
    Car emptyCar = {-1, -1};
    return emptyCar;//���ؿ� 
}

Car check(Stack *s) {
    if (!isStackEmpty(s)) {
        return s->cars[s->top];
    }//���ջ������ 
    Car emptyCar = {-1, -1};
    return emptyCar;//���ؿ� 
}

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}//��ʼ������ 

int isQueueFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}//�ж϶����Ƿ��� 

int isQueueEmpty(Queue *q) {
    return q->front == q->rear;
}//�ж϶����Ƿ�� 

void enqueue(Queue *q, Car car) {
    if (!isQueueFull(q)) {
        q->cars[q->rear] = car;
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    }
}//��� 

Car dequeue(Queue *q) {
    if (!isQueueEmpty(q)) {
        Car car = q->cars[q->front];
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        return car;
    }//���� 
    Car emptyCar = {-1, -1};
    return emptyCar;//���ؿ� 
}

void processArrival(Stack *parkingLot, Queue *sidewalk, int license_plate, int time) {
    if (!isStackFull(parkingLot)) {
        Car car = {license_plate, time};
        push(parkingLot, car);
        printf("����%dͣ��%d��ͣ��λ��\n", license_plate, parkingLot->top + 1);
    } //ͣ����δ��������ͣ���� 
	else {
        Car car = {license_plate, time};
        enqueue(sidewalk, car);
        printf("����%d��%d�ű���ϵȴ���\n", license_plate, (sidewalk->rear - sidewalk->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE);
    }//ͣ���������������� 
}

void processDeparture(Stack *parkingLot, Queue *sidewalk, int license_plate, int time) {
    Stack tempStack;
    initStack(&tempStack);
    int found = 0;
    while (!isStackEmpty(parkingLot)) {
        Car car = pop(parkingLot);
        if (car.license_plate == license_plate) /*�ж��Ƿ�ΪĿ�공��*/{
            found = 1;
            int t = time - car.arrival_time;
            int fee = t * 10;  // ÿ��ʱ�䵥λ�շ�10
            printf("����%d���뿪��ͣ��ʱ��: %d��λʱ��, ����: %d.\n", license_plate, t, fee);
            break;
        } //�Ƴ�Ŀ�공�� 
		else {
            push(&tempStack, car);
        }//��ͣ�����ڷ�Ŀ��������ʱ��ŵ���һ��ջ 
    }

    while (!isStackEmpty(&tempStack)) {
        push(parkingLot, pop(&tempStack));
    } //��ʱ���Ż�ȥ 

    if (!found) {
        printf("����%dδ����ͣ�������޷��Ƴ���\n", license_plate);
    }//����ʧ����� 

    if (!isQueueEmpty(sidewalk) && !isStackFull(parkingLot)) {
        Car car = dequeue(sidewalk);
        push(parkingLot, car);
        printf("����%d�ӱ������%d��ͣ��λ��\n", car.license_plate, parkingLot->top + 1);
    }//����������� 
}

int main() {
    Stack parkingLot;
    Queue sidewalk;
    initStack(&parkingLot);
    initQueue(&sidewalk);

    char events[][3] = {
        {'A', 1, 5},
        {'A', 2, 10},
        {'D', 1, 15},
        {'A', 3, 20},
        {'A', 4, 25},
        {'A', 5, 30},
        {'D', 2, 35},
        {'D', 4, 40},
        {'E', 0, 0}
    };

    int i = 0;
    while (events[i][0] != 'E') {
        char action = events[i][0];
        int license_plate = events[i][1];
        int time = events[i][2];

        if (action == 'A') {
            processArrival(&parkingLot, &sidewalk, license_plate, time);
        } else if (action == 'D') {
            processDeparture(&parkingLot, &sidewalk, license_plate, time);
        }
        i++;
    }

    printf("ģ����ɡ�\n");
    return 0;
}


