#pragma once

#include <SFML/Graphics.hpp>

#include <string>

namespace ApplesGame
{
	using namespace std::literals;
	const std::string RESOURCES_PATH	 = "Resources/"s;

	const int SCREEN_WIDTH				 = 800;
	const int SCREEN_HEIGHT				 = 600;
										 
	const float INITIAL_SPEED			 = 100.f; // pixel per second
	const float ACCELERATION			 = 20.f;
	const float PLAYER_SIZE				 = 20.f;
										 
	const int MIN_APPLES_FINITE			 = 15;
	const int MAX_APPLES_FINITE			 = 25;
	const int MIN_APPLES_INFINITE		 = 30;
	const int MAX_APPLES_INFINITE		 = 40;
	const float APPLE_SIZE				 = 20.f;
										 
	const int NUM_BARRIERS				 = 5;
	const float BARRIER_SIZE			 = 30.f;
										 
	const float PAUSE_TIME				 = 2.f;
										 
	const int FONT_SIZE					 = 28;
	const float MARGIN					 = 15.f;
										 
	// menu								 
	const int MENU_TITLE_SIZE			 = 24;
	const int MENU_ITEM_SIZE			 = 16;
	const float MENU_SPACING			 = 45.f;
	const float MENU_MARGIN_TOP			 = 100.f;
	const float MENU_ARROW_SIZE			 = 14.f;
	const float MENU_ARROW_GAP			 = 10.f;
	const int LEADERBOARD_INDEX			 = 4;

	// nameInput
	const int NAME_INPUT_TITLE_SIZE		 = 28;
	const int NAME_INPUT_TEXT_SIZE		 = 20;
	const int NAME_INPUT_MAX_NAME_LENGTH = 15;
	const std::string DEFAULT_NAME		 = "noname"s;

	// leaderBoard
	const int LD_TITLE_SIZE				 = 28;
	const int LD_HINT_SIZE				 = 14;
	const int LD_ENTRY_SIZE				 = 18;
	const int LD_EMPTY_SIZE				 = 20;
	
	const float LD_TITLE_Y				 = 60.f;
	const float LD_START_Y				 = 140.f;
	const float LD_ROW_SPACING			 = 40.f;
	const float LD_RANK_X				 = 100.f;
	const float LD_NAME_X				 = 200.f;
	const float LD_SCORE_X				 = 500.f;
	const float LD_HINT_Y_OFFSET		 = 50.f;

	const int MAX_RECORDS				 = 10;

	//
	const sf::Color textColor(255, 255, 255);
	const sf::Color hintColor(150, 150, 150);
	const sf::Color backgroundColor(20, 20, 40);
	const sf::Color normalColor(200, 200, 200);
	const sf::Color selectedColor(255, 255, 0);
	const sf::Color titleColor(255, 255, 255);

} // namespace ApplesGame