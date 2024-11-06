#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#define NUMBER 5
#define NULL 0
#define PCBSTRUCT struct PCBSTR
typedef PCBSTRUCT *PCB;
enum Algorithm
{
    PR,
    RR,
    MQ
};
char Means[3];
char b;

PCBSTRUCT
{
    char Name[10];
    int Proi;
    int Round;
    int Queueno;
    int CpuTime;
    int NeedTime;
    int Count;
    char State;
    PCBSTRUCT *Next;
};

PCB Finish, Ready, Tail, Run;
PCB queues[3] = {NULL, NULL, NULL}; // 全局变量，三个优先级队列
int R[3] = {2, 4, 6};
void FirstIn()
{
    Run = Ready;
    Run->State = 'R';
    Ready = Ready->Next;
}
void Print1()
{

    printf("\n+----------+----------+----------+----------+----------+----------+\n");
    if ((strcmp(Means, "MQ") == 0) || (strcmp(Means, "mq") == 0))

        printf("| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Name", "CpuTime", "NeedTime", "Queueno", "Round", "State");
    else if ((strcmp(Means, "PR") == 0) || (strcmp(Means, "pr") == 0))
        printf("| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Name", "CpuTime", "NeedTime", "Priority", "Round", "State");

    else

        printf("| %-8s | %-8s | %-8s | %-8s | %-8s | %-8s |\n", "Name", "CpuTime", "NeedTime", "Count", "Round", "State");
    printf("+----------+----------+----------+----------+----------+----------+\n");
}
void waitForG()
{
    char ch;
    do
    {
        printf("Press 'g' and Enter to continue...");
        ch = getchar(); // 读取字符
        while (getchar() != '\n')
            ; // 清除输入缓冲区
    } while (ch != 'g'); // 等待 g 键
}
void print()

{

    PCB p;

    Print1();

    // 打印运行进程

    printf("It's the Run queue\n");
    printf("+----------+----------+----------+----------+----------+----------+\n");
    if (Run != NULL)

    {

        if ((strcmp(Means, "MQ") == 0) || (strcmp(Means, "mq") == 0))

            printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", Run->Name, Run->CpuTime, Run->NeedTime, 0, Run->Round, Run->State);
        else if ((strcmp(Means, "PR") == 0) || (strcmp(Means, "pr") == 0))

            printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", Run->Name, Run->CpuTime, Run->NeedTime, Run->Proi, Run->Round, Run->State);
        else
            printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", Run->Name, Run->CpuTime, Run->NeedTime, Run->Count, Run->Round, Run->State);
        printf("+----------+----------+----------+----------+----------+----------+\n");
    }

    // 打印就绪队列
    printf("It's the Ready queue\n");
    if ((strcmp(Means, "MQ") == 0) || (strcmp(Means, "mq") == 0))

    {

        for (int i = 0; i < 3; i++)
        {
            printf("Queue %d:\n", i);
            printf("+----------+----------+----------+----------+----------+----------+\n");

            p = queues[i];

            while (p != NULL)

            {
                printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", p->Name, p->CpuTime, p->NeedTime, p->Queueno, p->Round, p->State);
                p = p->Next;
            }
            printf("+----------+----------+----------+----------+----------+----------+\n");
        }
    }

    else

    {
        printf("+----------+----------+----------+----------+----------+----------+\n");
        p = Ready;
        while (p != NULL)

        {

            if ((strcmp(Means, "PR") == 0) || (strcmp(Means, "pr") == 0))
                printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", p->Name, p->CpuTime, p->NeedTime, p->Proi, p->Round, p->State);
            else

                printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", p->Name, p->CpuTime, p->NeedTime, p->Count, p->Round, p->State);

            p = p->Next;
        }

        printf("+----------+----------+----------+----------+----------+----------+\n");
    }

    // 打印完成队列
    printf("It's the Finished queue\n");
    printf("+----------+----------+----------+----------+----------+----------+\n");
    p = Finish;

    while (p != NULL)

    {
        if ((strcmp(Means, "MQ") == 0) || (strcmp(Means, "mq") == 0))

            printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", p->Name, p->CpuTime, p->NeedTime, 0, p->Round, p->State);
        else if ((strcmp(Means, "PR") == 0) || (strcmp(Means, "pr") == 0))

            printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", p->Name, p->CpuTime, p->NeedTime, p->Proi, p->Round, p->State);

        else

            printf("| %-8s | %-8d | %-8d | %-8d | %-8d | %-8c |\n", p->Name, p->CpuTime, p->NeedTime, p->Count, p->Round, p->State);

        p = p->Next;
    }

    printf("+----------+----------+----------+----------+----------+----------+\n");
}

