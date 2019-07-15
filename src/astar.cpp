// A C++ Program to implement A* Search Algorithm

#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include "yaml-cpp/yaml.h"


using namespace std;

typedef pair<int,int> pathTemp;
typedef pair<double,double> pathStore;

//resolution value
double resolution = 0.0500000007451;
// Arrays to convert 1D data into 2D array
int H,W;
vector<vector<int> > map1;
vector<vector<int> > graph;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;
vector<pathStore> vecPath;

// A structure to hold the neccesary parameters
struct cell
{
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col, int row_max, int col_max)
{
    // Returns true if row number and column number is in range
    return (row >= 0) && (row < row_max) &&
           (col >= 0) && (col < col_max);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(vector<vector<int> > &graph, int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (graph[row][col] == 0 || -1)
        return (true);
    else
        return (false);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair src, Pair dest)
{
    double dx1,dy1,dx2,dy2,cross,heuristic = 0;
    if(map1[row][col] == 3) {
        heuristic = 1000;
        return heuristic;
    }
    dx1 = row - dest.first;
    dy1 = col - dest.second;
    dx2 = src.first - dest.first;
    dy2 = src.second - dest.second;
    cross = dx1*dy2 - dx2*dy1;
    heuristic += cross*0.001;
    return heuristic;
    // Return using the distance formula
    //return ((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

// double calculateHValue(int row, int col, Pair dest){
//     return (abs((row - dest.first)+(col-dest.second)));
// }

// double calculateHValue(int row, int col, Pair dest){
//     double m = max(abs((row - dest.first)),abs((col-dest.second)));
//     return (m);
// }

// A Utility Function to trace the path from the source
// to destination
vector<pathStore> trace(cell **cellDetails, Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    double x,y;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
    {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    vector<pathTemp> vecTemp;

    Path.push(make_pair(row, col));
    while (!Path.empty())
    {
        pair<int, int> p = Path.top();

        Path.pop();
        vecTemp.push_back(make_pair(p.first,p.second));
        cout << "-> (" << p.first << "," << p.second << ") ";
    }

    cout << endl;

    for(int i=0; i<vecTemp.size(); i++){

        x = (vecTemp[i].first)%W;
        y = (vecTemp[i].second)/W;
        x = x*resolution;
        y = y*resolution;
        vecPath.push_back(make_pair(y,x));
    }
        cout << "\nPath in resolution" << endl;
        for(int i =0; i<vecPath.size();i++){
            cout << fixed << setprecision(20)<< vecPath[i].first << " " <<fixed << setprecision(20)<< vecPath[i].second << " " << endl;
        }
        cout << endl;

    return vecPath;
}


//Utility function to map1 the data into the graph
void checkNeighbours(int row, int col){
    int rneigh,cneigh,i,j;
    int row_max = map1.size();
    int col_max = map1[0].size();
    i = (row*W)+col;
    if (isValid(row-1,col, row_max, col_max) == true){
        rneigh = row-1;
        cneigh = col;
        j = (rneigh*W)+cneigh;
        if(map1[row-1][col] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
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
        if(map1[row+1][col] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
     
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
        if(map1[row][col+1] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
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
      
        if(map1[row][col-1] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
           
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
   
        if(map1[row-1][col+1] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
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
        if(map1[row-1][col-1] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
        
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
        j = (rneigh*W)+cneigh;
        if(map1[row+1][col+1] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
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
        if(map1[row+1][col-1] == 3 || map1[row][col] == 3){
            graph[i][j] = 3;
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

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStar(vector<vector<int> > &graph, Pair src, Pair dest)
{
    int row_max = map1.size();
    int col_max = map1[0].size();
    // If the source is out of range
    if (isValid(src.first, src.second, row_max,col_max) == false)
    {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second,row_max,col_max) == false)
    {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (isUnBlocked(graph, src.first, src.second) == false ||
        isUnBlocked(graph, dest.first, dest.second) == false)
    {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest) == true)
    {
        printf("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which means
    // that no cell has been included yet
    // This closed list is implemented as a boolean 2D array
    bool closedList[H][W];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    //of that cell
    cell **cellDetails;
    cellDetails = new cell*[H];
    for (int i = 0; i < H; i++) {
        cellDetails[i] = new cell[W];
    }

    int i, j;

    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++) 
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /* 
     Create an open list having information as <f, <i, j>> 
     where f = g + h, and i, j are the row and column index of that cell 
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
     This open list is implenented as a set of pair of pair.*/
    set<pPair> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- (North) ------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j,row_max,col_max) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j] == false &&
                     isUnBlocked(graph, i - 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, src,dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == FLT_MAX ||
                    cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                              make_pair(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- (South) ------------

        if (isValid(i + 1, j,row_max,col_max) == true)
        {
           
            if (isDestination(i + 1, j, dest) == true)
            {
               
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }
          
            else if (closedList[i + 1][j] == false &&
                     isUnBlocked(graph, i + 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j,src, dest);
                fNew = gNew + hNew;

               
                if (cellDetails[i + 1][j].f == FLT_MAX ||
                    cellDetails[i + 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                  
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //-----------  (East) -----------

     
        if (isValid(i, j + 1,row_max,col_max) == true)
        {
            
            if (isDestination(i, j + 1, dest) == true)
            {
                
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
            vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }

            
            else if (closedList[i][j + 1] == false &&
                     isUnBlocked(graph, i, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, src,dest);
                fNew = gNew + hNew;

               
                if (cellDetails[i][j + 1].f == FLT_MAX ||
                    cellDetails[i][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                              make_pair(i, j + 1)));

                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- (West) ------------

       
        if (isValid(i, j - 1,row_max,col_max) == true)
        {
           
            if (isDestination(i, j - 1, dest) == true)
            {
               
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
            vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }

     
            else if (closedList[i][j - 1] == false &&
                     isUnBlocked(graph, i, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1,src, dest);
                fNew = gNew + hNew;

             
                if (cellDetails[i][j - 1].f == FLT_MAX ||
                    cellDetails[i][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                              make_pair(i, j - 1)));

                
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        //----------- (North-East) ------------

       
        if (isValid(i - 1, j + 1,row_max,col_max) == true)
        {
           
            if (isDestination(i - 1, j + 1, dest) == true)
            {
                
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }

          
            else if (closedList[i - 1][j + 1] == false &&
                     isUnBlocked(graph, i - 1, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1,src, dest);
                fNew = gNew + hNew;

              
                if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
                    cellDetails[i - 1][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                              make_pair(i - 1, j + 1)));

                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- (North-West) ------------

   
        if (isValid(i - 1, j - 1,row_max,col_max) == true)
        {
        
            if (isDestination(i - 1, j - 1, dest) == true)
            {
      
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }

          
            else if (closedList[i - 1][j - 1] == false &&
                     isUnBlocked(graph, i - 1, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, src,dest);
                fNew = gNew + hNew;

       
                if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
                    cellDetails[i - 1][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
                
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }

        //----------- (South-East) ------------

        if (isValid(i + 1, j + 1,row_max,col_max) == true)
        {
       
            if (isDestination(i + 1, j + 1, dest) == true)
            {
         
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }

     
            else if (closedList[i + 1][j + 1] == false &&
                     isUnBlocked(graph, i + 1, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, src,dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
                    cellDetails[i + 1][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                              make_pair(i + 1, j + 1)));

                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }

        //-----------  (South-West) ------------

    
        if (isValid(i + 1, j - 1,row_max,col_max) == true)
        {
          
            if (isDestination(i + 1, j - 1, dest) == true)
            {
            
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                vecPath = trace(cellDetails, dest);
                foundDest = true;
                return;
            }

   
            else if (closedList[i + 1][j - 1] == false &&
                     isUnBlocked(graph, i + 1, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, src,dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
                    cellDetails[i + 1][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                              make_pair(i + 1, j - 1)));

                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to blockages)
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
    //deallocation of cellDetails
    for(int indx=0;indx<H;indx++){
        for(int indx2=0;indx2<W;indx++)
        delete cellDetails[indx];
    }
    delete []cellDetails;
}

void printGraph(){
    for(int i =0; i < graph.size(); i++){
        for(int j=0; j<graph[i].size();j++){
            cout << graph[i][j] << " \t";
        }
        cout << endl;
    }
}



// Driver program to test above function
int main()
{
    ifstream file("new.txt");
    H = 122;
    W = 121;
    graph = vector<vector<int> >(H*W, vector<int>(W*H, 0));
    std::string line;
    std::getline(file, line);
    // if (!file.good())   ///CHECK THIS OUT
    //     return -1;
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

    for(int i =0; i < H; i++){
        for(int j=0; j< W; j++){
            checkNeighbours(i,j);
        }
      
    }

    cout << endl;
    cout << "+++ PRINTING GRAPH +++" << endl;
    cout << endl;
    //printGraph();
 
    // // Source is the left-most bottom-most corner
    Pair src = make_pair(120, 120);

    // // Destination is the left-most top-most corner
    Pair dest = make_pair(10,10);
    cout << endl;
    cout << "+++ COMPUTING ASTAR SOLUTION +++" << endl;
    cout << endl;
    aStar(graph, src, dest);
    
    YAML::Emitter yaml_out;
    yaml_out << YAML::BeginMap;
    yaml_out << YAML::Key << "waypoint";
    yaml_out << YAML::Value << YAML::BeginSeq ;
    for(int i =0; i<vecPath.size();i++)
    {
        yaml_out << YAML::BeginMap;    
        yaml_out << YAML::Key <<"position";
        yaml_out << YAML::Value << YAML::BeginMap;
        yaml_out << YAML::Key << "x";
        yaml_out << YAML::Value << vecPath[i].first;
        yaml_out << YAML::Key << "y";
        yaml_out << YAML::Value << vecPath[i].second;
        yaml_out << YAML::Key << "z";
        yaml_out << YAML::Value << "3.0";
        yaml_out << YAML::EndMap;
        yaml_out << YAML::Key << "orientation";
        yaml_out << YAML::Value << YAML::BeginMap;
        yaml_out << YAML::Key << "x";
        yaml_out << YAML::Value << "0.0444210774910485";
        yaml_out << YAML::Key << "y";
        yaml_out << YAML::Value << "-0.03997364552703113";
        yaml_out << YAML::Key << "z";
        yaml_out << YAML::Value << "0.7459565426241741";
        yaml_out << YAML::Key << "w";
        yaml_out << YAML::Value << "0.66330815768691";
        yaml_out << YAML::EndMap;
        yaml_out << YAML::EndMap;
    }                   
    yaml_out << YAML::EndSeq;
    yaml_out << YAML::EndMap;
    cout << "Here's the output YAML:\n" << yaml_out.c_str();
    
    cout << endl;

    ofstream inFile;
    inFile.open("yamlastardata.yaml");
    inFile << yaml_out.c_str();

    inFile.close();
    return 0;
}