#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include "linkedlist.h"
#include <string>

using namespace std;
// using namespace utils; // for the function defined in utils

int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string in;
    getline(input,in);

    // Get input
    //
    // Set up board (given queen locations, mark 1 or 0 . Check if square is already 1 .)
    // 
    // - use [0,0] to show how many open spaces left.
    // - if (open spaces < queens remaining) board is not possible.
    // - use row 0 to indicate rows without queens
    // 










  int x1,x2,x3,x4,y1,y2,y3,y4;
  int x_val,y_val;
  // Horizontal
  y = 1;
  while(y < board_size){
      board[x_val][y] = 1;
      y++;
  }
  // Vertical
  x = 1;
  while(x < board_size){
     board[x][y_val] = 1;
     x++;
  }

  // Top Left to Bottom Right
  x1 = x_val-1;
  y1 = y_val-1;

  x2 = x_val+1;
  y2 = y_val+1;
  // Top Right to Bottom Left
  x3 = x_val-1;
  y3 = y_val+1;

  x4 = x_val+1;
  y4 = y_val-1;
  bool finished = false;
  while(!finished){
    if((x1 > 0)&&(y1 > 0)){
      board[x1][y1] = 1;
      x1--;
      y1--;
    }
    if((x2 < board_size)&&(y2 < board_size)){
      board[x2][y2] = 1;
      x2++;
      y2++;
    }
    if((x3 > 0)&&(y3 < board_size)){
      board[x3][y3] = 1;
      x3--;
      y3++;
    }
    if((x4 < board_size)&&(y4 > 0)){
      board[x4][y4] = 1;
      x4++;
      y4--;
    }
  }
  // Bottom Left to Top Right
  //
  // create boolean
  //
  //

















    input.close(); //close input stream
    output.close(); // close output stream
}
