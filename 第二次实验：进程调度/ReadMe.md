# 进程调度模拟程序

*因为yy老师在小雅发了此次实验的c语言代码结构，故此次实验不再使用Java。*

## 简介

`ProcessScheduling.c` 是一个用C语言编写的进程调度模拟程序。该程序实现了三种不同的调度算法：多级反馈队列（Multiqueue）、优先级调度（Priority Scheduling）和时间片轮转调度（Round Robin）。用户可以选择其中一种算法来模拟进程调度的过程。

## 功能

- **多级反馈队列调度（Multiqueue Scheduling）**: 使用多个就绪队列，不同队列具有不同的优先级和时间片大小。
- **优先级调度（Priority Scheduling）**: 动态调整进程的优先级，每运行完一个时间片，优先级降低，并重新插入到合适的位置。
- **时间片轮转调度（Round Robin Scheduling）**: 每个进程分配一个固定的时间片，轮流执行。

## 使用方法

1. 编译代码：
   ```bash
   gcc -o ProcessScheduling ProcessScheduling.c
   ```

2. 运行程序：
   ```bash
   ./ProcessScheduling
   ```

3. 输入调度算法：
   - 输入 `MULTIQUEUE` 或 `mq` 选择多级反馈队列调度。
   - 输入 `PR` 或 `pr` 选择优先级调度。
   - 输入 `RR` 或 `rr` 选择时间片轮转调度。

4. 根据提示输入进程的名称、优先级（如果适用）和所需时间。

5. 按 `g` 键并回车以继续模拟过程。

## 代码结构

- **数据结构**: 使用链表来表示进程控制块（PCB），每个进程包含名称、优先级、所需时间、状态等信息。
- **函数**:
  - `Create`: 根据选择的算法创建进程并初始化队列。
  - `MultiqueueSch`: 实现多级反馈队列调度。
  - `PriSch`: 实现优先级调度。
  - `RoundSch`: 实现时间片轮转调度。
  - `print`: 打印当前的进程状态和队列信息。



该代码仅用于学习和研究目的。
