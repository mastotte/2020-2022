#include <iostream>
#include <fstream>
#include "linkedlist.h"
#include <stdlib.h>

using namespace std;
// using namespace utils; // for the function defined in utils

// Returns next number in input line
int get_next_number(string in){
  string out = "";
  in = in.substr(in.find_first_not_of(" "),in.length());
  out = in.substr(0,in.find_first_of(" "));
  return stoi(out);
}

// makeBoard function
// Parameters: col,row,board(int,int,int**)
// Output: updated board[][] (int[][])
int **make_board(int col, int row, int **board){
  
  int board_size = board[0][0];
  int x0,x1,x2,x3,x4,y0,y1,y2,y3,y4;
  // Vertical
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
// prints board (Q = Queen,* = covered square, - = open square, @ = eliminated path)
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
// Solves queens problem, returns output string
string solve(string in, int board_size){
  // Variable declaration
  List Stack;
  int col,row = 0;
  int *coordinates = new int[2];
  int **board = NULL;
  // ---------- Allocating Memory For Starting Board ----------
  board = new int*[board_size+1];
  for(int i = 0; i <= board_size; i++){
    board[i] = new int[board_size];
  }
  board[0][0] = board_size;
  // ------------Setting Up Starting Board----------------------
  while(in.length()>1){
    col = get_next_number(in);
    in = in.substr(in.find_first_of(" ")+1,in.length());
    row = get_next_number(in);
    in = in.substr(in.find_first_of(" ")+1,in.length());

    make_board(col,row,board);
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
    bool no_solution = false;
    int b_col,b_row = 0;
    Stack.push(first_board);
    Node* cur = Stack.getHead();
    //Node* printing_node;
    Node* del;
    Node* newNode;
    int inf_blocker=0;
    while((!solved)&&(!no_solution)){
      /*cout<<"Length: "<<Stack.getLength()<<endl;
      printing_node = Stack.getHead();
      cout<<"--------------------------"<<inf_blocker<<endl;
      for(int i = 1; i <= Stack.getLength(); i++){
        print_board(printing_node->board);
        printing_node = printing_node->next;
        cout<<endl;
      }
      cout<<"endendednednendnednendendnendne"<<endl;
      */
      find_empty_square(coordinates,cur->board);
      // Copy Board
      for(int i = 0; i <= board_size; i++){
        for(int j = 0; j <= board_size; j++){
          board[i][j] = cur->board[i][j];
        }
      }
      b_col = coordinates[0];
      b_row = coordinates[1];
      make_board(b_col,b_row,board);
      cur->board[b_row][b_col] = 3;
      if(isFull(board) > 1){   // Board is full and solved
        solved = true;
        //cout<<"Solved!"<<endl;
        //print_board(board);
      }else if(isFull(board) == 0){ // Board is not full
        newNode = Stack.makeNode(board_size);
        newNode->row = b_row;
        newNode->col = b_col;
        // Copy board
        for(int i = 0; i <= board_size; i++){
          for(int j = 0; j <= board_size; j++){
            newNode->board[i][j] = board[i][j];
          }
        }
        Stack.push(newNode);
      }else if(isFull(board) == 1){ // Board is full and not solved
        if(Stack.getLength()==1){ // Only board available is full, it's unsolvable
          no_solution = true;

          //deleteNode(cur);
        }
        else if(isFull(cur->board) == 1){
          del = Stack.pop();
          deleteNode(del);
        }
      }
      cur = Stack.getHead();
      inf_blocker++;
    }
    string out = "";
    // Finding Queen Locations
    if(no_solution){
      out = "No solution";
    }else{
      for(int i = 1; i <= board_size; i++){
        for(int j = 1; j <= board_size; j++){
          if(board[j][i] == 2){
            out = out + to_string(i) + " " + to_string(j) + " ";
          }
        }
      }
    }
    cur = NULL;
    del = NULL;
    newNode = NULL;
  return out;
}
int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }
    int board_size = 0;
    
    //int *input_array = new int[2];


    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
    
    string in;
    string out;
    while(getline(input,in)){
      //cout<<in<<endl;
      board_size = get_next_number(in);
      in = in.substr(in.find_first_of(" ")+1,in.length());

      out = solve(in, board_size);
      output<<out<<endl;
      
    }

    input.close(); //close input stream
    output.close(); // close output stream
}
// save the new coord that was added
// dont add boards that are dead ends
// if all a board's empty squares are dead ends, make it null or something, and make it's open square on
// the previous board (new head) a 1.
