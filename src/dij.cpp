// C program for Dijkstra's single  
// source shortest path algorithm. 
// The program is for adjacency matrix 
// representation of the graph. 
#include <stdio.h> 
#include <limits.h> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;
// Number of vertices in the graph 
// #define H 366  
// #define W 362 
//resolution value
double resolution = 0.0500000007451;
//Arrays to map 1D into 2D
int H ,W;
vector<vector<int> > map;
vector<vector<int> > graph;
//int *map[][];
//int graph[H*W][H*W];
vector<vector<int> >v1;
vector<vector<pair<double,double> > >v2; 


bool isValid(int row, int col, int row_max, int col_max)
{
    // Returns true if row number and column number is in range
    return (row >= 0) && (row < row_max) &&
           (col >= 0) && (col < col_max);
}

void checkNeighbours(int row, int col){
    int rneigh,cneigh,i,j;
    int row_max = map.size();
    int col_max = map[0].size();
    i = (row*H)+col;
    if (isValid(row-1,col, row_max, col_max) == true){
        rneigh = row-1;
        cneigh = col;
        j = (rneigh*H)+cneigh;
        if(map[row-1][col] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row-1][col] == -1 || map[row][col] == -1){
            graph[i][j] = 50; 
        }
        else if(map[row-1][col] == 0 || map[row][col] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
        
    }
    if (isValid(row+1,col, row_max, col_max) == true){
        rneigh = row+1;
        cneigh = col;
        j = (rneigh*H)+cneigh;   
        if(map[row+1][col] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row+1][col] == -1 || map[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map[row+1][col] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
        
    }

    if (isValid(row,col+1, row_max, col_max) == true){
        cneigh = col+1; 
        rneigh = row;
        j = (rneigh*H)+cneigh;
        if(map[row][col+1] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row][col+1] == -1 || map[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map[row][col+1] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
    }
    if (isValid(row,col-1, row_max, col_max) == true){
        cneigh = col-1; 
        rneigh = row;
        j = (rneigh*H)+cneigh;
        if(map[row][col-1] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row][col-1] == -1 || map[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map[row][col-1] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
    }
    if (isValid(row-1,col+1, row_max, col_max) == true){
        rneigh = row-1;
        cneigh = col+1; 
        j = (rneigh*H)+cneigh;
        if(map[row-1][col+1] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row-1][col+1] == -1 || map[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map[row-1][col+1] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
    }
    if (isValid(row-1,col-1, row_max, col_max) == true){
        rneigh = row-1;
        cneigh = col-1; 
        j = (rneigh*H)+cneigh;
        if(map[row-1][col-1] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row-1][col-1] == -1 || map[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map[row-1][col-1] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
    }
    if (isValid(row+1,col+1, row_max, col_max) == true){
        rneigh = row+1;
        cneigh = col+1; 
        j = (rneigh*H)+cneigh;
        if(map[row+1][col+1] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row+1][col+1] == -1 || map[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map[row+1][col+1] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
    }
    if (isValid(row+1,col-1, row_max, col_max) == true){
        rneigh = row+1;
        cneigh = col-1; 
        j = (rneigh*H)+cneigh;
        if(map[row+1][col-1] == 100 || map[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map[row+1][col-1] == -1 || map[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map[row+1][col-1] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
    }
}


// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree 
int minDistance(int dist[], bool sptSet[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
    for (int v = 0; v < H*W; v++) 
        if (sptSet[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    return min_index; 
} 
  
// Function to print shortest path from source to int 
void printPath(int parent[], int x, vector<int> &v) 
{ 
    if (parent[x] == - 1) 
        return; 
    printPath(parent, parent[x],v); 
    cout << "->" << x;
    v.push_back(x);
} 
  
// A utility function to print the constructed distance array 
void printSolution(int dist[], int n, int parent[]) 
{ 
    int src = 0; 
    printf("Vertex\t\t Distance\tPath\n");
    for (int i = 1; i < H*W; i++) 
    { 
        vector<int> v;
        printf("\n%d -> %d \t\t %d\t\t%d", src, i, dist[i], src); 
        printPath(parent, i, v);
        v1.push_back(v);
    }
} 

void printGraph(){
    for(int i =0; i < graph.size(); i++){
        for(int j=0; j<graph[i].size();j++){
            cout << graph[i][j] << " \t";
        }
        cout << endl;
    }

}

void Path2D(vector<vector<int> >&v1,vector<vector<pair<double,double> > >&v) {
    double x,y;
    for(int i=0; i<v1.size();i++){
        vector<pair<double,double> > tmp;
        for(int j=0; j<v1[i].size();j++){
            x = (v1[i][j])%W;
            y = (v1[i][j])/W;
            x = x*resolution;
            y = y*resolution;
            tmp.push_back(make_pair(y,x));
        }
        v.push_back(tmp);
    }
}
  
// Funtion that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation 
void dijkstra(vector<vector<int> > &graph, int src) 
{ 
      
    // The output array. dist[i] will hold the shortest distance from src to i 
    int dist[H*W];  
  
    // sptSet[i] will true if vertex i is included / in shortest 
    // path tree or shortest distance from src to i is finalized 
    bool sptSet[H*W]; 
  
    // Parent array to store shortest path tree 
    int parent[H*W]; 
  
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < H*W; i++) 
    { 
        parent[0] = -1; 
        dist[i] = INT_MAX; 
        sptSet[i] = false; 
    } 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < H*W - 1; count++) 
    { 
        // Pick the minimum distance vertex from the set of 
        // vertices not yet processed. u is always equal to src in first iteration. 
        int u = minDistance(dist, sptSet); 
  
        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value of the  
        // adjacent vertices of the 
        // picked vertex. 
        for (int v = 0; v < H*W; v++) 
  
            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and  
            // total weight of path from src to v through u is smaller 
            // than current value of dist[v] 
            if (!sptSet[v] && graph[u][v] && 
                dist[u] != INT_MAX && dist[u]+ graph[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
    } 
    // print the constructed distance array 
    printSolution(dist, H*W, parent); 
} 
  
// Driver Code 
int main() 
{ 
    std::ifstream file("no.txt");
    H = 3;
    W = 3;
    graph = vector<vector<int> >(H*W, vector<int>(W*H, 0));
    //int mapt[H][W];
    for(int row = 0; row < H; ++row){
    std::string line;
    std::getline(file, line);
    if (!file.good())
        return -1;

    std::stringstream iss(line);
    
        vector<int> tmp;
        for (int col = 0; col < W; ++col)
        {
            int temp_int;
            std::string val;
            std::getline(iss, val, ',');
            if ( !iss.good() )
                break;
            std::stringstream convertor(val);
            convertor >> temp_int;
            tmp.push_back(temp_int);   
        }
        map.push_back(tmp);
    }

    for(int i = 0; i < H; i++){
        for(int j = 0; j< W; j++){
            checkNeighbours(i,j);
        }   
    }

    printGraph();
    cout << endl;
    dijkstra(graph, 0); 
    cout << endl;

    printf("\n\n");

    Path2D(v1,v2);
    for(int i =0; i<v2.size(); i++){
        for(int j=0; j<v2[i].size(); j++){
            cout << fixed << setprecision(20)<< v2[i][j].first << " " <<fixed << setprecision(20)<< v2[i][j].second << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0; 
} 
