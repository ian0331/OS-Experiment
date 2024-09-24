package jobScheduling;

import java.util.ArrayList;
import java.util.Comparator;

public class MemoryProcess {
    public ArrayList<Job> entryMemoryJobs;
    public ArrayList<Job> finishedJobs;
    public Job nowProcess;
    public int systemTime;
    boolean out = false;
    public MemoryProcess(int systemTime) {
        this.entryMemoryJobs = new ArrayList<>();
        this.finishedJobs = new ArrayList<>();
        this.nowProcess = null;
        this.systemTime = systemTime;
    }

    public void excuteProcess() {
        if(!nowProcess.modifyStartTime) {
            nowProcess.startTime = systemTime;
            nowProcess.modifyStartTime = true;
        }
        systemTime++;
        nowProcess.RemainingRunTime--;
        if (nowProcess.RemainingRunTime == 0) {
            nowProcess.endTime = systemTime;
            nowProcess.turnaroundTime = nowProcess.endTime - nowProcess.arrivalTime;
            nowProcess.weightedTurnaroundTime = (double) nowProcess.turnaroundTime / nowProcess.estimatedRunTime;
            finishedJobs.add(nowProcess);
            entryMemoryJobs.remove(nowProcess);
            nowProcess = null;
        }
    }
    public void outPut(){
        finishedJobs.sort(Comparator.comparing(job -> job.arrivalTime));
        for(Job job : finishedJobs){
            if (!out) {
                out = true;
                System.out.println("+------+----------+--------------+----------+----------+----------+----------------+");
                System.out.println("| 作业  | 进入时间  | 估计运行时间   | 开始时间   | 结束时间  | 周转时间  | 带权周转时间     |");
                System.out.println("+------+----------+--------------+----------+----------+----------+----------------+");
            }
            String output = String.format("| %-4s | %-8s | %-12d | %-8s | %-8s | %-8d | %-14.2f |",
                    job.jobName,
                    TimeConverter.convertMinutesToTime(job.arrivalTime),
                    job.estimatedRunTime,
                    TimeConverter.convertMinutesToTime(job.startTime),
                    TimeConverter.convertMinutesToTime(job.endTime),
                    job.turnaroundTime,
                    job.weightedTurnaroundTime);
            System.out.println(output);
            if (entryMemoryJobs.size() == 1) {
                System.out.println("+------+----------+--------------+----------+----------+----------+----------------+");
            } else {
                System.out.println("+------+----------+--------------+----------+----------+----------+----------------+");
            }
        }
        // 添加表头

    }
    //先来先服务算法
    public void FCFS() {
        if (nowProcess == null) {
            if (!entryMemoryJobs.isEmpty()) {
                nowProcess = entryMemoryJobs.getFirst();
            } else {
                return;
            }
        }
        excuteProcess();
    }

    //短作业优先算法
    public void SJF() {
        if (!entryMemoryJobs.isEmpty()) {
            entryMemoryJobs.sort(Comparator.comparing(job -> job.RemainingRunTime));
            nowProcess = entryMemoryJobs.getFirst();
        } else {
            return;
        }

        excuteProcess();
    }

    //最高响应比优先算法
    public void HRN() {
        if (!entryMemoryJobs.isEmpty()) {
            for (Job allJob : entryMemoryJobs) {
                allJob.responseRatio = (1 + ((double) (systemTime - allJob.arrivalTime) / allJob.estimatedRunTime)) * (-1.0);
            }
            entryMemoryJobs.sort(Comparator.comparing(job -> job.responseRatio));
            nowProcess = entryMemoryJobs.getFirst();
        } else {
            return;
        }

        excuteProcess();
    }

    //基于优先数调度法
    public void HPF() {
        if (!entryMemoryJobs.isEmpty()) {
            entryMemoryJobs.sort(Comparator.comparing(job -> job.priority));
            nowProcess = entryMemoryJobs.getFirst();
        } else {
            return;
        }

        excuteProcess();
    }
}
