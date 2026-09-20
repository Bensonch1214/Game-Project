#ifndef FIRE_H_INCLUDED
#define FIRE_H_INCLUDED

#include "../Object.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Point.h"
#include <vector>
#include <queue>
#include <allegro5/allegro_primitives.h>
// enum class Dir;

// fixed settings
enum class FireType {
	FIRETYPE_MIN,FIRE1, FIRE2, FIRE3, FIRE4, FIRE5, FIRETYPE_MAX
};

/**
 * @brief The class of a monster (enemies).
 * @details Monster inherits Object and takes Rectangle as its hit box.
 */
class Fire : public Object
{
public:
	static Fire *create_fire(FireType type,int x,int y,double vx,double vy,double angle,int dmg);
public:
	Fire(FireType type,int x,int y,double vx,double vy,double angle,int dmg);
	void update();
	void draw();
	const int &get_dmg() const { return dmg; }
	// const int &get_money() const { return money; }
	// int HP;
	// const std::queue<Point> &get_path() const { return path; }
    ALLEGRO_BITMAP *bitmap;

protected:
	/**
	 * @var HP
	 * @brief Health point of a monster.
	 **
	 * @var v
	 * @brief Moving speed of a monster.
	 **
	 * @var money
	 * @brief The amount of money that player will earn when the monster is killed.
	 **
	 * @var bitmap_img_ids
	 * @brief The first vector is the Dir index, and the second vector is image id.
	 * @details `bitmap_img_ids[Dir][<ordered_id>]`
	 **
	 * @var bitmap_switch_counter
	 * @brief Counting down for bitmap_switch_freq.
	 * @see Monster::bitmap_switch_freq
	 **
	 * @var bitmap_switch_freq
	 * @brief Number of frames required to change to the next move pose for the current facing direction.
	 * @details The variable is left for child classes to define.
	 * 
	 * @var bitmap_img_id
	 * @brief Move pose of the current facing direction.
	 **
	 * @var dir
	 * @brief Current facing direction.
	 **
	 * @var path
	 * @brief The walk path of a monster, represented in grid format.
	 * @see Level::grid_to_region(const Point &grid) const
	*/
	double vx,vy;
    int x,y;
    double angle;
    int dmg;
	double exist_counter;
	double ai,ri;
	bool trace;
	double dist;
    // ,end_x,end_y;
	// int money;
	// std::vector<std::vector<int>> bitmap_img_ids;
	// int bitmap_switch_counter;
	// int bitmap_switch_freq;
	// int bitmap_img_id;
private:
	FireType type;
	// Dir dir;
	// std::queue<Point> path;
};

#endif