void Insert2(PCB p2)
{
    Tail->Next = p2;
    Tail = p2;
    p2->Next = NULL;
}
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
// 按优先级插入到就绪队列
void InsertByPriority(PCB p)
{
    PCB current = Ready;
    PCB previous = NULL;

    // 找到合适的插入位置
    while (current != NULL && current->Proi >= p->Proi)
    {
        previous = current;
        current = current->Next;
    }

    // 插入到队列中
    if (previous == NULL)
    {
        p->Next = Ready;
        Ready = p;
    }
    else
    {
        previous->Next = p;
        p->Next = current;
    }

    // 更新尾指针
    if (p->Next == NULL)
    {
        Tail = p;
    }
}

void Create(enum Algorithm alg)
{
    PCB p;
    int i, time, priority;
    char Na[10];
    Ready = NULL;
    Finish = NULL;
    Run = NULL;
    if (alg == MQ)
    {
        printf("Input Name, Priority (0-2) and NeedTime\n");
        for (i = 0; i < NUMBER; i++)
        {
            scanf("%s", Na);
            scanf("%d", &priority);
            scanf("%d", &time);
            p = (PCB)malloc(sizeof(PCBSTRUCT));
            if (p == NULL) // 检查内存分配是否成功
            {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            strcpy(p->Name, Na);
            p->CpuTime = 0;
            p->NeedTime = time;
            p->Proi = priority; // 设置优先级
            p->Count = 0;
            p->State = 'W';
            p->Round = R[priority]; // 初始时间片为1

            // 插入到对应优先级的队列
            if (priority >= 0 && priority < 3)
            {
                p->Queueno = priority;
                p->Next = NULL; // 确保新节点的Next指针为NULL
                if (queues[priority] == NULL)
                {
                    queues[priority] = p; // 如果队列为空，直接将新节点作为头节点
                }
                else
                {
                    PCB temp = queues[priority];
                    while (temp->Next != NULL)
                    {
                        temp = temp->Next; // 找到队列的尾部
                    }
                    temp->Next = p; // 将新节点插入到队列尾部
                }
            }
            else
            {
                printf("Invalid priority! Must be between 0 and 2.\n");
                free(p);
            }
        }
    }
    else if (alg == PR)
    {
        printf("Input Name, Priority and NeedTime\n");
        for (i = 0; i < NUMBER; i++)
        {
            scanf("%s", Na);
            scanf("%d", &priority);
            scanf("%d", &time);
            p = (PCB)malloc(sizeof(PCBSTRUCT));
            strcpy(p->Name, Na);
            p->CpuTime = 0;
            p->NeedTime = time;
            p->Proi = priority; // 设置优先级
            p->Count = 0;
            p->State = 'W';
            p->Round = 2;
            InsertByPriority(p); // 按优先级插入到就绪队列
        }
    }
    else
    {
        printf("Input Name and NeedTime\n");
        Ready = NULL;
        for (i = 0; i < NUMBER; i++)
        {
            scanf("%s", Na);
            scanf("%d", &time);
            p = (PCB)malloc(sizeof(PCBSTRUCT));
            strcpy(p->Name, Na);
            p->CpuTime = 0;
            p->NeedTime = time;
            p->Count = 0;
            p->State = 'W';
            p->Round = 2;
            if (Ready != NULL)
                Insert2(p);
            else
            {
                p->Next = Ready;
                Ready = p;
                Tail = p;
            }
        }
    }
    if (alg == MQ)
        printf("Output Of Multiqueue:\n");
    else if (alg == PR)
        printf("Output Of Priority:\n");
    else
        printf("Output of RoundRobin:\n");
    if (Ready != NULL)
    {
        Run = Ready;
        Ready = Ready->Next;
        Run->State = 'R';
    }
}

// 多级反馈队列调度算法，有多个就绪队列，优先级和时间片大小不同。
void MultiqueueSch()
{
    int currentQueue = 0; // 当前处理的队列
    while (1)
    {
        // 找到下一个非空队列
        while (currentQueue < 3 && queues[currentQueue] == NULL)
        {
            currentQueue++;
        }

        // 如果所有队列都为空，调度结束
        if (currentQueue == 3)
        {
            break;
        }

        // 从当前队列中取出第一个进程
        Run = queues[currentQueue];
        queues[currentQueue] = queues[currentQueue]->Next;
        Run->Next = NULL;
        Run->State = 'R';
        print();
        // 运行进程
        while (Run != NULL)
        {
            Run->CpuTime++;
            Run->NeedTime--;
            Run->Count++;

            if (Run->NeedTime == 0)
            {
                Run->State = 'F';
                Run->Next = Finish;
                Finish = Run;
                Run = NULL;
            }
            else if (Run->Count == Run->Round)
            {
                Run->Count = 0;
                Run->State = 'W';

                // 如果当前队列不是最高优先级队列，降低优先级
                if (currentQueue < 2)
                {
                    Run->Queueno = currentQueue + 1;
                    Run->Round += 2;  // 增加时间片
                    Run->Next = NULL; // 确保新节点的Next指针为NULL
                    if (queues[currentQueue + 1] == NULL)
                    {
                        queues[currentQueue + 1] = Run; // 如果队列为空，直接将新节点作为头节点
                    }
                    else
                    {
                        PCB temp = queues[currentQueue + 1];
                        while (temp->Next != NULL)
                        {
                            temp = temp->Next; // 找到队列的尾部
                        }
                        temp->Next = Run; // 将新节点插入到队列尾部
                    }
                }
                else
                {
                    // 如果是最低优先级队列，重新插入到队列尾部
                    PCB temp = queues[currentQueue];
                    if (temp == NULL)
                    {
                        queues[currentQueue] = Run;
                    }
                    else
                    {
                        while (temp->Next != NULL)
                        {
                            temp = temp->Next;
                        }
                        temp->Next = Run;
                    }
                }
                Run = NULL;
            }
        }
        printf("========================================================================================\n");
        waitForG(); // 等待用户按下Enter键
    }
}

// 动态优先级和时间片轮转相结合的调度算法，每运行完一个时间片，优先级-5，重新插入到就绪队列适当的的位置
void PriSch()
{
    while (Run != NULL)
    {
        print();
        Run->CpuTime = Run->CpuTime + 1;
        Run->NeedTime = Run->NeedTime - 1;
        Run->Count = Run->Count + 1;
        if (Run->NeedTime == 0)
        {
            Run->Next = Finish;
            Finish = Run;
            Run->State = 'F';
            Run = NULL;
            if (Ready != NULL)
                FirstIn();
        }
        else if (Run->Count == Run->Round)
        {
            Run->Count = 0;
            Run->Proi = Run->Proi - 5; // 优先级降低
            if (Ready != NULL)
            {
                Run->State = 'W';
                InsertByPriority(Run); // 按优先级插入到就绪队列
                FirstIn();
            }
        }
        printf("========================================================================================\n");
        waitForG(); // 等待用户按下Enter键
    }
}

// 时间片轮转调度算法
void RoundSch()
{
    while (Run != NULL)
    {
        print();
        Run->CpuTime = Run->CpuTime + 1;
        Run->NeedTime = Run->NeedTime - 1;
        Run->Count = Run->Count + 1;
        if (Run->NeedTime == 0)
        {
            Run->Next = Finish;
            Finish = Run;
            Run->State = 'F';
            Run = NULL;
            if (Ready != NULL)
                FirstIn();
        }
        else if (Run->Count == Run->Round)
        {
            Run->Count = 0;
            if (Ready != NULL)
            {
                Run->State = 'W';
                Insert2(Run);
                FirstIn();
            }
        }
        printf("========================================================================================\n");
        waitForG(); // 等待用户按下Enter键
    }
}

int main()
{
    printf("Type then Algorithm:(Priority/RoundRobin)");
    scanf("%s", Means);
    clearInputBuffer(); // 清除缓冲区

    if ((strcmp(Means, "MULTIQUEUE") == 0) || (strcmp(Means, "mq") == 0))
    {
        Create(MQ);
        MultiqueueSch();
    }
    else if ((strcmp(Means, "PR") == 0) || (strcmp(Means, "pr") == 0))
    {
        Create(PR);
        PriSch();
    }
    else if ((strcmp(Means, "RR") == 0) || (strcmp(Means, "rr") == 0))
    {
        Create(RR);
        RoundSch();
    }
    else
        printf("Invalid Input!");
    printf("\nIt's Finished!");
    getchar();
    return 0;
}
