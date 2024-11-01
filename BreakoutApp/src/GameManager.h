#pragma once

#include "GameData.h"

class GameManager {
public:

	// initializes all game objects
	bool loadObjects(GameObjects& gObjects);

	// updates all game objects
	void update(GameObjects& gObjects, GameState& gameState, PaddleMove& paddleMove, float timeStep);
};
