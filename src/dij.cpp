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

#define KERNEL_SIZE 3
#define ORIGIN_MAP 15

//resolution value
double resolution = 0.0500000007451;
//Arrays to map 1D into 2D
int H ,W;
vector<vector<int> > map;
vector<vector<int> > graph;
//vectors to store path
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
    i = (row*(W)+col);
    if (isValid(row-1,col, row_max, col_max) == true){
        rneigh = row-1;
        cneigh = col;
        j = (rneigh*W)+cneigh;
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
        j = (rneigh*W)+cneigh;   
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
        j = (rneigh*W)+cneigh;
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
        j = (rneigh*W)+cneigh;
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
        j = (rneigh*W)+cneigh;
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
        j = (rneigh*W)+cneigh;
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
        j = (rneigh*(W))+cneigh;
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
        j = (rneigh*W)+cneigh;
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
int minDistance(int dist[], bool spt[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
    for (int v = 0; v < H*W; v++) 
        if (spt[v] == false && dist[v] <= min){
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
void printSolution(int src, int dist[], int n, int parent[]) 
{ 
    
    cout << "Vertex\t\t Distance\tPath" << endl;
    for (int i = 0; i < H*W; i++) 
    { 
        vector<int> v;
        cout << endl;
        cout << src << " -> " << i <<" \t\t " << dist[i] << "\t\t" << src;   
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
            x = x*resolution*KERNEL_SIZE;
            y = (v1[i][j])/W;
            y = y*resolution*KERNEL_SIZE;
            x = x-ORIGIN_MAP;
            y = y-ORIGIN_MAP;
            tmp.push_back(make_pair(x,y));
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
    bool spt[H*W]; 
  
    // Parent array to store shortest path tree 
    int parent[H*W]; 
  
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < H*W; i++) 
    { 
        parent[0] = -1; 
        dist[i] = INT_MAX;
        spt[i] = false; 
    } 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int i = 0; i < H*W - 1; i++) 
    { 
        // Pick the minimum distance vertex from the set of 
        // vertices not yet processed. u is always equal to src in first iteration. 
        int l = minDistance(dist, spt); 
  
        // Mark the picked vertex as processed 
        spt[l] = true; 
  
        // Update dist value of the  
        // adjacent vertices of the 
        // picked vertex. 
        for (int v = 0; v < H*W; v++) {

            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and  
            // total weight of path from src to v through u is smaller 
            // than current value of dist[v] 
            if (!spt[v] && graph[l][v] && 
                dist[l] != INT_MAX && dist[l]+ graph[l][v] < dist[v]) 
            { 
                parent[v] = l; 
                dist[v] = dist[l] + graph[l][v]; 
            }  
        }
    } 
    // print the constructed distance array 
    printSolution(src,dist, H*W, parent); 
} 
  
// Driver Code 
int main() 
{ 
    std::ifstream file("new.txt");
    H = 122;
    W = 121;
    graph = vector<vector<int> >(H*W, vector<int>(W*H, 0));
    //int mapt[H][W];
    //for(int row = 0; row < H; ++row){
    std::string line;
    std::getline(file, line);
    

    std::stringstream iss(line);

    for(int row = 0; row < H; ++row){
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

    file.close();
    
    cout << endl;
    cout << "+++ FILE WAS READ CORRECTLY +++" << endl;
    cout << endl;

    for(int i = 0; i < H; i++){
        for(int j = 0; j< W; j++){
            checkNeighbours(i,j);
        }   
    }

    cout << endl;
    cout << "+++ PRINTING GRAPH +++" << endl;
    cout << endl;
    //printGraph();

    cout << endl;
    cout << "+++ COMPUTING DIJKSTRA SOLUTION +++" << endl;
    cout << endl;
    dijkstra(graph, 0); 
    cout << endl;

    cout << endl;
    cout << "+++ COMPUTING PATH IN RESOLUTION +++" << endl;
    cout << endl;
    Path2D(v1,v2);
    // // for(int i =0; i<v2.size(); i++){
    // //     for(int j=0; j<v2[i].size(); j++){
    // //         cout << fixed << setprecision(20)<< v2[i][j].first << " " << fixed << setprecision(20)<< v2[i][j].second << endl;
    // //     }
    // //     cout << endl;
    // // }

    cout << endl;
    cout << "PATH FOR LAST VERTEX" << endl;

    int i = v2.size()-1;
    int j = 0;

    for(i =v2.size()-1; i>0; i--)
    {
        if(i==v2.size()-2){
            break;
        }
        else{
            for(j=0; j<v2[i].size(); j++){
                cout << fixed << setprecision(20)<< v2[i][j].first << " " << fixed << setprecision(20)<< v2[i][j].second << " ";   
            }
            cout << endl;
            }
    }
 

    cout << endl;

  
    return 0; 
} 
