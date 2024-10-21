import java.security.spec.RSAOtherPrimeInfo;
import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        int numProcesses,numResourceTypes;
        Scanner in = new Scanner(System.in);
        System.out.println("请输入进程数: ");
        numProcesses = in.nextInt();
        System.out.println("请输入资源种类的数量：");
        numResourceTypes = in.nextInt();
        BankerAlgorithm ba = new BankerAlgorithm(numProcesses, numResourceTypes);
        System.out.println("初始化Max矩阵:");
        for(int i=0; i<numProcesses; i++){
            for(int j=0; j<numResourceTypes; j++){
                ba.Max[i][j] = in.nextInt();
            }
        }
        System.out.println("初始化Allocation矩阵:");
        for(int i=0; i<numProcesses; i++){
            for(int j=0; j<numResourceTypes; j++){
                ba.Allocation[i][j] = in.nextInt();
            }
        }
        System.out.println("请输入当前可用的资源量:");
        for(int i=0; i<numResourceTypes; i++){
            ba.Available[i] = in.nextInt();
            ba.Work[i] = ba.Available[i];
        }
        for(int i=0; i<numProcesses; i++){
            for(int j=0; j<numResourceTypes; j++){
                ba.Need[i][j] = ba.Max[i][j] - ba.Allocation[i][j];
            }
        }
        System.out.println("请输入发出请求的进程编号：");
        ba.nowProcess = in.nextInt();
        System.out.println("请输入请求向量：");
        for(int i=0; i<numResourceTypes; i++){
            ba.Request[i] = in.nextInt();
        }
        for(int i=0; i<numProcesses; i++){
            ba.finished[i] = false;
        }
        ba.request();
    }
}
/*
运行用例
Max
3 2 2
6 1 3
3 1 4
4 2 2
Allocation
1 0 0
4 1 1
2 1 1
0 0 2
Available
2 1 2
*/