// C program for Dijkstra's single  
// source shortest path algorithm. 
// The program is for adjacency matrix 
// representation of the graph. 
#include <stdio.h> 
#include <limits.h> 
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
// Number of vertices in the graph 
#define H 3 //366 
#define W 3 //362
//Arrays to map 1D into 2D
int map[H][W];
int graph[H*W][H*W];
  

bool isValid(int row, int col)
{
    // Returns true if row number and column numbe is in range
    return (row >= 0) && (row < H) &&
           (col >= 0) && (col < W);
}

void checkNeighbours(int row, int col){
    int rneigh,cneigh,i,j;
    i = (row*H)+col;
    cneigh = col;
    rneigh = row;
    if (isValid(row-1,col) == true){
        rneigh -= 1;
        j = (rneigh*H)+cneigh;
        if(map[row-1][col] == 100 ){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row-1][col] == -1 ){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
    if (isValid(row+1,col) == true){
        rneigh += 1;
        j = (rneigh*H)+cneigh;
        if(map[row+1][col] == 100 ){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row+1][col] == -1 ){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
    if (isValid(row,col+1) == true){
        cneigh += 1; 
        j = (rneigh*H)+cneigh;
        if(map[row][col+1] == 100 ){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row][col+1] == -1 ){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
    if (isValid(row,col-1) == true){
        cneigh -= 1; 
        j = (rneigh*H)+cneigh;
        if(map[row][col-1] == 100 ){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row][col-1] == -1 ){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
    if (isValid(row-1,col+1) == true){
        rneigh -= 1;
        cneigh += 1; 
        j = (rneigh*H)+cneigh;
        if(map[row-1][col+1] == 100 ){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row-1][col+1] == -1 ){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
    if (isValid(row-1,col-1) == true){
        rneigh -= 1;
        cneigh -= 1; 
        j = (rneigh*H)+cneigh;
        if(map[row-1][col-1] == 100 ){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row-1][col-1] == -1){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
    if (isValid(row+1,col+1) == true){
        rneigh += 1;
        cneigh += 1; 
        j = (rneigh*H)+cneigh;
        if(map[row+1][col+1] == 100){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row+1][col+1] == -1 ){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
    if (isValid(row+1,col-1) == true){
        rneigh += 1;
        cneigh -= 1; 
        j = (rneigh*H)+cneigh;
        if(map[row+1][col-1] == 100 ){
            graph[i][j] = 100;
            graph[j][i] = 100;
        }
        else if(map[row+1][col-1] == -1 ){
            graph[i][j] = 50;
            graph[j][i] = 50;
        }
        else{
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
}


// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree 
int minDistance(int dist[], bool sptSet[]) 
{ 
      
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < H*W; v++) 
        if (sptSet[v] == false && 
                   dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 
  
// Function to print shortest path from source to int 
void printPath(int parent[], int x) 
{ 
    if (parent[x] == - 1) 
        return; 
  
    printPath(parent, parent[x]); 
  
    cout << "->" << x;
} 
  
// A utility function to print the constructed distance array 
void printSolution(int dist[], int n, int parent[]) 
{ 
    int src = 0; 
    printf("Vertex\t Distance\tPath"); 
    for (int i = 1; i < H*W; i++) 
    { 
        printf("\n%d -> %d \t\t %d\t\t%d", src, i, dist[i], src); 
        printPath(parent, i); 
    } 
} 


void printGraph(){
    for(int i =0; i < H*W; i++){
        for(int j=0; j<H*W;j++){
            cout << graph[i][j] << " \t";
        }
        cout << endl;
    }

}
  
// Funtion that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation 
void dijkstra(int graph[H*W][H*W], int src) 
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
                dist[u] + graph[u][v] < dist[v]) 
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

    for(int row = 0; row < H; ++row)
    {
        std::string line;
        std::getline(file, line);
        if ( !file.good() )
            break;

        std::stringstream iss(line);

        for (int col = 0; col < W; ++col)
        {
            std::string val;
            std::getline(iss, val, ',');
            if ( !iss.good() )
                break;

            std::stringstream convertor(val);
            convertor >> map[row][col];
        }
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
    
    return 0; 
} 