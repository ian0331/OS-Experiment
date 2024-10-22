import java.security.spec.RSAOtherPrimeInfo;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int numProcesses, numResourceTypes;
        Scanner in = new Scanner(System.in);
        System.out.println("请输入进程数: ");
        numProcesses = in.nextInt();
        System.out.println("请输入资源种类的数量：");
        numResourceTypes = in.nextInt();
        BankerAlgorithm ba = new BankerAlgorithm(numProcesses, numResourceTypes);
        System.out.println("初始化Max矩阵(" + ba.numProcesses + "行" + ba.numResourceTypes + "列)" + ":");
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResourceTypes; j++) {
                ba.Max[i][j] = in.nextInt();
            }
        }
        System.out.println("初始化Allocation矩阵(" + ba.numProcesses + "行" + ba.numResourceTypes + "列)" + ":");
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResourceTypes; j++) {
                ba.Allocation[i][j] = in.nextInt();
            }
        }
        System.out.println("请输入当前可用的资源量(一行" + ba.numResourceTypes + "列)" + ":");
        for (int i = 0; i < numResourceTypes; i++) {
            ba.Available[i] = in.nextInt();
            ba.Work[i] = ba.Available[i];
        }
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResourceTypes; j++) {
                ba.Need[i][j] = ba.Max[i][j] - ba.Allocation[i][j];
            }
        }
        int way; // 添加变量声明
        while (true) {
            System.out.println("输入操作：");
            System.out.println("1: 申请资源");
            System.out.println("2：查看当前系统状态");
            System.out.println("3: 退出程序");
            way = in.nextInt(); // 获取用户输入的操作
            switch (way) {
                case 1:
                    // 处理资源申请逻辑
                    System.out.println("请输入发出请求的进程编号(1~ " + ba.numProcesses + ")：");
                    ba.nowProcess = in.nextInt();
                    ba.nowProcess--;
                    System.out.println("请输入请求向量(1行" + ba.numResourceTypes + "列)" + ":");
                    for (int i = 0; i < numResourceTypes; i++) {
                        ba.Request[i] = in.nextInt();
                    }
                    for (int i = 0; i < numProcesses; i++) {
                        ba.finished[i] = false;
                    }
                    //发出申请
                    ba.request();
                    break;
                case 2:
                    // 查看当前系统状态
                    ba.printStatus();
                    break;
                case 3:
                    System.out.println("程序已退出。");
                    return; // 退出主函数
                default:
                    System.out.println("无效的操作，请重新输入。");
            }
        }

    }
}
/*
 * 运行用例
 * Max
 * 3 2 2
 * 6 1 3
 * 3 1 4
 * 4 2 2
 * Allocation
 * 1 0 0
 * 4 1 1
 * 2 1 1
 * 0 0 2
 * Available
 * 2 1 2
 */