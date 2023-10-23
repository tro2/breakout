#include "pch.h"

#include "..\BreakoutApp\src\Utils.h"

// up down
TEST(CollisionTest, A_above_B) {
	MeshRect a = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(0.f, 0.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, false);
}

TEST(CollisionTest, B_above_A) {
	MeshRect a = MeshRect(Vec2d(0.f, -20.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, false);
}

TEST(CollisionTest, A_Int_B_above) {
	MeshRect a = MeshRect(Vec2d(0.f, 9.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(0.f, 0.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, true);
}

TEST(CollisionTest, B_int_A_above) {
	MeshRect a = MeshRect(Vec2d(0.f, -4.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(0.f, 5.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, true);
}


// left right
TEST(CollisionTest, A_left_B) {
	MeshRect a = MeshRect(Vec2d(5.f, 10.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(15.f, 10.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, false);
}

TEST(CollisionTest, B_left_A) {
	MeshRect a = MeshRect(Vec2d(15.f, 10.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(-15.f, 10.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, false);
}

TEST(CollisionTest, A_left_Int_B) {
	MeshRect a = MeshRect(Vec2d(-5.f, 10.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, true);
}

TEST(CollisionTest, B_left_int_A) {
	MeshRect a = MeshRect(Vec2d(5.f, 10.f), Vec2d(10.f, 10.f));
	MeshRect b = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));

	bool result = Utils::checkCollision(a, b);

	EXPECT_EQ(result, true);
}
