import java.util.Scanner;

public class mcm
{
    static int f(int i, int j, int [] arr)
    {
        if(i == j) return 0;
        int mini = Integer.MAX_VALUE;
        for(int k = i; k <= j-1; k++)
        {
            int steps = arr[i-1] * arr[k] * arr[j] + f(i,k, arr) + f(k+1, j, arr);
            mini = Math.min(mini, steps);
        }
        return mini;
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

        System.out.println("The minimum number of steps required to transform " + n + " matrices is: " + f(1, n-1, arr));
        sc.close();
    }
}
