/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

const int BOARD_HEIGHT = 3; // Number of rows in the board
const int BOARD_WIDTH = 4;  // Number of columns in the board

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, check_board_initial_piece)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.pieceAt(0,0);
	ASSERT_EQ(cur, Blank);
}

TEST(PiezasTest, check_board_initial)
{
  Piezas piezas = Piezas();
  bool all_blank = true;
  for (int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      if(piezas.pieceAt(i,j) != Blank){
        all_blank = false;
      }
    }
  }
	ASSERT_TRUE(all_blank);
}

TEST(PiezasTest, check_board_reset)
{
  Piezas piezas = Piezas();
  piezas.reset();
  bool all_blank = true;
  for (int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      if(piezas.pieceAt(i,j) != Blank){
        all_blank = false;
      }
    }
  }
	ASSERT_TRUE(all_blank);
}

TEST(PiezasTest, check_board_row_negative)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.pieceAt(-1,0);
	ASSERT_EQ(cur, Invalid);
}

TEST(PiezasTest, check_board_col_negative)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.pieceAt(0,-1);
	ASSERT_EQ(cur, Invalid);
}

TEST(PiezasTest, check_board_row_out_of_bounds)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.pieceAt(3,0);
	ASSERT_EQ(cur, Invalid);
}

TEST(PiezasTest, check_board_col_out_of_bounds)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.pieceAt(0,4);
	ASSERT_EQ(cur, Invalid);
}

TEST(PiezasTest, check_drop_piece_col_negative)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.dropPiece(-1);
	ASSERT_EQ(cur, Invalid);
}

TEST(PiezasTest, check_drop_piece_out_of_bounds)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.dropPiece(4);
	ASSERT_EQ(cur, Invalid);
}

TEST(PiezasTest, check_drop_first_piece)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.dropPiece(0);
  ASSERT_EQ(cur, X);
}

TEST(PiezasTest, check_first_piece_at_after_drop)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.dropPiece(0);
  ASSERT_EQ(cur, piezas.pieceAt(0,0));
}

TEST(PiezasTest, check_drop_second_piece_same_col)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(0);
  Piece cur2 = piezas.dropPiece(0);
  ASSERT_EQ(cur1, X);
	ASSERT_EQ(cur2, O);
}

TEST(PiezasTest, check_second_piece_at_after_drop)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(0);
  Piece cur2 = piezas.dropPiece(0);
  ASSERT_EQ(cur1, piezas.pieceAt(0,0));
	ASSERT_EQ(cur2, piezas.pieceAt(1,0));
}

TEST(PiezasTest, check_drop_third_piece_player_X)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(0);
  Piece cur2 = piezas.dropPiece(0);
  Piece cur3 = piezas.dropPiece(0);
  ASSERT_NE(cur2, cur1);
	ASSERT_EQ(cur1, cur3);
}

TEST(PiezasTest, check_drop_third_piece_spot_matches)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(0);
  Piece cur2 = piezas.dropPiece(0);
  Piece cur3 = piezas.dropPiece(0);
  ASSERT_NE(cur2, cur1);
	ASSERT_EQ(cur3, piezas.pieceAt(2,0));
}

TEST(PiezasTest, check_drop_fourth_piece_same_col)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(0);
  Piece cur2 = piezas.dropPiece(0);
  Piece cur3 = piezas.dropPiece(0);
  Piece cur4 = piezas.dropPiece(0);
  ASSERT_EQ(cur1, cur3);
  ASSERT_EQ(cur2, O);
	ASSERT_EQ(cur4, Blank);
}

TEST(PiezasTest, check_game_not_over)
{
  Piezas piezas = Piezas();
  Piece cur = piezas.gameState();
  ASSERT_EQ(cur, Invalid);
}

// X O X O
// O X O X
// X O X O  *Tie, return Blank
TEST(PiezasTest, checkerboard_tie)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(0);
  Piece cur2 = piezas.dropPiece(0);
  Piece cur3 = piezas.dropPiece(0);
  Piece cur4 = piezas.dropPiece(1);
  Piece cur5 = piezas.dropPiece(1);
  Piece cur6 = piezas.dropPiece(1);
  Piece cur7 = piezas.dropPiece(2);
  Piece cur8 = piezas.dropPiece(2);
  Piece cur9 = piezas.dropPiece(2);
  Piece cur10 = piezas.dropPiece(3);
  Piece cur11 = piezas.dropPiece(3);
  Piece cur12 = piezas.dropPiece(3);
  Piece cur = piezas.gameState();
  ASSERT_EQ(cur, Blank);
}

// O X X X
// O O O O
// O X X X  *O wins (most in a row)
TEST(PiezasTest, checkerboard_O_wins_row)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(1);
  Piece cur2 = piezas.dropPiece(1);
  Piece cur3 = piezas.dropPiece(1);
  Piece cur4 = piezas.dropPiece(0);
  Piece cur5 = piezas.dropPiece(2);
  Piece cur6 = piezas.dropPiece(0);
  Piece cur7 = piezas.dropPiece(3);
  Piece cur8 = piezas.dropPiece(2);
  Piece cur9 = piezas.dropPiece(2);
  Piece cur10 = piezas.dropPiece(3);
  Piece cur11 = piezas.dropPiece(3);
  Piece cur12 = piezas.dropPiece(0);
  Piece cur = piezas.gameState();
  ASSERT_EQ(cur, O);
}

// O O X O
// O O O X
// X X X X  *X wins (most in a row)
TEST(PiezasTest, checkerboard_X_wins_row)
{
  Piezas piezas = Piezas();
  Piece cur1 = piezas.dropPiece(0);
  Piece cur2 = piezas.dropPiece(0);
  Piece cur3 = piezas.dropPiece(1);
  Piece cur4 = piezas.dropPiece(0);
  Piece cur5 = piezas.dropPiece(2);
  Piece cur6 = piezas.dropPiece(1);
  Piece cur7 = piezas.dropPiece(3);
  Piece cur8 = piezas.dropPiece(2);
  Piece cur9 = piezas.dropPiece(3);
  Piece cur10 = piezas.dropPiece(1);
  Piece cur11 = piezas.dropPiece(2);
  Piece cur12 = piezas.dropPiece(3);
  Piece cur = piezas.gameState();
  ASSERT_EQ(cur, X);
}
