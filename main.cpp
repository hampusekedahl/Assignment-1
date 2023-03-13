//
//  main.cpp
//  Assignment 2
//
//  Created by Hampus Ekedahl on 2023-03-01.
//

#include <iostream>

#define N 9
#define EMPTY 0

bool valid(int grid[N][N], int i, int j, int value){
    for(int col = 0; col < N; col++){
        if(grid[i][col] == value){
            return false;
        }
    }
    
    for(int row = 0; row < N; row++){
        if(grid[row][j] == value){
            return false;
        }
    }
    
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + (i - i % 3)][col + (j - j % 3)] == value){
                return false;
            }
    
    return true;
}

bool findEmpty(int grid[N][N], int &i, int &j){
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(grid[i][j] == EMPTY){
                return true;
            }
        }
    }
    
    return false;
}

bool Solution(int grid[N][N])
{
    int row, col;
 
    if (!findEmpty(grid, row, col))
        return true;
    
    for (int num = 1; num <= 9; num++)
    {
        
        if (valid(grid, row, col, num))
        {
             
            grid[row][col] = num;
 
            if (Solution(grid))
                return true;
 
            grid[row][col] = EMPTY;
        }
    }
    
    return false;
}

void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            std::cout << grid[row][col] << " ";
        std::cout << std::endl;
    }
}


int main(int argc, const char * argv[]) {
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                           { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                           { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                           { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                           { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                           { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                           { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                           { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                           { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    
    if (Solution(grid) == true)
        printGrid(grid);
    else
        std::cout << "No solution exists";
     
    return 0;
}
