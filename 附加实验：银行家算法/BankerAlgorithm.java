import java.util.Arrays;
import java.util.Scanner;
//银行家算法
public class BankerAlgorithm {
    public int numProcesses;       // 进程的数量
    public int numResourceTypes;   // 资源种类的数量
    public int[][] Max;            //最大需求矩阵
    public int[][] Allocation;     //分配矩阵
    public int[][] Need;           //需求矩阵
    public int[] Available;
    public int[] Work;             //工作向量
    public int nowProcess;         //当前正在请求分配资源的进程
    public int[] Request;          //进程申请资源向量
    public int[] Answer;
    public boolean[] finished =  new boolean[numProcesses];//标记已完成的进程
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
                System.out.println("所需要的资源数已经超过它所宣布的最大值");
                return;
            }
            if (Request[i] > Available[i]) {
                System.out.println("尚无足够资源");
                return;
            }
        }
        for (int i = 0; i < numResourceTypes; i++) {
            Available[i] -= Request[i];
            Allocation[nowProcess][i] += Request[i];
            Need[nowProcess][i] -= Request[i];
        }
        if(security()){
            System.out.println("当前状态安全，其中一个安全序列为:");
            for(int i =0;i<numProcesses;i++){
                System.out.print(Answer[i]+"->");
            }
        }else{

            System.out.println("当前状态不安全,发生死锁。");
//            System.out.println("当前资源分配矩阵(Allocation):");
//            for (int[] row : Allocation) {
//                System.out.println(Arrays.toString(row));
//            }
//            System.out.println("需求矩阵(Need):");
//            for (int[] row : Need) {
//                System.out.println(Arrays.toString(row));
//            }
//            System.out.println("可用资源向量(Available): " + Arrays.toString(Available));
//            System.out.println("工作向量(Work): " + Arrays.toString(Work));
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
                        break;
                    }
                }
                if (j == numResourceTypes) { // 如果所有资源都满足需求
                    for (int k = 0; k < numResourceTypes; k++) {
                        Work[k] += Allocation[i][k];
                    }
                    Answer[count++] = i; // 记录这个进程为安全序列的一部分
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
}
