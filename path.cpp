
#include <cstdio>
#include <climits>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <ctime>

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

	int parent[V]; // parent matrix

	for (int i = 0; i < V; i++)
	{
		parent[src] = -1; //initializing source as -1
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
				dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];  //minimim distance will be stored.
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
	// printing for all 3d matrix.
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
	//counting number of hops
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			int count = 0;
			for (int k = 0; k < V;k++) {
				if (pathMatrix[i][j][k] != 0) { // number of characters in path matrix - 1
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

void calculateEdgeTraffic2(double EdgeTraffic[V][V], double weightedMatrixG[V][V],double weightedMatrixPath[V][V][V], double graph[V][V], double flow[V][V], double residualMatrix[V][V], double capacity[V][V])
{
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			for (int k = 0; k < V - 1;k++) {
				if (weightedMatrixPath[i][j][k + 1] != 0) {
					EdgeTraffic[(int) weightedMatrixPath[i][j][k]-1][(int) weightedMatrixPath[i][j][k+1]-1] = EdgeTraffic[(int) weightedMatrixPath[i][j][k]-1][(int) weightedMatrixPath[i][j][k+1]-1] + flow[i][j];
				}
			}
		}
	}
	for (int i = 0; i < V; i++) {
		for (int j = 0;j < V;j++) {
			if (graph[i][j] == 0 || weightedMatrixG[i][j] == 0) {
				EdgeTraffic[i][j] = 0;
			}
		}
	}
	/*for (int i = 0; i < V; i++) {
		for (int j = 0;j < V;j++) {
			if (EdgeTraffic[i][j] >= capacity[i][j]) {
				//residualMatrix[i][j] = EdgeTraffic[i][j] - capacity[i][j];
				//EdgeTraffic[i][j] = capacity[i][j];
				graph[i][j] = 0;
				weightedMatrixG[i][j] = 0;
			}
		}
	}*/
}

void calculateWeightedMatrixG(double graph[V][V], double EdgeTraffic[V][V], double capacity[V][V], double weightedMatrixG[V][V])
{
	// G matrix calculation
	for (int i = 0;i < V; i++) {
		for (int j = 0; j < V;j++) {
			if (EdgeTraffic[i][j] >= capacity[i][j]) {
				weightedMatrixG[i][j] = 0;
			}
			else {
				int c = capacity[i][j] + 1;
				weightedMatrixG[i][j] = ((double) c/((double) (c - EdgeTraffic[i][j])))*graph[i][j]; // formulae for weighted edge.
			}
		}
	}
}

void calculatePredictedMatrix(double graph[V][V], double predictedMatrix[V][V])
{
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			predictedMatrix[i][j] = (graph[i][j] + ((double) graph[i][j]*0.1));
		}
	}
}

void calcualteNewFlowMatrix(double flow[V][V], double newFlowMatrix[V][V], double percent)
{
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			newFlowMatrix[i][j] = flow[i][j]*percent;
		}
	}
}

void calcualteActualPathDelay(double weightedMatrixG[V][V], double pathMatrix[V][V][V], double actualPathDelayMatrix[V][V])
{
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i != j) {
				for (int k = 0;k < V - 1;k++) {
					if ((int) pathMatrix[i][j][k + 1] != 0) {
						actualPathDelayMatrix[i][j] = actualPathDelayMatrix[i][j] + weightedMatrixG[((int) pathMatrix[i][j][k]) - 1][((int) pathMatrix[i][j][k+1]) - 1];
						if (i == 0 && j == 2) {
							cout << actualPathDelayMatrix[i][j] << pathMatrix[i][j][k] << pathMatrix[i][j][k+1];
						}
					}
				}
			}
		}
	}
}

void updateEdgeTraffic(double graph[V][V], double EdgeTraffic[V][V], double capacity[V][V], double residualMatrix[V][V], double weightedMatrixG[V][V], double weightedMatrixPath[V][V][V], double updatedShortestPath[V][V], double pathMatrix[V][V][V], double actualPathDelayMatrix[V][V])
{
	for (int it1 = 0; it1 < V;it1++) {
		for (int it2 = 0; it2 < V; it2++) {
			for (int it3 = 0; it3 < V;it3++) {
				weightedMatrixPath[it1][it2][it3] = pathMatrix[it1][it2][it3];
			}
		}
	}
	calculateWeightedMatrixG(graph, EdgeTraffic, capacity, weightedMatrixG);
	cout << " aad" << weightedMatrixG[1][5];
	double tmpG[V][V] = {0};

	for (int it4 = 0; it4 < V;it4++) {
		for (int it5 = 0; it5 < V; it5++) {
			tmpG[it4][it5] = weightedMatrixG[it4][it5];
		}
	}

	for (int it1 = 0; it1 < V;it1++) {
		for (int it2 = 0; it2 < V;it2++) {
			int x = residualMatrix[it1][it2];
			if (x > 0) {
				while (x > 0) {
					for (int i = 0; i < V;i++) {
						int p[V][V]={0};
						int dist[V]={0};
						dijkstra(tmpG, i, p, dist);

						for (int j = 0;j < V;j++) {
							for (int k = 0; k < V;k++) {
								weightedMatrixPath[i][j][k] = p[j][k];
							}
						}

						for (int j = 0; j < V;j++) {
							updatedShortestPath[i][j] = dist[j];
						}
					}

					setSource(weightedMatrixPath);
					reversePathMatrix(weightedMatrixPath);
					separatezeroes(weightedMatrixPath);
					for (int it3 = 0; it3 < V - 1;it3++) {
						if (((int) weightedMatrixPath[it1][it2][it3 + 1]) != 0) {
							int tmp = EdgeTraffic[(int) weightedMatrixPath[it1][it2][it3] -1][(int) weightedMatrixPath[it1][it2][it3 + 1] - 1];
							EdgeTraffic[(int) weightedMatrixPath[it1][it2][it3] -1][(int) weightedMatrixPath[it1][it2][it3 + 1] - 1] = tmp + 1;
							//cout << weightedMatrixPath[it1][it2][it3] << " " << weightedMatrixPath[it1][it2][it3 + 1]<< " ";
						}
					}
					cout << endl;
					x--;
					residualMatrix[it1][it2] = x;
					calculateWeightedMatrixG(tmpG, EdgeTraffic, capacity, weightedMatrixG);
					//cout << weightedMatrixG[it1][it2]<< endl;
				}
			}
		}
	}
}

