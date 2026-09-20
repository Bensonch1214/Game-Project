#include "Fire.h"
#include "../data/DataCenter.h"
#include "../data/ImageCenter.h"
#include "../Level.h"
#include "../shapes/Point.h"
#include "../shapes/Circle.h"
#include "../Utils.h"
#include <allegro5/allegro_primitives.h>
#include<cmath>


using namespace std;

// fixed settings
// enum class Dir {
// 	UP, DOWN, LEFT, RIGHT
// };
namespace FireSetting {
	static constexpr char fire_imgs_root_path[static_cast<int>(FireType::FIRETYPE_MAX)][40] = {
		"",
		"",
		"./assets/image/fire/fire2",
		"./assets/image/fire/fire3",
		"./assets/image/fire/fire4",
        "./assets/image/fire/fire5"
	};
}

/**
 * @brief Create a Monster* instance by the type.
 * @param type the type of a monster.
 * @param path walk path of the monster. The path should be represented in road grid format.
 * @return The curresponding Monster* instance.
 * @see Level::grid_to_region(const Point &grid) const
 */
Fire *Fire::create_fire(FireType type,int x,int y,double vx,double vy,double angle,int dmg) {
    // printf("here\n");
    return new Fire{type,x,y,vx,vy,angle,dmg};
	// switch(type) {
	// 	case FireType::FIRE1 :{
	// 		// return new Fire1{start_x,start_y,_end_x,_end_y,_vx,_vy};
	// 	}
	// 	case FireType::FIRE2: {
	// 		return new Fire{type,x,y,vx,vy,angle,dmg};
	// 	}
	// 	case FireType::FIRE3: {
	// 		return new Fire3{start_x,start_y,_end_x,_end_y,_vx,_vy};
	// 	}
	// 	case FireType::FIRE4: {
	// 		return new Fire4{start_x,start_y,_end_x,_end_y,_vx,_vy};
	// 	}
    //     case FireType::FIRE5: {
	// 		return new Fire5{start_x,start_y,_end_x,_end_y,_vx,_vy};
	// 	}
	// 	case FireType::FIRETYPE_MAX: {}
	// }
	GAME_ASSERT(false, "fire type error.");
}

/**
 * @brief Given velocity of x and y direction, determine which direction the monster should face.
 */
// Dir convert_dir(const Point &v) {
// 	if(v.y < 0 && abs(v.y) >= abs(v.x))
// 		return Dir::UP;
// 	if(v.y > 0 && abs(v.y) >= abs(v.x))
// 		return Dir::DOWN;
// 	if(v.x < 0 && abs(v.x) >= abs(v.y))
// 		return Dir::LEFT;
// 	if(v.x > 0 && abs(v.x) >= abs(v.y))
// 		return Dir::RIGHT;
// 	return Dir::RIGHT;
// }

Fire::Fire(FireType type,int x,int y,double vx,double vy,double angle,int dmg):type{type},x{x},y{y},vx{vx},vy{vy},angle{angle},dmg{dmg} {
	DataCenter *DC = DataCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	char buffer[50];
	sprintf(
		buffer, "%s.png",FireSetting::fire_imgs_root_path[static_cast<int>(type)]);
	bitmap = IC->get(buffer);
    int r = std::min(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap)) * 0.4;
	shape.reset(new Circle{x, y, r});

	// dir = Dir::RIGHT;
    shape->update_center_x(x);
    shape->update_center_y(y);
	exist_counter=0;
	ai=1.35;
	ri=15;
	trace=true;
	// bitmap_img_id = 0;
	// bitmap_switch_counter = 0;
	// for(const Point &p : path)
	// 	this->path.push(p);
	// if(!path.empty()) {
	// 	const Point &grid = this->path.front();
	// 	const Rectangle &region = DC->level->grid_to_region(grid);
	// 	// Temporarily set the bounding box to the center (no area) since we haven't got the hit box of the monster.
	// 	shape.reset(new Rectangle{region.center_x(), region.center_y(), region.center_x(), region.center_y()});
	// 	this->path.pop();
	// }
}

/**
 * @details This update function updates the following things in order:
 * @details * Move pose of the current facing direction (bitmap_img_id).
 * @details * Current position (center of the hit box). The position is moved based on the center of the hit box (Rectangle). If the center of this monster reaches the center of the first point of path, the function will proceed to the next point of path.
 * @details * Update the real bounding box by the center of the hit box calculated as above.
 */
void
Fire::update() {
	DataCenter *DC = DataCenter::get_instance();
	// ImageCenter *IC = ImageCenter::get_instance();
    double dx = vx / DC->FPS;
	double dy = vy / DC->FPS;
	exist_counter+=1;
    switch(type){
        case FireType::FIRE2:
            // printf("here\n");
            shape->update_center_y(shape->center_y()+vy);break;
		case FireType::FIRE3:
			vx=ri*cos(ai*exist_counter/60+angle)-ai*ri*exist_counter/60*sin(ai*exist_counter/60+angle);
        	vy=ri*sin(ai*exist_counter/60+angle)+ai*ri*exist_counter/60*cos(ai*exist_counter/60+angle);
			shape->update_center_x(shape->center_x()+vx);
			shape->update_center_y(shape->center_y()+vy);
			break;
		case FireType::FIRE4:
			dist = sqrt((DC->mouse.x - shape->center_x())*(DC->mouse.x - shape->center_x()) + (DC->mouse.y - shape->center_y())*(DC->mouse.y - shape->center_y()));

			if(trace){
				vx = (DC->mouse.x - shape->center_x())*15 / dist;
				vy = (DC->mouse.y - shape->center_y())*15 / dist;
			}

			if(dist <= 210){
				trace = false;
			}
			shape->update_center_x(shape->center_x()+vx);
			shape->update_center_y(shape->center_y()+vy);
			break;
		case FireType::FIRE5:
			// vx *= 1.02;
			// vy *= 1.02;
			// if(vx<5 && vx>-5) vx *= 1.02;
			// if(vy<5 && vy>-5) vy *= 1.02;

			// printf("%lf %lf\n", vx, vy);
			
			
			shape->update_center_x(shape->center_x()+vx);
			shape->update_center_y(shape->center_y()+vy);
			break;

    }
    // if(shape->center_y()<end_y)
    
	const double &cx = shape->center_x();
	const double &cy = shape->center_y();
	// We set the hit box slightly smaller than the actual bounding box of the image because there are mostly empty spaces near the edge of a image.
	const int &h = al_get_bitmap_width(bitmap) * 0.8;
	const int &w = al_get_bitmap_height(bitmap) * 0.8;
	shape.reset(new Rectangle{
		(cx - w / 2.), (cy - h / 2.),
		(cx - w / 2. + w), (cy - h / 2. + h)
	});
}

void
Fire::draw() {
	// ImageCenter *IC = ImageCenter::get_instance();
	// char buffer[50];
	// sprintf(
	// 	buffer, "%s/%s_%d.png",
	// 	MonsterSetting::monster_imgs_root_path[static_cast<int>(type)],
	// 	MonsterSetting::dir_path_prefix[static_cast<int>(dir)],
	// 	bitmap_img_ids[static_cast<int>(dir)][bitmap_img_id]);
	// ALLEGRO_BITMAP *bitmap = IC->get(buffer);
	al_draw_bitmap(
		bitmap,
		shape->center_x() - al_get_bitmap_width(bitmap) / 2,
		shape->center_y() - al_get_bitmap_height(bitmap) / 2, 0);
}
