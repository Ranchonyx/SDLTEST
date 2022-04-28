#pragma once
#include "ECS.hpp"
#include "Vector2D.hpp"

class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D velocity;

	bool suppressLog = false;
	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() {
		position.x = 0;
		position.y = 0;
	}

	TransformComponent(int sc) {
		position.x = 0;
		position.y = 0;
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = h;
		scale = sc;
	}

	TransformComponent(float x, float y, int h, int w, int sc, bool sup) {
		position.x = x;
		position.y = y;
		height = h;
		width = h;
		scale = sc;
		suppressLog = sup;
	}

	int x() {
		return position.x;
	}

	int x(int x) {
		position.x = x;
	}
	
	int y() {
		return position.y;
	}

	int y(int y) {
		position.y = y;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	void logSelf() override {
		if(!suppressLog) {
			SDL_Log("Transform[X%f | Y%f][W%f | H%f][S%f]", position.x, position.y, height, width, scale);
		}
	}

	void setPos(int x, int y) {
		position.x = x;
		position.y = y;
	}

};