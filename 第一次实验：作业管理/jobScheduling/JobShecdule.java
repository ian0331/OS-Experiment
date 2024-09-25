package jobScheduling;

import java.util.ArrayList;
import java.util.Scanner;

public class JobShecdule {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Job> jobs = new ArrayList<>();
//        Job A = new Job("1", TimeConverter.convertTimeToMinutes("10:00"), 35,5);
//        Job B = new Job("2", TimeConverter.convertTimeToMinutes("10:10"), 30,3);
//        Job C = new Job("3", TimeConverter.convertTimeToMinutes("10:15"), 45,4);
//        Job D = new Job("4", TimeConverter.convertTimeToMinutes("10:20"), 20,6);
//        Job E = new Job("5", TimeConverter.convertTimeToMinutes("10:30"), 30,6);
////        Job A = new Job("1", TimeConverter.convertTimeToMinutes("10:00"), 40,5);
////        Job B = new Job("2", TimeConverter.convertTimeToMinutes("10:20"), 30,3);
////        Job C = new Job("3", TimeConverter.convertTimeToMinutes("10:30"), 50,4);
////        Job D = new Job("4", TimeConverter.convertTimeToMinutes("10:50"), 20,6);
        System.out.println("请输入CPU通道数：");
        int batches = scanner.nextInt();
        System.out.print("请输入作业数量：");
        int jobCount = scanner.nextInt();
        scanner.nextLine(); // 清除缓冲区

        for (int i = 0; i < jobCount; i++) {
            System.out.print("请输入作业名称：");
            String name = scanner.nextLine();
            System.out.print("请输入作业开始时间 (格式HH:MM)：");
            String startTime = scanner.nextLine();
            System.out.print("请输入作业运行时间（分钟）：");
            int runTime = scanner.nextInt();
            System.out.print("请输入作业优先级(没有输入0即可）：");
            int priority = scanner.nextInt();
            scanner.nextLine(); // 清除缓冲区

            Job job = new Job(name, TimeConverter.convertTimeToMinutes(startTime), runTime, priority);
            jobs.add(job);
        }

        SystemProcess sp = new SystemProcess(jobs);
        MemoryProcess mp = new MemoryProcess(sp.systemTime);

        System.out.println("请选择系统进程调度算法：");
        System.out.println("1. 先来先服务 (FCFS)");
        System.out.println("2. 最短作业优先 (SJF)");
        System.out.println("3. 最高响应比优先 (HRN)");
        System.out.println("4. 最高优先级优先 (HPF)");
        System.out.print("请输入选择（1-4）：");
        int spChoice = scanner.nextInt();

        System.out.println("请选择内存进程调度算法：");
        System.out.println("1. 先来先服务 (FCFS)");
        System.out.println("2. 最短作业优先 (SJF)");
        System.out.println("3. 最高响应比优先 (HRN)");
        System.out.println("4. 最高优先级优先 (HPF)");
        System.out.print("请输入选择（1-4）：");
        int mpChoice = scanner.nextInt();

        do {
            switch (spChoice) {
                case 1:
                    sp.FCFS();
                    break;
                case 2:
                    sp.SJF();
                    break;
                case 3:
                    sp.HRN();
                    break;
                case 4:
                    sp.HPF();
                    break;
                default:
                    System.out.println("无效选择，默认使用先来先服务 (FCFS)");
                    sp.FCFS();
            }

            if (!sp.enterSystemJobs.isEmpty()) {
                if (mp.entryMemoryJobs.isEmpty() || mp.entryMemoryJobs.size() < batches) {
                    mp.entryMemoryJobs.add(sp.enterSystemJobs.getFirst());
                    sp.enterSystemJobs.removeFirst();
                }
            }

            switch (mpChoice) {
                case 1:
                    mp.FCFS();
                    break;
                case 2:
                    mp.SJF();
                    break;
                case 3:
                    mp.HRN();
                    break;
                case 4:
                    mp.HPF();
                    break;
                default:
                    System.out.println("无效选择，默认使用先来先服务 (FCFS)");
                    mp.FCFS();
            }
        } while (!sp.allJobs.isEmpty() || !sp.enterSystemJobs.isEmpty() || mp.nowProcess != null || !mp.entryMemoryJobs.isEmpty());
        mp.outPut();
        scanner.close();
    }
}
