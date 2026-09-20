#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "Object.h"
#include <allegro5/bitmap.h>
#include <string>
#include"shapes/Point.h"


#include <cmath>
const double PI = acos(-1);
/**
 * @brief The bullet shot from Tower.
 * @see Tower
 */
class Light : public Object
{
public:
	Light(const Point &p, const std::string &path, double vx,double vy, int dmg, int type, double angel);
    // Bullet(const Point &p, const Point &target, const std::string &path, double v, int dmg, double fly_dist);
	void update();
	void draw();
	// const double &get_fly_dist() const { return fly_dist; }
	const int &get_dmg() const { return dmg; }

	ALLEGRO_BITMAP *bitmap;

private:
	/**
	 * @brief Velocity in x direction.
	 */
	double vx;
	/**
	 * @brief Velocity in y direction.
	 */
	double vy;
	/**
	 * @brief Flying distance limit of the bullet. If the flying distance exceeds the limit, the bullet should be erased.
	 */
	// double fly_dist;
	/**
	 * @brief Base damage of the bullet when hit anything.
	 */
	int dmg;
	/**
	 * @brief ALLEGRO_BITMAP of the bullet.
	 */

	/**
	 * @brief
	 * type or direction
	 */
	int type;
	double angel;
};

#endif
