#include "pch.h"
#include "../Client/include/MainPlayer.h"

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")
#endif

// Dummy Test
TEST(PlayerClass, ValidatePlayer) {
	//MainPlayer o_MainPlayer("bbcorp");
	//MainPlayer o_mainPlayer("test_pseudo");
	//EXPECT_GT(o_mainPlayer.m_name.length(), 0);
	EXPECT_TRUE(true);
}
