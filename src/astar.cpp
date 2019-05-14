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
using namespace std;

//#define W 3 //362
//#define H 3 //366
// Arrays to convert 1D data into 2D array
int H,W;
vector<vector<int> > map;
vector<vector<int> > graph;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

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
double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
void tracePath(cell **cellDetails, Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
    {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));
    while (!Path.empty())
    {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }

    return;
}

//Utility function to map the data into the graph
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



// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStar(vector<vector<int> > &graph, Pair src, Pair dest)
{
    int row_max = map.size();
    int col_max = map[0].size();
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
                tracePath(cellDetails, dest);
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
                hNew = calculateHValue(i - 1, j, dest);
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
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
          
            else if (closedList[i + 1][j] == false &&
                     isUnBlocked(graph, i + 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
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
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            
            else if (closedList[i][j + 1] == false &&
                     isUnBlocked(graph, i, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
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
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

     
            else if (closedList[i][j - 1] == false &&
                     isUnBlocked(graph, i, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
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
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

          
            else if (closedList[i - 1][j + 1] == false &&
                     isUnBlocked(graph, i - 1, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1, dest);
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
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

          
            else if (closedList[i - 1][j - 1] == false &&
                     isUnBlocked(graph, i - 1, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, dest);
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
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

     
            else if (closedList[i + 1][j + 1] == false &&
                     isUnBlocked(graph, i + 1, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, dest);
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
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

   
            else if (closedList[i + 1][j - 1] == false &&
                     isUnBlocked(graph, i + 1, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, dest);
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
    cout << "asdf" << endl;
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
    ifstream file("no.txt");
    H = 3;
    W = 3;
    graph = vector<vector<int> >(H*W, vector<int>(W*H, 0));
  
    for(int row = 0; row < H; ++row){
        string line;
        getline(file, line);
        if (!file.good())
            return -1;

        stringstream iss(line);
    
        vector<int> tmp;
        for (int col = 0; col < W; ++col)
        {
            int temp_int;
            string val;
            getline(iss, val, ',');
            if ( !iss.good() )
                break;
            stringstream convertor(val);
            convertor >> temp_int;
            tmp.push_back(temp_int);  
        }
        map.push_back(tmp);
    }
    file.close();

    for(int i =0; i < H; i++){
        for(int j=0; j< W; j++){
            checkNeighbours(i,j);
        }
    }

    printGraph();
    /* Description of the Grid- 
     1--> The cell is not blocked 
     0--> The cell is blocked    */
    // int grid[H][W] =
    //     {
    //         {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
    //         {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
    //         {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
    //         {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    //         {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    //         {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
    //         {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    //         {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
    //         {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}};

    // // Source is the left-most bottom-most corner
     Pair src = make_pair(0, 1);

    // // Destination is the left-most top-most corner
     Pair dest = make_pair(0,2);

    aStar(graph, src, dest);
     cout << endl;
    return (0);
}