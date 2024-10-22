import java.util.Arrays;
import java.util.Scanner;
//银行家算法
public class BankerAlgorithm {
    public int numProcesses;       // 进程的数量
    public int numResourceTypes;   // 资源种类的数量
    public int[][] Max;            //最大需求矩阵
    public int[][] Allocation;     //分配矩阵
    public int[][] Need;           //需求矩阵
    public int[] Available;        //系统可用（剩余）资源量
    public int[] Work;             //工作向量
    public int nowProcess;         //当前正在请求分配资源的进程
    public int[] Request;          //进程申请资源向量
    public int[] Answer;           //辅助数组，记录安全序列
    public boolean[] finished;     //标记已完成的进程
    public BankerAlgorithm(int numProcesses, int numResourceTypes) {
        //构造函数，初始化
        this.numProcesses = numProcesses;
        this.numResourceTypes = numResourceTypes;
        this.Max = new int[numProcesses][numResourceTypes];
        this.Allocation = new int[numProcesses][numResourceTypes];
        this.Need = new int[numProcesses][numResourceTypes];
        this.Available = new int[numResourceTypes];
        this.finished =  new boolean[numProcesses];
        this.Work = new int[numResourceTypes];
        this.Request = new int[numResourceTypes];
        this.Answer = new int[numProcesses];
    }
    public void request() {
        
        //请求分配资源
        for (int i = 0; i < numResourceTypes; i++) {
            if (Request[i] > Need[nowProcess][i]) {
                System.out.println("出错，进程申请的资源多于它自己申报的最大量");
                return;
            }
            if (Request[i] > Available[i]) {
                System.out.println("尚无足够资源，需等待");
                return;
            }
        }
        //尝试分配资源
        for (int i = 0; i < numResourceTypes; i++) {
            Available[i] -= Request[i];
            Allocation[nowProcess][i] += Request[i];
            Need[nowProcess][i] -= Request[i];
        }
        if(security()){
            System.out.println("当前状态安全，实施分配，其中一个安全序列为:");
            for(int i =0;i<numProcesses;i++){
                if(i == (numProcesses - 1)){
                    System.out.print((Answer[i]));
                }else{
                    System.out.print((Answer[i])+"->");
                }
            }
        }else{
            //恢复原来的状态
            for (int i = 0; i < numResourceTypes; i++) {
                Available[i] += Request[i];
                Allocation[nowProcess][i] -= Request[i];
                Need[nowProcess][i] += Request[i];
            }
            System.out.println("当前状态不安全,拒绝分配，恢复原来的系统状态，进程等待");
        }

    }
    public boolean security() {
            //安全性检查函数
        // 重置 Work 和 finished
        System.arraycopy(Available, 0, Work, 0, numResourceTypes);
        Arrays.fill(finished, false);
        int count = 0; // 用于记录已完成的进程数量
        while (count < numProcesses) {
            boolean found = false;
            for (int i = 0; i < numProcesses; i++) {
                if (!finished[i]) {
                    int j;
                    for (j = 0; j < numResourceTypes; j++) {
                        if (Need[i][j] > Work[j]) {
                            //如果有需求大于可分配的资源，这不符合，直接break，目的是找到第一个满足的进程
                            break;
                        }
                    }
                    if (j == numResourceTypes) { // 一个进程的所有资源都满足需求
                        for (int k = 0; k < numResourceTypes; k++) {
                            Work[k] += Allocation[i][k];
                        }
                        Answer[count++] = i+1; // 记录这个进程为安全序列的一部分
                        finished[i] = true;
                        found = true;
                        break;
                    }
                }
            }
            if (!found) {
                return false; // 如果在一轮循环中没有找到可以完成的进程，则退出
            }
        }
        //如果对于所有的i，Finish[i]=true都成立，则系统处于安全状态；否则系统就是不安全的
        return true;
    }
    public void printStatus() {
        for (int i = 1; i <= numProcesses; i++) {
            System.out.println("进程"+ i +":");
            // 打印分配矩阵
            System.out.print("Allocation[" + i + "]: ");
            for (int j = 1; j <= numResourceTypes; j++) {
                System.out.print(Allocation[i-1][j-1] + " ");
            }
            System.out.print(" | Max[" + i + "]: ");
            // 打印最大需求矩阵
            for (int j = 1; j <= numResourceTypes; j++) {
                System.out.print(Max[i-1][j-1] + " ");
            }
            System.out.print(" | Need[" + i + "]: ");
            // 打印需求矩阵
            for (int j = 1; j <= numResourceTypes; j++) {
                System.out.print(Need[i-1][j-1] + " ");
            }
            System.out.println(); // 换行
        }
        System.out.print("系统剩余资源量：");
        for (int j = 1; j <= numResourceTypes; j++) {
            System.out.print(Available[j-1] + " ");
        }
        System.out.println(); // 换行
    }
}