double getMax(double flow[V][V])
{
	double max = 0;
	for (int i = 0;i < V;i++) {
		for (int j = 0;j < V;j++) {
			if (flow[i][j] > max && flow[i][j] != 0) {
				max = flow[i][j];
			}
		}
	}

	return max;
}

void getNewFlow(double tmpFlowMatrix[V][V], double flow[V][V])
{
	// adding 1 car for each source destination pair.
	for (int i = 0; i < V;i++) {
		for (int j = 0;j < V;j++) {
			if (tmpFlowMatrix[i][j] > 0) {
				flow[i][j] = flow[i][j] + 1;
				tmpFlowMatrix[i][j] = tmpFlowMatrix[i][j] - 1;
			}
		}
	}
}

void updateCongestionTraffic(double graph[V][V], double flow[V][V], double EdgeTraffic[V][V], double capacity[V][V], double residualMatrix[V][V], double weightedMatrixG[V][V], double weightedMatrixPath[V][V][V], double updatedShortestPath[V][V], double pathMatrix[V][V][V], double actualPathDelayMatrix[V][V])
{

	double max = getMax(flow);
	double tmpFlowMatrix[V][V] = {0};

	for (int i = 0;i < V;i++) {
		for (int j = 0;j < V;j++) {
			for (int k = 0;k < V;k++) {
				weightedMatrixPath[i][j][k] = pathMatrix[i][j][k];
			}
		}
	}

	for (int i = 0;i < V;i++) {
		for (int j = 0;j < V;j++) {
			tmpFlowMatrix[i][j] = flow[i][j];
		}
	}

	for (int i = 0;i < V;i++) {
		for (int j = 0;j < V;j++) {
			flow[i][j] = 0;
		}
	}

	int tmp = max;
	cout << max;
	while (max-- > 0) {

		for (int i = 0;i < V;i ++) {
			for (int j = 0;j < V;j++) {
				EdgeTraffic[i][j] = 0;
			}
		}
		//cout << "Maximum vehcile on each s-d pair: "<< tmp - max << endl;
		double residualMatrix[V][V] = {0};
		getNewFlow(tmpFlowMatrix, flow);
		calculateEdgeTraffic2(EdgeTraffic, weightedMatrixG, weightedMatrixPath, graph, flow, residualMatrix, capacity);
		for (int i = 0; i < V; i++) {
			for (int j = 0;j < V;j++) {
				if (EdgeTraffic[i][j] > capacity[i][j]) {
					//residualMatrix[i][j] = EdgeTraffic[i][j] - capacity[i][j];
					//EdgeTraffic[i][j] = capacity[i][j];
					//graph[i][j] = 0;
					weightedMatrixG[i][j] = 0;
				}
			}
		}
		calculateWeightedMatrixG(graph, EdgeTraffic, capacity, weightedMatrixG);
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
				updatedShortestPath[i][j] = dist[j];
			}
		}

/*		for (int i = 0;i < V;i++) {
			for (int j = 0;j < V;j++) {
				graph[i][j] = weightedMatrixG[i][j];
			}
		}*/

		setSource(weightedMatrixPath);
		reversePathMatrix(weightedMatrixPath);
		separatezeroes(weightedMatrixPath);
		cout << "weightedMatrixG:\n";
		printMatrix(weightedMatrixG);
		cout << "Predicted shortest path: \n";
		printPathMatrix(weightedMatrixPath);
		cout<< "Edge traffic at kth car: ";
		printMatrix(EdgeTraffic);
		//printMatrix(flow);
	}
}

