/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

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

TEST(PiezasTest, check_board_constructor)
{
  Piezas piezas = new Piezas();
  bool all_blank = true;
  for(int i = 0; i < BOARD_HEIGHT; i++){
    for(int j = 0; j < BOARD_WIDTH; j++){
      if(board[i][j] != Blank){
        all_blank = false;
      }
    }
  }
	ASSERT_TRUE(all_blank);
}
