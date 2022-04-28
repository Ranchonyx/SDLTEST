#include "Collision.hpp"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {

	if (
		//Prüfen, ob sich vertikale und horizontale Achsen beider Rechtecke schneiden
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		) {
		//Kollision
		return true;
	}
		//Keine Kollision
		return false;
}