int main()
{
	clock_t start = clock();
	double graph[V][V]; // Given Graph or edge matrix.

	double flow[V][V]; // Given FLow matrix

	double capacity[V][V]; // Given capacity matrix.

    int Count=0;
	int i,j,k; 
	int N,S,D;
	FILE *f=fopen("input.txt","r"); // reading input from file.
	const char s[2]=",";
	char *token;
	char line[20];
	if(f!=NULL)
	{
		if(fgets(line,sizeof line,f)!=NULL){
		token=strtok(line,s);
		N=atoi(token);
		token = strtok(NULL,s); 
		S=atoi(token);
		token = strtok(NULL,s); 
		D=atoi(token); 
		token = strtok(NULL,s); 
		printf("%d\t%d\t%d\n",N,S,D);
		}
		int E[N+1][N+1],F[N+1][N+1],C[N+1][N+1],G[N+1][N+1],MyDist[N+1][N+1],Hop[N+1][N+1],Parent[N+1][N+1],Count[N+1][N+1],Path[N+1][N+1][N+1];
		float Load[N+1][N+1];

		for(i=0;i<N;i++){for(j=0;j<N;j++)
                 {
                        E[i][j]=0;F[i][j]=0;C[i][j]=0;G[i][j]=0;MyDist[i][j]=0;Load[i][j]=0;
			if(i==j)
                                {E[i-1][j-1]=0;MyDist[i-1][j-1]=0;Hop[i][j]=0;Parent[i][j]=i;}  
                 }
                }

		char mat_type;int from,to,val;
		for(i=0;i<N;i++){for(i=1;i<N;i++){for(j=0;j<N;j++)for(k=0;k<N;k++){if(k==0){Path[i][j][k]=1;}else{Path[i][j][k]=0;}}}}
		while(fgets(line, sizeof line, f) != NULL) 
		{		
			token = strtok(line, s);
			for(i=1;i<5;i++) 
			{ 
					if(i==1&&token)
						mat_type=token[i];
					else if(i==2&&token)
                                                from=atoi(token);						
					else if(i==3&&token)
						to=atoi(token);
					else if(i==4&&token)
						val=atoi(token);
					token = strtok(NULL,s);
			} 
			switch (mat_type)  //using switch case for distrubuting values to different values.
			{
				case 'E':
				
					{
						E[from-1][to-1]=val;
						if (from == 10) {
						cout << from << to << val << endl;}break;}
				case 'F':

					{F[from-1][to-1]=val;
						if (from == 1 && to == 1) {cout << val;}break;}
				case 'C':
					{C[from-1][to-1]=val;break;}
			}
		} 

		for (i = 0;i < V;i++) {
			for (j = 0;j < V;j++) {
				graph[i][j] = (double) E[i][j];
				flow[i][j] = (double) F[i][j];
				capacity[i][j] = (double) C[i][j];
				//cout << graph[i][j];
			}
		}
	}
   


	double pathMatrix[V][V][V] = {0};  // Path Length Matrix.
	double shortestpath[V][V] = {0};   // Shortest Distance from all S-D pair matrix.
	double hopCount[V][V] = {0};       // Hop count for all s-d pair.
	double EdgeTraffic[V][V] = {0.0};
	double weightedMatrixG[V][V] = {0.0};
	double actualPathDelayMatrix[V][V] = {0.0};
	double weightedMatrixPath[V][V][V] = {0};
	double predictedMatrix[V][V] = {0};
	double newFlowMatrix[V][V] = {0};
	double residualMatrix[V][V]= {0};
	double updatedShortestPath[V][V] = {0};

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

	//calculateEdgeTraffic(EdgeTraffic, pathMatrix, graph, flow, residualMatrix, capacity);
	//cout << "Edge Traffic: \n";
	//printMatrix(EdgeTraffic);

	cout << "capacity Matrix: \n";
	printMatrix(capacity);

	calculateWeightedMatrixG(graph, EdgeTraffic, capacity, weightedMatrixG);
	cout <<"Weighted matrix: \n";
	printMatrixDouble(weightedMatrixG);

	/*cout << "Actual path delay: \n";
	calcualteActualPathDelay(weightedMatrixG, pathMatrix, actualPathDelayMatrix);
	printMatrixDouble(actualPathDelayMatrix);

	cout << "residualMatrix: \n";
	printMatrix(residualMatrix);

	updateEdgeTraffic(graph, EdgeTraffic, capacity,residualMatrix, weightedMatrixG, weightedMatrixPath, updatedShortestPath, pathMatrix, actualPathDelayMatrix);
	cout << "Updated Edge Traffic: \n ";
	printMatrix(EdgeTraffic);

	cout << " Updated weightedMatrixG: \n";
	printMatrix(weightedMatrixG);

	cout << " updatedShortestPath: \n";
	printMatrix(updatedShortestPath);

	cout << "Updated residualMatrix: \n";
	printMatrix(residualMatrix);*/

	updateCongestionTraffic(graph, flow, EdgeTraffic, capacity,residualMatrix, weightedMatrixG, weightedMatrixPath, updatedShortestPath, pathMatrix, actualPathDelayMatrix);

	clock_t end = clock();
	double duration = ((double) end) - ((double) start) / CLOCKS_PER_SEC;
	cout << "Execution time of the program: " << duration << endl;
	
	return 0;
}
