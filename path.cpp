
#include <cstdio>
#include <climits>
#include <iostream>

#define V 6

using namespace std;

void printMatrix(double graph[V][V]) 
{
	for (int i = 0;i < V;i++) {
		cout <<"| ";
		for (int j = 0;j < V;j++) {
			cout << graph[i][j] << " ";
		}
		cout << " |" << endl;
	}
}

void printMatrixDouble(double graph[V][V]) 
{
	for (int i = 0;i < V;i++) {
		cout <<"| ";
		for (int j = 0;j < V;j++) {
			cout << graph[i][j] << " ";
		}
		cout << " |" << endl;
	}
}

int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] < min)
			min = dist[v], min_index = v;

	return min_index;
}

void printPath(int parent[], int j, int a[100], int index)
{
	if (parent[j]==-1)
		return;
	printPath(parent, parent[j], a, ++index);
    
    a[index] = j;
    
}

void dijkstra(double graph[V][V], int src, int p[V][V], int dist[V])
{
	bool sptSet[V];

	int parent[V];

	for (int i = 0; i < V; i++)
	{
		parent[src] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < V-1; count++)
	{
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < V; v++)

			if (!sptSet[v] && graph[u][v] &&
				dist[u] + graph[u][v] <= dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			} 
	}

	for (int j = 0; j < V; j++)
	{
	    int a[V] = {0};
	    int x = 0;
		printPath(parent, j, a, 0);
		for (int i = V-1; i>= 0; i--){
		    if (a[i] != 0){
		    	p[j][i] = a[i]+1;

		    }else {
		    p[j][i] = a[i];
		}
		}
	}
}

void setSource(double pathMatrix[V][V][V])
{
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V;k++) {
				if (j != 0) {
					if ((pathMatrix[i][j][k] != 0 && pathMatrix[i][j][k+1] == 0)) {
						pathMatrix[i][j][k+1] = i+1;
						break;
					}
				}
				if (j == 0 && i != j) {
					
					pathMatrix[i][j][0] = j+1;
					pathMatrix[i][j][V-1] = i+1;
					break;
				}
				if (i == j) {
					pathMatrix[i][j][k] = i+1;
					break;
				}
			}
		}
	}
}

void printPathMatrix(double pathMatrix[V][V][V])
{
	for (int i = 0; i < V;i++) {
		cout << "| ";
		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V;k++) {
//				if (pathMatrix[i][j][k]) {
					cout << pathMatrix[i][j][k] << " ";
//				}
			}
			cout << " ";
		}
		cout << " |"<<endl;
	}
}

void reversePathMatrix(double pathMatrix[V][V][V])
{
	int tmp[V][V][V];
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V;k++) {
				tmp[i][j][k] = pathMatrix[i][j][V-k-1];
			}
		}
	}

	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V;k++) {
				pathMatrix[i][j][k] = tmp[i][j][k];
			}
		}
	}
}

void hopCountCalucaltion(double pathMatrix[V][V][V], double hopCount[V][V])
{
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			int count = 0;
			for (int k = 0; k < V;k++) {
				if (pathMatrix[i][j][k] != 0) {
					count++;
				}
			}
			hopCount[i][j] = count-1;
		}
	}
}

void separatezeroes(double pathMatrix[V][V][V])
{
	int tmp[V][V][V] = {0};
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			int c = 0;
			for (int k = 0; k < V;k++) {
				if (pathMatrix[i][j][k] != 0) {
					tmp[i][j][c] = pathMatrix[i][j][k];
					c++;
				}
			}
		}
	}

	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V;k++) {
				pathMatrix[i][j][k] = tmp[i][j][k];
			}
		}
	}
}

void calculateEdgeTraffic(double EdgeTraffic[V][V], double pathMatrix[V][V][V], double graph[V][V], double flow[V][V])
{
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V - 1;k++) {
				if (pathMatrix[i][j][k + 1] != 0) {
					EdgeTraffic[(int) pathMatrix[i][j][k]-1][(int) pathMatrix[i][j][k+1]-1] = EdgeTraffic[(int) pathMatrix[i][j][k]-1][(int) pathMatrix[i][j][k+1]-1] + flow[i][j];
				}
			}
		}
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0;j < V;j++) {
			if (graph[i][j] == 0) {
				EdgeTraffic[i][j] = 0;
			}
		}
	}
}

