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
