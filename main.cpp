#include <iostream>
#include<bits/stdc++.h>
using namespace std;

void print_sudoko(int arr[9][9])
{
  cout<<"--------------------"<<endl;
  for(int r=0;r<9;r++)
    {
      for(int cell = 0; cell<9; cell++)
        {
          cout<<arr[r][cell]<<" ";
        }
      cout<<endl;
    }
  cout<<"--------------------"<<endl;
}

bool canPlace(int arr[9][9], int row, int col, int n)
{
  if(arr[row][col]!=0)
  {
    return false;
  }
  int gridx = (col/3) * 3;
  int gridy = (row/3) *3;
  bool status = true;
  for(int i=0;i<9;i++)
    {
      
    if(arr[row][i]== n)
    {
      status = false;
      break;
    }
    if(arr[i][col]==n)
    {
      status = false;
      break;
    }
    if(arr[gridy + i/3][gridx +i%3] == n)
    {
      status = false;
      break;
    }
    } 
  return status;
}

vector<int> findPlaces(int arr[9][9], int r, int c)
  {
    vector<int> cps = {};
    for(int i = 1;i<=9;i++)
      {
        if(canPlace(arr,r,c,i))
        {
          cps.push_back(i);
        }
      }
    return cps;
  }
void copy(int arr[9][9], int arrCopy[9][9])
{
  for(int i = 0;i<9;i++)
    {
      for(int j=0;j<9;j++)
        {
          arrCopy[i][j] = arr[i][j];
          
        }
    }
}

void nextEmpty(int arr[9][9], int row, int col, int &nextRow, int &nextCol)
{
  int index = 81;
  for(int  i=row*9 + col+1;i<81;i++)
    {
      if(arr[i/9][i%9] == 0)
      {
        index = i;
        break;
      }
    }
  nextRow = index/9;
  nextCol = index%9;
  
}

bool solveSudoko(int arr[9][9], int row, int col)
{
  // system("cls");
  // print_sudoko(arr);
  if(row>8)
  {
    return true;
  }
  if(arr[row][col]!=0)
  {
    int nextRow, nextCol;
    nextEmpty(arr, row, col, nextRow, nextCol);
    return solveSudoko(arr, nextRow, nextCol);
    
  }
  
  vector<int> placeables = findPlaces(arr, row, col);
  if(placeables.size()==0)
  {
    return false;
  }
  bool status = false;
  for(int i=0;i<placeables.size(); i++)
    {
     int n = placeables[i];
      int arrCpy[9][9];
      copy(arr, arrCpy);
      arrCpy[row][col] = n;
      int nextRow, nextCol;
      nextEmpty(arrCpy, row, col, nextRow, nextCol);
      if(solveSudoko(arrCpy, nextRow, nextCol))
      {
        copy(arrCpy, arr);
        status = true;
          break;
          
      }
    }
  return status;
}
  
int main()
{
  int board[9][9] = {
      {0,5,2,0,0,6,0,0,0},
      {1,6,0,9,0,0,0,0,4},
      {0,4,9,8,0,3,6,2,0},
      {4,0,0,0,0,0,8,0,0},
      {0,8,3,2,0,1,5,9,0},
      {0,0,1,0,0,0,0,0,2},
      {0,9,7,3,0,5,2,4,0},
      {2,0,0,0,0,9,0,5,6},
      {0,0,0,1,0,0,9,7,0}
  };
  // print_sudoko(board);
  solveSudoko(board, 0, 0);
  print_sudoko(board);
}