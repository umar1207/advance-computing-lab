import java.util.Scanner;

public class mcm_adv
{
    static void answer(int i, int j, int [][] st)
    {
        if(i == j)
        {
            System.out.print(i);
            return;
        }
        System.out.print("(");
        answer(i, st[i][j], st);
        answer(st[i][j]+1, j, st);
        System.out.print(")");
    }
    public static void main(String[] args)
    {
        System.out.print("Enter the number of matrices: ");
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();

        int n = x+1;

        System.out.print("Enter the dimensions of " + x + " matrices: ");
        int [] arr = new int[n];
        for(int i = 0; i < n; i++) arr[i] = sc.nextInt();

        int [][] dp = new int[n][n];
        int [][] st = new int[n][n];

        for(int i = 0; i < n; i++) dp[i][i] = 0; // base case
        for(int i=n-1; i>=1; i--)
        {
            for(int j=i+1; j<n; j++)
            {
                int mini = Integer.MAX_VALUE;
                for(int k = i; k <= j-1; k++)
                {
                    int steps = arr[i-1] * arr[k] * arr[j] + dp[i][k] + dp[k+1][j];
                    if(steps < mini)
                    {
                        mini = steps;
                        st[i][j] = k;
                    }
                }
                dp[i][j] = mini;
            }
        }

        answer(1, n-1, st);
        System.out.println("\nThe minimum number of steps required to transform " + n + " matrices is: " + dp[1][n-1]);

        for(int i=1; i<n; i++)
        {

            for(int j=1; j<n; j++)
            {
                if(i <= j) System.out.printf("%-5d", dp[i][j]);
                else System.out.print("     ");
            }
            System.out.println();
        }

        sc.close();
    }
}






