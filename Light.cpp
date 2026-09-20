#include "Light.h"
#include "data/DataCenter.h"
#include "data/ImageCenter.h"
#include "shapes/Circle.h"
#include "shapes/Point.h"
#include <algorithm>
#include <allegro5/bitmap_draw.h>
#include <allegro5/keycodes.h>

Light::Light(const Point &p, const std::string &path, double vx,double vy, int dmg, int type, double angel) {
	ImageCenter *IC = ImageCenter::get_instance();
	// this->fly_dist = fly_dist;
	this->dmg = dmg;
	bitmap = IC->get(path);
	double r = std::min(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap)) * 0.4;
	shape.reset(new Circle{p.x, p.y, r});
	// double d = Point::dist(p, target);
	// vx = (target.x - p.x) * v / d;
	// vy = (target.y - p.y) * v / d;
    this->vx=vx;
    this->vy=vy;
	this->type = type;
	this->angel = angel;
}

/**
 * @brief Update the Light position by its velocity and fly_dist by its movement per frame.
 * @details We don't detect whether to delete the Light itself here because deleting a object itself doesn't make any sense.
 */
void
Light::update() {
	// if(fly_dist == 0) return;
	DataCenter *DC = DataCenter::get_instance();
	double dx = vx / DC->FPS;
	double dy = vy / DC->FPS;
	if(type == ALLEGRO_KEY_LEFT)
	{
		dx *= cos(angel);
		dy *= sin(angel)*1.5;
		angel -= 0.01;
		if(angel<=-PI) angel = PI;
	}
	else if(type == ALLEGRO_KEY_RIGHT)
	{
		dx *= cos(angel);
		dy *= sin(angel)*1.5;
		angel += 0.01;
		if(angel>=PI) angel = -PI;
	}
	// double movement = Point::dist(Point{dx, dy}, Point{0, 0});
	// if(fly_dist > movement) {
	// 	shape->update_center_x(shape->center_x() + dx);
	// 	shape->update_center_y(shape->center_y() + dy);
	// 	fly_dist -= movement;
	// } else {
	// 	shape->update_center_x(shape->center_x() + dx * fly_dist / movement);
	// 	shape->update_center_y(shape->center_y() + dy * fly_dist / movement);
	// 	fly_dist = 0;
	// }
    shape->update_center_x(shape->center_x() + dx);
	shape->update_center_y(shape->center_y() + dy);
}

void
Light::draw() {
	al_draw_bitmap(
		bitmap,
		shape->center_x() - al_get_bitmap_width(bitmap) / 2,
		shape->center_y() - al_get_bitmap_height(bitmap) / 2, 0);
}
