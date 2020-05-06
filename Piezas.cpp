#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/

const int BOARD_HEIGHT = 3; // Number of rows in the board
const int BOARD_WIDTH = 4;  // Number of columns in the board

/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  board.resize(BOARD_HEIGHT);
  for (int i = 0; i < BOARD_HEIGHT; i++){
    board[i].resize(BOARD_WIDTH);
  }
  for (int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      board[i][j] = Blank;
    }
  }
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  Piece current = Blank;
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      board[i][j] = current;
    }
  }
  turn = X;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
  Piece cur;
  // If out of bounds, return Invalid value for the Piece
  if(column < 0 || column >= 4){
    cur = Invalid;
  }
  else{
    // Go through the rows in the chosen column.
    // If a blank space is located, the player with current turn gets that spot
    // If none of the spaces in that row are Blank, current player loses turn
    bool located = false;
    int row = 0;
    while(!located && row < BOARD_HEIGHT){
      cur = pieceAt(row, column);
      if(cur == Blank){
        board[row][column] = turn;
        cur = turn;
        located = true;
      }
      else{
        row++;
      }
    }
    if(row == BOARD_HEIGHT){
      cur = Blank;
    }
  }

  // If it was X's turn, now it's O's turn, and vice versa
  turn == X ? turn = O : turn = X;
  return cur;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  if(row < 0 || row >= 3 || column < 0 || column >= 4){
    return Invalid;
  }
  return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  // Check for Row winner
  // If any spots are blank, no need to continue (game is not over)
  int x_row_max = 0;
  int o_row_max = 0;
  for(int i = 0; i < BOARD_HEIGHT; i++){
    int x_cur = 0;
    int o_cur = 0;
    for(int j = 0; j < BOARD_WIDTH; j++){
      if(board[i][j] == Blank){
        return Invalid;
      }
      else if(board[i][j] == X){
        if(j == 0 || board[i][j-1] == X){
          x_cur++;
        }
        else{
          x_cur = 1;
        }
        // set current max for x
        if(x_cur > x_row_max){
          x_row_max = x_cur;
        }
      }
      else{  // is space on board is not blank and not X, space is O
        if(j == 0 || board[i][j-1] == O){
          o_cur++;
        }
        else{
          o_cur = 1;
        }
        // set current max for o
        if(o_cur > o_row_max){
          o_row_max = o_cur;
        }
      }
    }
  }

  // Check for Column Winner
  int x_col_max = 0;
  int o_col_max = 0;
  for(int j = 0; j < BOARD_WIDTH; j++){
    int x_cur = 0;
    int o_cur = 0;
    for(int i = 0; i < BOARD_HEIGHT; i++){
      if(board[i][j] == X){
        if(i == 0 || board[i-1][j] == X){
          x_cur++;
        }
        else{
          x_cur = 1;
        }
        // set current max for x
        if(x_cur > x_col_max){
          x_col_max = x_cur;
        }
      }
      else{  // is space on board is not blank and not X, space is O
        if(i == 0 || board[i-1][j] == O){
          o_cur++;
        }
        else{
          o_cur = 1;
        }
        // set current max for o
        if(o_cur > o_col_max){
          o_col_max = o_cur;
        }
      }
    }
  }

  // Get best score overall for Xs and Os
  int best_x;
  if(x_row_max > x_col_max){
    best_x = x_row_max;
  }
  else{
    best_x = x_col_max;
  }
  int best_o;
  if(o_row_max > o_col_max){
    best_o = o_row_max;
  }
  else{
    best_o = o_col_max;
  }

  // Return Overall Winner (or tie)
  if(best_x > best_o){
    return X;
  }
  else if(best_o > best_x){
    return O;
  }
  else{
    return Blank;
  }
}
