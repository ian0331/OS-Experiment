//
// Created by ian on 2024/11/19.
//实验 页面淘汰
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

int page, totalPages;
vector<int> pageDirection;
vector<vector<int>> ans;
vector<int> isReplaced;
void print_ans(const string& algorithm)
{
    // 打印列标题
    cout << "\n页面置换过程演示：\n\n";
    cout << algorithm << "\t";  // 显示对应的算法名称

    for(int i = 0; i < pageDirection.size(); i++) {
        cout << pageDirection[i] << "\t";
    }
    cout << "\n    \t";
    for(int i = 0; i < pageDirection.size(); i++) {
        cout << "--\t";
    }
    cout << endl;

    // 打印每一行的状态
    for(int i = 0; i < ans.size(); i++) {
        cout << "页" << i + 1 << " |\t";
        for(int j = 0; j < ans[i].size(); j++) {
            if(ans[i][j] != 0)
                cout << ans[i][j] << "\t";
            else
                cout << " \t";
        }
        cout << endl;
    }

    // 打印分隔线
    cout << "    \t";
    for(int i = 0; i < pageDirection.size(); i++) {
        cout << "--\t";
    }
    cout << endl;

    // 打印缺页标记
    cout << "缺页 |\t";
    for(int x : isReplaced) {
        if(x == 0)
            cout << "✓\t";
        else
            cout << "✗\t";
    }

    // 计算缺页率
    int faultCount = 0;
    for(int x : isReplaced) {
        if(x == 1) faultCount++;
    }
    double faultRate = (double)faultCount / isReplaced.size() * 100;

    cout << "\n\n缺页次数: " << faultCount;
    cout << "\n缺页率: " << fixed << setprecision(2) << faultRate << "%\n" << endl;
}

void FIFO()
{
    queue<int> pagesQueue;
    // 初始化ans大小
    ans.resize(totalPages, vector<int>(pageDirection.size(), 0));

    for(int i = 0; i < pageDirection.size(); i++)
    {

        // 检查当前页面是否已在队列中
        bool isExist = false;
        queue<int> temp = pagesQueue;
        while(!temp.empty()) {
            if(temp.front() == pageDirection[i]) {
                isExist = true;
                break;
            }
            temp.pop();
        }

        if(!isExist) {
            // 如果队列未满，直接添加
            if(pagesQueue.size() < totalPages) {
                pagesQueue.push(pageDirection[i]);
            }
                // 如果队列已满，移除最早的页面
            else {
                pagesQueue.pop();
                pagesQueue.push(pageDirection[i]);
            }
            isReplaced[i] = 1;
        }

        // 将当前队列状态记录到ans中
        queue<int> tempForAns = pagesQueue;
        int j = 0;
        while(!tempForAns.empty()) {
            ans[j][i] = tempForAns.front();
            tempForAns.pop();
            j++;
        }
    }

    print_ans("FIFO");
}