void calculateWeightedMatrixG(double graph[V][V], double EdgeTraffic[V][V], double capacity[V][V], double weightedMatrixG[V][V])
{
	for (int i = 0;i < V; i++) {
		for (int j = 0; j < V;j++) {
			if (EdgeTraffic[i][j] > capacity[i][j]) {
				weightedMatrixG[i][j] = 0;
			}
			else {
				int c = capacity[i][j] + 1;
				weightedMatrixG[i][j] = ((double) c/((double) (c - EdgeTraffic[i][j])))*graph[i][j];
			}
		}
	}
}

int main()
{
	double graph[V][V] = { {0, 7, 0, 7, 0,9},
					{0, 0, 5, 0, 10, 3},
					{9, 10, 0, 8, 4, 6},
					{9, 4, 2, 0, 0, 0},
					{3, 5, 10, 10, 0, 0},
					{0, 5, 8, 10, 0,0} };

	double flow[V][V] = { {0, 9, 11, 12, 8, 12},
						{18, 0, 15, 10, 17, 18},
						{17, 18, 0, 14, 10, 10},
						{17, 8, 10, 0, 17, 18},
						{15, 9, 12, 14, 0, 16},
						{18, 16, 15, 8, 9, 0}};

	double capacity[V][V] = { {0, 13, 0, 33, 0, 20},
					{0, 0, 67, 0, 5, 55},
					{5,5,0,32, 134, 17},
					{23, 34, 55, 0, 0, 0,},
					{68, 47, 20, 14, 0, 0},
					{0, 16, 44, 16, 0, 0}};

	double pathMatrix[V][V][V] = {0};
	double shortestpath[V][V] = {0};
	double hopCount[V][V] = {0};
	double EdgeTraffic[V][V] = {0.0};
	double weightedMatrixG[V][V] = {0.0};
	double weightedMatrixShort[V][V] = {0.0};
	double weightedMatrixPath[V][V][V] = {0};

	for (int i = 0; i < V;i++) {
		int p[V][V]={0};
		int dist[V]={0};
		dijkstra(graph, i, p, dist);

		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V;k++) {
				pathMatrix[i][j][k] = p[j][k];
			}
		}

		for (int j = 0; j < V;j++) {
			shortestpath[i][j] = dist[j];
		}
	}

	cout << "Input matrix: \n";
	printMatrix(graph);

	cout << "shortest path matrix: \n";
	printMatrix(shortestpath);

	setSource(pathMatrix);
	reversePathMatrix(pathMatrix);

	separatezeroes(pathMatrix);
	cout <<"Path matrix: \n";
	printPathMatrix(pathMatrix);

	cout << "Hop count: \n";
	hopCountCalucaltion(pathMatrix, hopCount);
	printMatrix(hopCount);

	cout << "Flow Matrix: \n";
	printMatrix(flow);

	calculateEdgeTraffic(EdgeTraffic, pathMatrix, graph, flow);
	cout << "Edge Traffic: \n";
	printMatrix(EdgeTraffic);

	cout << "capacity Matrix: \n";
	printMatrix(capacity);

	calculateWeightedMatrixG(graph, EdgeTraffic, capacity, weightedMatrixG);
	cout <<"Weighted matrix: \n";
	printMatrixDouble(weightedMatrixG);

	for (int i = 0; i < V;i++) {
		int p[V][V]={0};
		int dist[V]={0};
		dijkstra(weightedMatrixG, i, p, dist);

		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V;k++) {
				weightedMatrixPath[i][j][k] = p[j][k];
			}
		}

		for (int j = 0; j < V;j++) {
			weightedMatrixShort[i][j] = dist[j];
		}
	}

	cout << "Actual path delay: \n";
	printMatrixDouble(weightedMatrixShort);

	cout <<"Actual path matrix: \n";
	printPathMatrix(weightedMatrixPath);
	return 0;
}
