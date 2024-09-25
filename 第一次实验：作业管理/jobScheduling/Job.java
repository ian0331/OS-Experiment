package jobScheduling;

public class Job {
    String jobName;
    int arrivalTime;
    int estimatedRunTime;
    int RemainingRunTime;
    int startTime;
    boolean modifyStartTime;
    int endTime;
    int turnaroundTime;
    double weightedTurnaroundTime;
    double responseRatio;
    int waitingTime;
    int priority;
    public Job(String jobName, int arrivalTime, int estimatedRunTime, int priority) {
        this.jobName = jobName;
        this.arrivalTime = arrivalTime;
        this.estimatedRunTime = estimatedRunTime;
        this.RemainingRunTime = estimatedRunTime;
        this.priority = priority;
        this.modifyStartTime = false;
    }
}
