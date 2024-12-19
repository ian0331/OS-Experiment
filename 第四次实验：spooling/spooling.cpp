#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <queue>
using namespace std;

// 进程控制块类
class PCB {
public:
    int status; // 进程状态 (0:空闲, 1:忙碌, 2:完成)
    int length; // 当前进程的数据总长度

    PCB() : status(0), length(0) {}
};

// 请求块类
class REQ {
public:
    int reqname; // 发起请求的用户编号
    int length;  // 本次请求的数据长度

    REQ() : reqname(0), length(0) {}
};

// 全局变量
const int BUFFER_SIZE = 100;  // 输出井大小
const int PCB_COUNT = 3;
const int REQ_COUNT = 10;

queue<int> buffer[2];     // 两个用户的输出井队列
int bufferSize[2] = {0, 0};  // 记录每个输出井当前的数据量
int head = 0;            // 请求队列的头指针
int tail = 0;            // 请求队列的尾指针
int t1 = 0;             // 用户1的剩余请求次数
int t2 = 0;             // 用户2的剩余请求次数

PCB pcb[PCB_COUNT];      // 3个PCB
REQ reqBlock[REQ_COUNT]; // 10个请求块组成的循环队列

// 打印分隔线
void printLine() {
    cout << "--------------------------------" << endl;
}

// 打印双线分隔
void printDoubleLine() {
    cout << "============================================================" << endl;
}

// 用户发起打印请求
void request(int i) {
    // 检查输出井是否已满
    if (bufferSize[i-1] >= BUFFER_SIZE) {
        cout << "\n";
        printDoubleLine();
        cout << "【用户" << i << "请求被暂停】" << endl;
        cout << "输出井" << i << "已满（当前使用量：" << bufferSize[i-1] << "/" << BUFFER_SIZE << "）" << endl;
        cout << "等待 SPOOLING 进程释放空间..." << endl;
        if (i == 1) t1++;
        else t2++;
        return;
    }

    if (i == 1)
        t1--;
    else
        t2--;

    cout << "\n";
    printDoubleLine();
    cout << "【用户" << i << "发起请求】" << endl;

    REQ &run = reqBlock[tail % REQ_COUNT];
    run.reqname = i;
    run.length = 0;

    // 随机生成打印数据
    int length = 0;
    cout << "\n生成的打印数据序列: ";
    while (bufferSize[i-1] + length < BUFFER_SIZE) {
        int j = (rand() % 9) + 1;
        if (rand() % 10 == 0 || length >= 20) { // 添加最大长度限制
            run.length = length;
            break;
        }

        buffer[i-1].push(j);
        cout << j << " ";
        length++;
    }

    bufferSize[i-1] += length;

    cout << "\n\n数据统计:" << endl;
    printLine();
    cout << "生成数据个数: " << length << endl;
    cout << "当前输出井" << i << "使用量: " << bufferSize[i-1] << "/" << BUFFER_SIZE << endl;
    pcb[i-1].length += length;
    cout << "PCB[" << i-1 << "] 累计长度: " << pcb[i-1].length << endl;
    printLine();

    if (pcb[2].status == 2) {
        pcb[2].status = 0;
    }
    tail++;
}

// SPOOLING输出服务程序
void spooling() {
    if (head == tail) {
        cout << "\n";
        printDoubleLine();
        cout << "【SPOOLING空闲】当前无待处理的请求" << endl;
        return;
    }

    cout << "\n";
    printDoubleLine();
    cout << "【SPOOLING输出服务】" << endl;

    REQ &run = reqBlock[head % REQ_COUNT];
    cout << "\n打印任务信息:" << endl;
    printLine();
    cout << "打印用户编号: " << run.reqname << endl;
    cout << "打印数据长度: " << run.length << endl;
    printLine();

    cout << "\n打印数据内容:" << endl;
    printLine();
    for (int i = 0; i < run.length; i++) {
        cout << buffer[run.reqname-1].front() << " ";
        buffer[run.reqname-1].pop();
    }
    cout << endl;
    printLine();

    bufferSize[run.reqname-1] -= run.length;
    cout << "输出井" << run.reqname << "空间已释放" << endl;
    cout << "当前输出井" << run.reqname << "使用量: "
         << bufferSize[run.reqname-1] << "/" << BUFFER_SIZE << endl;
    printLine();

    head++;

    for (int j = 0; j < 2; j++) {
        if (pcb[j].status == 1) {
            pcb[j].status = 0;
        }
    }
}

int main() {
    // 初始化
    t1 = t2 = 0;

    // 系统启动界面
    cout << "\n";
    printDoubleLine();
    cout << setw(45) << "SPOOLING系统启动" << endl;
    printDoubleLine();

    cout << "\n请输入任务参数:" << endl;
    printLine();
    cout << "input the times  of user1’s output file > ";
    cin >> t1;
    cout << "input the times  of user2’s output file > ";
    cin >> t2;
    printLine();

    // 初始化随机数种子
    srand(time(nullptr));

    // 主循环
    while (true) {
        int k = rand() % 100;
        cout << "\n";
        printDoubleLine();
        cout << "系统随机数: " << k << endl;

        if (k <= 45 && t1 > 0) {
            if (pcb[0].status == 0) {
                request(1);
            }
        }
        else if (k <= 90 && t2 > 0) {
            if (pcb[1].status == 0) {
                request(2);
            }
        }
        else {
            spooling();
        }

        if (t1 == 0 && t2 == 0 && head == tail) {
            break;
        }
    }

    cout << "\n";
    printDoubleLine();
    cout << setw(45) << "系统运行结束" << endl;
    printDoubleLine();

    return 0;
}