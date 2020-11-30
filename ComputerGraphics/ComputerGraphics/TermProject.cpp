#include "stdafx.h"
#include "TermProject.h"
#include "Object.h"
#include "Ball.h"
#include "Rigidbody.h"
#include "Tile.h"

TermProject::TermProject()
{
}

Object* InstantiateBall()
{
	auto ball = new Object("Ball");
	ball->AddComponent<Ball>();
	ball->AddComponent<Rigidbody>();

	return ball;
}

Object* InstantiateBlackTile()
{
	auto tile = new Object();
	auto tileTile = tile->AddComponent<Tile>();

	tileTile

	return tile;
}
