#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include "linkedlist.h"
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;
// using namespace utils; // for the function defined in utils

// getInput function
// Parameters: 
// Output: input_array[] 
int get_input(List Stack, string in, int *input_array){
    int len,board_size,col,row = 0;
    int count = 1;
    len = in.length();
    char c_array[len+1];
    char *tmp;
    strcpy(c_array,in.c_str());
    tmp = strtok(c_array," ");
    if(tmp) board_size = atoi(tmp);
    
    // Making input array
    // input_array = {size, col_1, row_1, col_2...}
    while(tmp!=NULL){
      tmp = strtok(NULL," ");
      if(tmp){ 
        col = atoi(tmp);
        tmp = strtok(NULL," ");
        row = atoi(tmp);
        //input_array
        input_array[count] = col;
        input_array[count+1] = row;
        input_array[0]+=2;
        count+=2;
      }
    }
    return board_size;
}
// makeBoard function
// Parameters: col,row,board(int,int,int**)
// Output: updated board[][] (int[][])
int **make_board(int col, int row, int **board){
  // Vertical
  cout<<"1"<<endl;
  int board_size = board[0][0];
  cout<<"2"<<endl;
  int x0,x1,x2,x3,x4,y0,y1,y2,y3,y4;
  if(board[0][col] == 0){
    y0 = 1;
    while(y0 <= board_size){
      board[y0][col] = 1;
      y0++;
    }
    board[0][col] = 1;
  }
  // Horizontal
  if(board[row][0] == 0){
    x0 = 1;
    while(x0 <= board_size){
      board[row][x0] = 1;
      x0++;
    }
    board[row][0] = 1;
  }

  // Top Left to Bottom Right
  x1 = col-1;
  y1 = row-1;

  x2 = col+1;
  y2 = row+1;
  // Top Right to Bottom Left
  x3 = col-1;
  y3 = row+1;

  x4 = col+1;
  y4 = row-1;
  bool b1,b2,b3,b4;
  b1 = false;
  b2 = false;
  b3 = false;
  b4 = false;
  bool finished = false;
  while(!finished){
    if(!b1){
      if((x1 > 0)&&(y1 > 0)){
        if(board[y1][x1]==0)
          board[y1][x1] = 1;
        x1--;
        y1--;
      }else{
        b1 = true;
      }
    }
    if(!b2){
      if((x2 <= board_size)&&(y2 <= board_size)){
        if(board[y2][x2]==0)
          board[y2][x2] = 1;
        x2++;
        y2++;
      }else{
        b2 = true;
      }
    }
    if(!b3){
      if((x3 > 0)&&(y3 <= board_size)){
        if(board[y3][x3]==0)
          board[y3][x3] = 1;
        x3--;
        y3++;
      }else{
        b3 = true;
      }
    }
    if(!b4){
      if((x4 <= board_size)&&(y4 > 0)){
        if(board[y4][x4]==0)
          board[y4][x4] = 1;
        x4++;
        y4--;
      }else{
        b4 = true;
      }
    }
    board[row][col] = 2;
    finished = (b1&&b2&&b3&&b4);
  }
  return board;
}
// find empty square function
// return int[2] (col,row) or (-1,-1) if no squares are found
void find_empty_square(int *coordinates,int **board){
  int board_size = board[0][0];
  for(int i = 1; i <= board_size; i++){
    if(board[i][0] == 0){
      for(int j = 1; j <= board_size; j++){
        if(board[i][j] == 0){
          coordinates[0] = j;
          coordinates[1] = i;
          return;
        }
      }
    }
  }
  coordinates[0] = -1;
  coordinates[1] = -1;
}
void print_board(int **board){
  for(int i = 0; i <= board[0][0]; i++){
      for(int j = 0; j <= board[0][0]; j++){
        if(board[i][j] == 1){
         cout<<"*  ";
        }else if(board[i][j] == 0){
          cout<<"-  ";
        }else if(board[i][j] == 2){
          cout<<"Q  ";
        }else if(board[i][j] == 3){
          cout<<"@  ";
        }else{
          cout<<board[i][j]<<"  ";
        }
      }
      cout<<endl;
  }
}
// 0 = false
// 1 = true
// (board_size) = Complete
int isFull(int **board){
  int Queen_Counter = 0;
  for(int i = 1; i <= board[0][0]; i++){
    for(int j = 1; j <= board[0][0]; j++){
      if(board[i][j] == 0){
        return 0;
      }else if(board[i][j] == 2){
        Queen_Counter++;
      }
    }
  }
  if(Queen_Counter==board[0][0]){
    return Queen_Counter;
  }
  return 1;
}
// Given a node, delete it, freeing the memory
void deleteNode(Node *N)
{
    for(int i = 0; i <= N->board[0][0]; i++){
        delete(N->board[i]);
    }
    delete(N); 
}
int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }
    List Stack;
    int *coordinates = new int[1];
    int *input_array = new int[1];
    int **board = NULL;

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string in;
    getline(input,in);

    int board_size = get_input(Stack,in,input_array);
    // ---------- Allocating Memory For Starting Board ----------
    board = new int*[board_size];
    for(int i = 0; i <= board_size; i++){
      board[i] = new int[board_size];
    }
    board[0][0] = board_size;
    // ------------Setting Up Starting Board----------------------
    for(int i = 1; i <= input_array[0]; i+=2){
        make_board(input_array[i],input_array[i+1],board);
        print_board(board);
    }
    // -------------Stack Operations------------------------------
    Node* first_board = Stack.makeNode(board_size);
    // Copy Board
    for(int i = 0; i <= board_size; i++){
      for(int j = 0; j <= board_size; j++){
        first_board->board[i][j] = board[i][j];
      }
    }
    bool solved = false;
    Stack.push(first_board);
    Node* cur = Stack.getHead();
    Node* printing_node;
    Node* del;
    Node* newNode;
    int inf_blocker=0;
    while((!solved)&&(Stack.getLength() > 0)){
      printing_node = Stack.getHead();
      cout<<"--------------------------"<<inf_blocker<<endl;
      for(int i = 1; i <= Stack.getLength(); i++){
        print_board(printing_node->board);
        printing_node = printing_node->next;
        cout<<endl;
      }
      cout<<"endendednednendnednendendnendne"<<endl;
      
      find_empty_square(coordinates,cur->board);
      newNode = Stack.makeNode(board_size);
      // Copy Board
      for(int i = 0; i <= board_size; i++){
        for(int j = 0; j <= board_size; j++){
          newNode->board[i][j] = cur->board[i][j];
        }
      }
      newNode->col = coordinates[0];
      newNode->row = coordinates[1];
      make_board(newNode->col,newNode->row,newNode->board);
      cur->board[newNode->row][newNode->col] = 3;
      if(isFull(newNode->board) > 1){   // Board is full and solved
        solved = true;
        cout<<"Solved!"<<endl;
        print_board(newNode->board);
      }else if(isFull(newNode->board) == 0){ // Board is not full
        Stack.push(newNode);
      }else if(isFull(newNode->board) == 1){ // Board is full and not solved
        if(isFull(cur->board) == 1){
          del = Stack.pop();
          //deleteNode(del);
        }
        //del = newNode;
        //deleteNode(del);
      }
      cur = Stack.getHead();
      inf_blocker++;
    }
    cur = NULL;
    del = NULL;
    newNode = NULL;
    
    input.close(); //close input stream
    output.close(); // close output stream
}
