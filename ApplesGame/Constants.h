#pragma once

#include <string>

namespace ApplesGame
{

	const std::string RESOURCES_PATH = "Resources/";

	const int SCREEN_WIDTH			 = 800;
	const int SCREEN_HEIGHT			 = 600;

	const float INITIAL_SPEED		 = 100.f; // pixel per second
	const float ACCELERATION		 = 20.f;
	const float PLAYER_SIZE			 = 20.f;

	const int NUM_APPLES			 = 20;
	const float APPLE_SIZE			 = 20.f;

	const int NUM_BARRIERS			 = 5;
	const float BARRIER_SIZE		 = 30.f;

	const float PAUSE_TIME			 = 2.f;

	const float FONT_SIZE			 = 28.f;
	const float MARGIN				 = 15.f;

} // namespace ApplesGame