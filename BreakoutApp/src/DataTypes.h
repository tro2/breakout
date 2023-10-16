#pragma once

struct Vec2d {

    double x;
    double y;

};

struct Vec2i {

    int x;
    int y;

};

struct MeshRect {

    Vec2d position;
    Vec2d size;

};

enum GameState
{
    READY,
    IN_GAME,
    VICTORY,
};
