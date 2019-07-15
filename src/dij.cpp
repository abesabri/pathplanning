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
#include "yaml-cpp/yaml.h"

using namespace std;

//resolution value
double resolution = 0.0500000007451;
//Arrays to map 1D into 2D
int H ,W;
vector<vector<int> > map1;
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
    int row_max = map1.size();
    int col_max = map1[0].size();
    i = (row*(W)+col);
    if (isValid(row-1,col, row_max, col_max) == true){
        rneigh = row-1;
        cneigh = col;
        j = (rneigh*W)+cneigh;
        if(map1[row-1][col] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row-1][col] == -1 || map1[row][col] == -1){
            graph[i][j] = 50; 
        }
        else if(map1[row-1][col] == 0 || map1[row][col] == 0){
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
        if(map1[row+1][col] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row+1][col] == -1 || map1[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map1[row+1][col] == 0){
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
        if(map1[row][col+1] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row][col+1] == -1 || map1[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map1[row][col+1] == 0){
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
        if(map1[row][col-1] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row][col-1] == -1 || map1[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map1[row][col-1] == 0){
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
        if(map1[row-1][col+1] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row-1][col+1] == -1 || map1[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map1[row-1][col+1] == 0){
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
        if(map1[row-1][col-1] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row-1][col-1] == -1 || map1[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map1[row-1][col-1] == 0){
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
        if(map1[row+1][col+1] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row+1][col+1] == -1 || map1[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map1[row+1][col+1] == 0){
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
        if(map1[row+1][col-1] == 100 || map1[row][col] == 100){
            graph[i][j] = 100;
        }
        else if(map1[row+1][col-1] == -1 || map1[row][col] == -1){
            graph[i][j] = 50;
        }
        else if(map1[row+1][col-1] == 0){
            graph[i][j] = 1;
        }
        else{
            graph[i][j] = 0;
        }
    }
}


// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree 
int mDist(int dist[], bool spt[]) 
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
void printSolution(int dist[], int n, int parent[]) 
{ 
    int src = 0; 
    cout << "Vertex\t\t Distance\tPath" << endl;
    for (int i = 1; i < H*W; i++) 
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
            x = (v1[i][j])*resolution*3;
            y = (v1[i][j])*resolution*3;
            x = x-32;
            y = y-7;
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
        int l = mDist(dist, spt); 
  
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
    printSolution(dist, H*W, parent); 
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
    if (!file.good())
       return -1;

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
        map1.push_back(tmp);
    }

    file.close();

    for(int i =0; i < map1.size(); i++){
        for(int j=0; j<map1[i].size();j++){
            cout << map1[i][j] << "\t";
        }
        cout << endl;
    }

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
    for(int i =0; i<v2.size(); i++){
        for(int j=0; j<v2[i].size(); j++){
            cout << fixed << setprecision(20)<< v2[i][j].first << " " <<fixed << setprecision(20)<< v2[i][j].second << " ";
        }
        cout << endl;
    }
    cout << endl;

    // YAML::Emitter yaml_out;
    // yaml_out << YAML::BeginMap;
    // yaml_out << YAML::Key << "waypoints";
    // yaml_out << YAML::Value << YAML::BeginSeq ;
    // for(int i =0; i<v2.size();i++)
    // {
    //     for(int j=0; j<v2[i].size();j++)
    //     {
    //         yaml_out << YAML::BeginMap;    
    //         yaml_out << YAML::Key <<"position";
    //         yaml_out << YAML::Value << YAML::BeginMap;
    //         yaml_out << YAML::Key << "x";
    //         yaml_out << YAML::Value << v2[i].first; 
    //         yaml_out << YAML::Key << "y";
    //         yaml_out << YAML::Value << v2[i].second;
    //         yaml_out << YAML::Key << "z";
    //         yaml_out << YAML::Value << "4.5";
    //         yaml_out << YAML::EndMap;
    //         yaml_out << YAML::Key << "orientation";
    //         yaml_out << YAML::Value << YAML::BeginMap;
    //         yaml_out << YAML::Key << "x";
    //         yaml_out << YAML::Value << "0.0444210774910485";
    //         yaml_out << YAML::Key << "y";
    //         yaml_out << YAML::Value << "-0.03997364552703113";
    //         yaml_out << YAML::Key << "z";
    //         yaml_out << YAML::Value << "0.7459565426241741";
    //         yaml_out << YAML::Key << "w";
    //         yaml_out << YAML::Value << "0.66330815768691";
    //         yaml_out << YAML::EndMap;
    //         yaml_out << YAML::EndMap;
    //     }
        
    // }                   
    // yaml_out << YAML::EndSeq;
    // yaml_out << YAML::EndMap;
    // cout << "Here's the output YAML:\n" << yaml_out.c_str();
    
    // cout << endl;

    // ofstream inFile;
    // inFile.open("../config/yamldijdata.yaml");
    // inFile << yaml_out.c_str();

    // inFile.close();    
    return 0; 
} 
