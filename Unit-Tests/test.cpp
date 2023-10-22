#include "pch.h"

#include "..\BreakoutApp\src\Utils.h"

TEST(CollisionTest, A_B_Separate_Y) {
	MeshRect a = MeshRect(Vec2d(10.f, 10.f), Vec2d(0.f, 106.f));
	MeshRect b = MeshRect(Vec2d(100.f, 10.f), Vec2d(0.f, 95.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, false);
}
