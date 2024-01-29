import java.util.*;

public class bipartite
{

	static int findColor(int color)
	{
		return (color==1) ? 0 : 1;
	}
	
	static String stringColor(int color)
	{
		if(color==0) return "Blue";
		return "Red";
	}
	
	static boolean isBiPartite(int [][]graph, int []visited, int v, int s)
	{
		// declare and initialise the queue;
		int queue[] = new int[v];
		for(int i=0; i<v; i++) queue[i] = -1;
		
		int head = 0; int tail = 0; //POP AT HEAD, PUSH AT TAIL
		queue[tail++] = s; //PUSH
		visited[s] = 0;
		
		System.out.println("\n\nIntermediate Steps");
		
		while(head != tail)
		{
			int node = queue[head++];
			int color = visited[node]; //COLOR OF NODE
			int nColor = findColor(color); //EXPECTED COLOR OF NEIGHBOURS
			
			System.out.println("\nExploring vertex " + node);
			System.out.println("Color of vertex " + node + " : "  + stringColor(color));
			
			for(int i=0; i<v; i++)
			{
				if(graph[node][i] == 1) // EDGE EXISTS 
				{
					if(visited[i] == -1)
					{
						queue[tail++] = i;
						visited[i] = nColor;
						System.out.println("Vertex " + i + " coloured with " + stringColor(nColor));
					}
					else
					{
						if(visited[i] != nColor)
						{
							System.out.println("#MISMATCH: " + i + " cannot be colored " + stringColor(nColor) + " because it was previsously coloured " + stringColor(visited[i]));
							return false;
						}
						else continue;
					}
				}
			}
		}
		return true;
		
	}
	public static void main(String args[])
	{
		System.out.print("Enter the number of vertices: ");
		Scanner sc = new Scanner(System.in);
		
		int V = sc.nextInt();
		System.out.print("Enter the number of edges: ");
		int e = sc.nextInt();
		
		int graph[][] = new int[V][V];
		for(int i=0; i<V; i++)
		{
			for(int j=0; j<V; j++)
			{
				graph[i][j] = 0;
			}
		}
		
		System.out.println("Enter the nodes between which the edge exist");
		
		for(int i=0; i<e; i++)
		{
			int u = sc.nextInt();
			int v = sc.nextInt();
			
			graph[u][v] = 1;
			graph[v][u] = 1;
			
		}
		
        sc.close();

		int visited[] = new int[V]; 
		
		boolean printed[] = new boolean[V];
		for(int i=0; i<V; i++) printed[i] = false;		
		// initialise visited and queue
		for(int i=0; i<V; i++) visited[i] = -1;
		
		int count = 0;
		for(int j=0; j<V; j++)
		{
			if(visited[j]==-1)
			{
				boolean ans = isBiPartite(graph, visited, V, j);
				// System.out.println(ans);
				if (ans == true)
				{
					System.out.println("\n\nGraph " + (++count) + " is a bipartite graph");
					System.out.print("\nVertices of set 1 (Blue): ");
					for(int i=0; i<V; i++) 
					{
						if(visited[i] == 0 && printed[i] == false)
						{
							System.out.print(i + " ");
							printed[i] = true;
						}
					}
				
					System.out.print("\nVertices of set 2 (Red): ");
					for(int i=0; i<V; i++) 
					{
						if(visited[i] == 1 && printed[i] == false)
						{
							System.out.print(i + " ");
							printed[i] = true;
						}
					}
				}
				else 
				{
					System.out.println("\n\nGraph " + (++count) + " is not a bipartite graph");
					break;
				}
			}
		}
	}
}
