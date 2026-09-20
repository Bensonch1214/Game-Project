#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include"Light.h"
#include"Bomb.h"

enum class HeroState
{
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    HEROSTATE_MAX
};

class Hero : public Object
{

public:
    void init();
    void update();
    void draw();
    Light *create_light(int type, double angel, double vx, double vy) {
		const Point &p = Point(shape->center_x(), shape->center_y());
		return new Light(p, "assets/image/light.png", vx, vy, 20, type, angel);
	}
    Bomb *create_bomb() {
		const Point &pt = Point(shape->center_x(), shape->center_y());
		return new Bomb(pt, "assets/image/bomb.png",0, -300, 20, 180);
	}
    
	// const double attack_range() const { return 160; }
private:
    HeroState state = HeroState::FRONT; // the state of character
    double speed = 5;                   // the move speed of hero
    int width, height;                  // the width and height of the hero image
    std::map<HeroState, std::string> gifPath;
};
#endif