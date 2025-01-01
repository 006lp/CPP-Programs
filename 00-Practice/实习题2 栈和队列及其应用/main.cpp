#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 2  // 停车场容量
#define MAX_QUEUE_SIZE 100  // 便道最大容量

typedef struct {
    int license_plate;
    int arrival_time;
} Car;// 车辆号码牌和到达时间 

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
}//栈初始化 

int isStackFull(Stack *s) {
    return s->top == MAX_CAPACITY - 1;
}//判断栈是否满 

int isStackEmpty(Stack *s) {
    return s->top == -1;
}//判断栈是否空 

void push(Stack *s, Car car) {
    if (!isStackFull(s)) {
        s->cars[++s->top] = car;
    }
}//汽车进来 

Car pop(Stack *s) {
    if (!isStackEmpty(s)) {
        return s->cars[s->top--];
    }//汽车出去 
    Car emptyCar = {-1, -1};
    return emptyCar;//返回空 
}

Car check(Stack *s) {
    if (!isStackEmpty(s)) {
        return s->cars[s->top];
    }//检查栈顶汽车 
    Car emptyCar = {-1, -1};
    return emptyCar;//返回空 
}

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}//初始化队列 

int isQueueFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}//判断队列是否满 

int isQueueEmpty(Queue *q) {
    return q->front == q->rear;
}//判断队列是否空 

void enqueue(Queue *q, Car car) {
    if (!isQueueFull(q)) {
        q->cars[q->rear] = car;
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    }
}//入队 

Car dequeue(Queue *q) {
    if (!isQueueEmpty(q)) {
        Car car = q->cars[q->front];
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        return car;
    }//出队 
    Car emptyCar = {-1, -1};
    return emptyCar;//返回空 
}

void processArrival(Stack *parkingLot, Queue *sidewalk, int license_plate, int time) {
    if (!isStackFull(parkingLot)) {
        Car car = {license_plate, time};
        push(parkingLot, car);
        printf("车辆%d停在%d号停车位；\n", license_plate, parkingLot->top + 1);
    } //停车场未满，加入停车场 
	else {
        Car car = {license_plate, time};
        enqueue(sidewalk, car);
        printf("车辆%d在%d号便道上等待；\n", license_plate, (sidewalk->rear - sidewalk->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE);
    }//停车场已满，加入便道 
}

void processDeparture(Stack *parkingLot, Queue *sidewalk, int license_plate, int time) {
    Stack tempStack;
    initStack(&tempStack);
    int found = 0;
    while (!isStackEmpty(parkingLot)) {
        Car car = pop(parkingLot);
        if (car.license_plate == license_plate) /*判断是否为目标车辆*/{
            found = 1;
            int t = time - car.arrival_time;
            int fee = t * 10;  // 每个时间单位收费10
            printf("车辆%d已离开，停车时间: %d单位时间, 费用: %d.\n", license_plate, t, fee);
            break;
        } //移除目标车辆 
		else {
            push(&tempStack, car);
        }//将停车场内非目标汽车临时存放到另一个栈 
    }

    while (!isStackEmpty(&tempStack)) {
        push(parkingLot, pop(&tempStack));
    } //临时车放回去 

    if (!found) {
        printf("车辆%d未进入停车场，无法移除；\n", license_plate);
    }//查找失败输出 

    if (!isQueueEmpty(sidewalk) && !isStackFull(parkingLot)) {
        Car car = dequeue(sidewalk);
        push(parkingLot, car);
        printf("车辆%d从便道移入%d号停车位；\n", car.license_plate, parkingLot->top + 1);
    }//便道车辆移入 
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

    printf("模拟完成。\n");
    return 0;
}


