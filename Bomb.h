#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include "Object.h"
#include <allegro5/bitmap.h>
#include <string>
#include"shapes/Point.h"
#include"Light.h"

#include <allegro5/keycodes.h>

/**
 * @brief The bullet shot from Tower.
 * @see Tower
 */
class Bomb : public Object
{
public:
	Bomb(const Point &p, const std::string &path, double vx,double vy, int dmg,double distance);
    // Bullet(const Point &p, const Point &target, const std::string &path, double v, int dmg, double fly_dist);
	void update();
	void draw();
    Light *create_light(double vx,double vy) {
		const Point &p = Point(shape->center_x(), shape->center_y());
		return new Light(p, "assets/image/light.png",vx, vy, 20, ALLEGRO_KEY_UP, 0); //if key up, then angel doesn't matter
	}
	// const double &get_fly_dist() const { return fly_dist; }
	const int &get_dmg() const { return dmg; }
	const double &get_distance() const{ return distance; }
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
    double distance;
	/**
	 * @brief ALLEGRO_BITMAP of the bullet.
	 */
	ALLEGRO_BITMAP *bitmap;
};

#endif
