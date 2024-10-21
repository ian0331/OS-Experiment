package jobScheduling;

import java.util.ArrayList;
import java.util.Comparator;

public class SystemProcess {
    public ArrayList<Job> allJobs;
    public ArrayList<Job> enterSystemJobs;
    int systemTime;

    public SystemProcess(ArrayList<Job> allJobs) {
        enterSystemJobs = new ArrayList<>();
        this.allJobs = allJobs;
        // 按 arrivalTime 排序
        allJobs.sort(Comparator.comparing(job -> job.arrivalTime));
        this.systemTime = allJobs.getFirst().arrivalTime;
    }
    //先来先服务策略
    public void FCFS() {
        if (!allJobs.isEmpty()) {
            if (allJobs.getFirst().arrivalTime == systemTime) {
                enterSystemJobs.add(allJobs.getFirst());
                allJobs.removeFirst();
            }
        }
        systemTime++;
    }
    //短作业优先
    public void SJF(){
            if(!allJobs.isEmpty()){
                if(allJobs.getFirst().arrivalTime == systemTime) {
                    enterSystemJobs.add(allJobs.getFirst());
                    // 按 estimatedRunTime 排序
                    enterSystemJobs.sort(Comparator.comparing(job -> job.estimatedRunTime));
                    allJobs.removeFirst();
                }
            }
        systemTime++;
    }
    //最高响应比
    public void HRN() {
        if (!allJobs.isEmpty()) {
            if (allJobs.getFirst().arrivalTime == systemTime) {
                enterSystemJobs.add(allJobs.getFirst());
                for (Job allJob : enterSystemJobs) {
                    allJob.responseRatio = (1 + ((double) (systemTime - allJob.arrivalTime) / allJob.estimatedRunTime)) * (-1.0);
                }
                // 按 响应比 排序
                enterSystemJobs.sort(Comparator.comparing(job -> job.responseRatio));
                allJobs.removeFirst();
            }
        }
        systemTime++;

    }
//优先数调度算法
    public void HPF(){
        if(!allJobs.isEmpty()){
            if(allJobs.getFirst().arrivalTime == systemTime) {
                enterSystemJobs.add(allJobs.getFirst());
                // 按 priority 排序
                enterSystemJobs.sort(Comparator.comparing(job -> job.priority));
                allJobs.removeFirst();
            }
        }
        systemTime++;
    }
}
