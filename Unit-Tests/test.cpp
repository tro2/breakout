#include "pch.h"

#include "..\BreakoutApp\src\Physics.h"
#include "..\BreakoutApp\src\GameData.h"

namespace resolveCollision
{
	TEST(resolveElasticCollisions, ball_into_wall_from_left)
	{
		// tests whether ball hitting wall from the left will bounce off to the right
		MoveableMRect ball = MoveableMRect(MeshRect(Vec2d(5.f, 0.f), Vec2d(10.f, 10.f)), Vec2d(-1.f, 0.f), 1.f);

		std::list<MeshRect> obstacles;
		std::forward_list<MeshRect*> walls;
		walls.push_front(new MeshRect(Vec2d(0.f, 0.f), Vec2d(10.f, 10.f)));

		Physics::moveElasticBounce(ball, obstacles, walls, MoveableMRect(), 1.f);

		EXPECT_EQ(ball.velocity.x, 1.f);
		EXPECT_EQ(ball.velocity.y, 0.f);
	}

	TEST(resolveElasticCollisions, ball_into_wall_from_right)
	{
		// tests whether ball hitting wall from the right will bounce off to the left
		MoveableMRect ball = MoveableMRect(MeshRect(Vec2d(-5.f, 0.f), Vec2d(10.f, 10.f)), Vec2d(1.f, 0.f), 1.f);

		std::list<MeshRect> obstacles;
		std::forward_list<MeshRect*> walls;
		walls.push_front(new MeshRect(Vec2d(0.f, 0.f), Vec2d(10.f, 10.f)));

		Physics::moveElasticBounce(ball, obstacles, walls, MoveableMRect(), 1.f);

		EXPECT_EQ(ball.velocity.x, -1.f);
		EXPECT_EQ(ball.velocity.y, 0.f);
	}
}
namespace checkCollision
{
	TEST(CollisionTest, A_above_B) {
		MeshRect a = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(0.f, 0.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, false);
	}

	TEST(CollisionTest, B_above_A) {
		MeshRect a = MeshRect(Vec2d(0.f, -20.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, false);
	}

	TEST(CollisionTest, A_Int_B_above) {
		MeshRect a = MeshRect(Vec2d(0.f, 9.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(0.f, 0.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, true);
	}

	TEST(CollisionTest, B_int_A_above) {
		MeshRect a = MeshRect(Vec2d(0.f, -4.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(0.f, 5.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, true);
	}


	// left right
	TEST(CollisionTest, A_left_B) {
		MeshRect a = MeshRect(Vec2d(5.f, 10.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(15.f, 10.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, false);
	}

	TEST(CollisionTest, B_left_A) {
		MeshRect a = MeshRect(Vec2d(15.f, 10.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(-15.f, 10.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, false);
	}

	TEST(CollisionTest, A_left_Int_B) {
		MeshRect a = MeshRect(Vec2d(-5.f, 10.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, true);
	}

	TEST(CollisionTest, B_left_int_A) {
		MeshRect a = MeshRect(Vec2d(5.f, 10.f), Vec2d(10.f, 10.f));
		MeshRect b = MeshRect(Vec2d(0.f, 10.f), Vec2d(10.f, 10.f));

		bool result = Physics::checkCollision(a, b);

		EXPECT_EQ(result, true);
	}
}