//理想页面置换算法
void OPT() {
    vector<int> memory(totalPages, 0);  // 当前内存中的页面
    // 初始化ans大小
    ans.resize(totalPages, vector<int>(pageDirection.size(), 0));

    for(int i = 0; i < pageDirection.size(); i++) {
        // 检查当前页面是否在内存中
        bool found = false;
        for(int j = 0; j < totalPages; j++) {
            if(memory[j] == pageDirection[i]) {
                found = true;
                break;
            }
        }

        if(!found) {
            // 需要进行页面置换
            isReplaced[i] = 1;

            // 如果内存还有空闲位置
            int emptySlot = -1;
            for(int j = 0; j < totalPages; j++) {
                if(memory[j] == 0) {
                    emptySlot = j;
                    break;
                }
            }

            if(emptySlot != -1) {
                memory[emptySlot] = pageDirection[i];
            } else {
                // 找出最远将被使用的页面
                vector<int> nextUse(totalPages, INT_MAX);
                for(int j = 0; j < totalPages; j++) {
                    for(int k = i + 1; k < pageDirection.size(); k++) {
                        if(memory[j] == pageDirection[k]) {
                            nextUse[j] = k;
                            break;
                        }
                    }
                }

                // 选择最远将被使用的页面进行置换
                int maxDist = -1;
                int replaceIndex = 0;
                for(int j = 0; j < totalPages; j++) {
                    if(nextUse[j] > maxDist) {
                        maxDist = nextUse[j];
                        replaceIndex = j;
                    }
                }
                memory[replaceIndex] = pageDirection[i];
            }
        }

        // 记录当前状态
        for(int j = 0; j < totalPages; j++) {
            ans[j][i] = memory[j];
        }
    }

    print_ans("OPT");
}
void LRU() {
    vector<int> memory(totalPages, 0);  // 当前内存中的页面
    vector<int> lastUsed(totalPages, -1);  // 记录每个内存位置上的页面最后使用时间
    // 初始化ans大小
    ans.resize(totalPages, vector<int>(pageDirection.size(), 0));

    for(int i = 0; i < pageDirection.size(); i++) {
        // 检查当前页面是否在内存中
        bool found = false;
        int foundIndex = -1;
        for(int j = 0; j < totalPages; j++) {
            if(memory[j] == pageDirection[i]) {
                found = true;
                foundIndex = j;
                break;
            }
        }

        if(found) {
            // 页面已在内存中，更新使用时间
            lastUsed[foundIndex] = i;
        } else {
            // 需要进行页面置换
            isReplaced[i] = 1;

            // 查找空闲位置或最久未使用的位置
            int replaceIndex = 0;
            int leastRecentlyUsed = INT_MAX;

            // 先找空闲位置
            bool hasEmpty = false;
            for(int j = 0; j < totalPages; j++) {
                if(memory[j] == 0) {
                    replaceIndex = j;
                    hasEmpty = true;
                    break;
                }
            }

            // 如果没有空闲位置，找最久未使用的页面
            if(!hasEmpty) {
                for(int j = 0; j < totalPages; j++) {
                    if(lastUsed[j] < leastRecentlyUsed) {
                        leastRecentlyUsed = lastUsed[j];
                        replaceIndex = j;
                    }
                }
            }

            // 替换页面
            memory[replaceIndex] = pageDirection[i];
            lastUsed[replaceIndex] = i;
        }

        // 记录当前状态
        for(int j = 0; j < totalPages; j++) {
            ans[j][i] = memory[j];
        }
    }

    print_ans("LRU");
}
void SC()
{
    vector<int> memory(totalPages, 0);  // 当前内存中的页面
    vector<int> R(totalPages, 1);   //初始R位都置0，一旦被使用就置1
    // 初始化ans大小
    ans.resize(totalPages, vector<int>(pageDirection.size(), 0));
    int point = 0;

    for(int i = 0; i < pageDirection.size(); i++) {
        // 检查当前页面是否在内存中
        bool found = false;
        int foundIndex = -1;
        for(int j = 0; j < totalPages; j++) {
            if(memory[j] == pageDirection[i]) {
                found = true;
                foundIndex = j;
                break;
            }
        }

        if(found) {
            // 页面已在内存中，更新R位
            R[foundIndex] = 1;
        } else {
            // 需要进行页面置换
            isReplaced[i] = 1;

            // 查找空闲位置或最久未使用的位置
            int replaceIndex = 0;

            // 先找空闲位置
            bool hasEmpty = false;
            for(int j = 0; j < totalPages; j++) {
                if(memory[j] == 0) {
                    replaceIndex = j;
                    hasEmpty = true;
                    break;
                }
            }

            // 如果没有空闲位置，找最久未使用的页面
            if(!hasEmpty) {
               while(true)
               {
                   if(R[point] == 0)
                   {
                       replaceIndex = point;
                       point ++ ;
                       point %= totalPages;
                       break;
                   }
                   else
                   {
                       R[point]--;
                       point ++ ;
                       point %= totalPages;
                   }
               }
            }

            // 替换页面
            memory[replaceIndex] = pageDirection[i];
            R[replaceIndex] = 1;
        }

        // 记录当前状态
        for(int j = 0; j < totalPages; j++) {
            ans[j][i] = memory[j];
        }
    }

    print_ans("SC");
}
//老化算法
void Aging() {
    vector<int> memory(totalPages, 0);  // 当前内存中的页面
    vector<unsigned char> counters(totalPages, 0);  // 8位计数器
    // 初始化ans大小
    ans.resize(totalPages, vector<int>(pageDirection.size(), 0));

    for(int i = 0; i < pageDirection.size(); i++) {
        // 先将所有计数器右移一位
        for(int j = 0; j < totalPages; j++) {
            counters[j] >>= 1;
        }

        // 检查当前页面是否在内存中
        bool found = false;
        int foundIndex = -1;
        for(int j = 0; j < totalPages; j++) {
            if(memory[j] == pageDirection[i]) {
                found = true;
                foundIndex = j;
                break;
            }
        }

        if(found) {
            // 页面已在内存中，设置最高位为1
            counters[foundIndex] |= 0x80;  // 设置最左位为1 (10000000)
        } else {
            // 需要进行页面置换
            isReplaced[i] = 1;

            // 查找空闲位置
            int replaceIndex = -1;
            for(int j = 0; j < totalPages; j++) {
                if(memory[j] == 0) {
                    replaceIndex = j;
                    break;
                }
            }

            // 如果没有空闲位置，找计数器值最小的页面
            if(replaceIndex == -1) {
                unsigned char minCount = 255;
                for(int j = 0; j < totalPages; j++) {
                    if(counters[j] < minCount) {
                        minCount = counters[j];
                        replaceIndex = j;
                    }
                }
            }

            // 替换页面
            memory[replaceIndex] = pageDirection[i];
            counters[replaceIndex] = 0x80;  // 新页面设置最高位为1
        }

        // 记录当前状态
        for(int j = 0; j < totalPages; j++) {
            ans[j][i] = memory[j];
        }
    }

    print_ans("Aging");
}
int main()
{
    cout << "请输入页面走向(直接按回车结束):" << endl;

    // 持续读取数字，直到输入非数字字符
    while (cin >> page) {
        pageDirection.push_back(page);

        // 检查下一个字符是否为换行符
        if (cin.get() == '\n') {
            break;
        }
    }
    isReplaced.resize(pageDirection.size(), 0);
    cout << "请输入页面总数:" << endl;
    cin >> totalPages;

    int choice;
    cout << "\n请选择页面置换算法:\n";
    cout << "1. FIFO (先进先出算法)\n";
    cout << "2. OPT (最佳置换算法)\n";
    cout << "3. LRU (最近最久未使用算法)\n";
    cout << "4. SC (第二次机会页面置换算法/时钟页面置换算法)\n";
    cout << "5. Aging (老化算法)\n";
    cout << "请输入选择 (1-4): ";
    cin >> choice;

    switch(choice) {
        case 1:
            FIFO();
            break;
        case 2:
            OPT();
            break;
        case 3:
            LRU();
            break;
        case 4:
            SC();
            break;
        case 5:
            Aging();
            break;
        default:
            cout << "无效的选择！" << endl;
    }

    return 0;
}
//4 3 2 1 4 3 5 4 3 2 1 5