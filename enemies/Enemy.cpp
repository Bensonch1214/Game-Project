#include "Enemy.h"
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"Enemy4.h"
#include"Enemy5.h"
#include"fire.h"
#include "../data/DataCenter.h"
#include "../data/ImageCenter.h"
#include "../Level.h"
#include "../shapes/Point.h"
#include "../shapes/Rectangle.h"
#include "../Utils.h"
#include <allegro5/allegro_primitives.h>
#include<cmath>
#define PI acos(-1)
using namespace std;

// fixed settings
// enum class Dir {
// 	UP, DOWN, LEFT, RIGHT
// };
namespace EnemySetting {
	static constexpr char enemy_imgs_root_path[static_cast<int>(EnemyType::ENEMYTYPE_MAX)][40] = {
		"",
		"./assets/image/enemy/enemy1",
		"./assets/image/enemy/enemy2",
		"./assets/image/enemy/enemy3",
		"./assets/image/enemy/enemy4",
        "./assets/image/enemy/enemy5"
	};
}

/**
 * @brief Create a Monster* instance by the type.
 * @param type the type of a monster.
 * @param path walk path of the monster. The path should be represented in road grid format.
 * @return The curresponding Monster* instance.
 * @see Level::grid_to_region(const Point &grid) const
 */
Enemy *Enemy::create_enemy(EnemyType type,int start_x,int start_y,int _end_x,int _end_y,int _vx,int _vy) {
	switch(type) {
		case EnemyType::ENEMY1 :{
			return new Enemy1{start_x,start_y,_end_x,_end_y,_vx,_vy};
		}
		case EnemyType::ENEMY2: {
			return new Enemy2{start_x,start_y,_end_x,_end_y,_vx,_vy};
		}
		case EnemyType::ENEMY3: {
			return new Enemy3{start_x,start_y,_end_x,_end_y,_vx,_vy};
		}
		case EnemyType::ENEMY4: {
			return new Enemy4{start_x,start_y,_end_x,_end_y,_vx,_vy};
		}
        case EnemyType::ENEMY5: {
			return new Enemy5{start_x,start_y,_end_x,_end_y,_vx,_vy};
		}
		case EnemyType::ENEMYTYPE_MAX: {}
	}
	GAME_ASSERT(false, "enemy type error.");
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

Enemy::Enemy(EnemyType type,int start_x,int start_y,int _end_x,int _end_y,int _vx,int _vy):type{type},x{start_x},y{start_y},end_x{_end_x},end_y{_end_y},vx{_vx},vy{_vy} {
	DataCenter *DC = DataCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
	char buffer[50];
	sprintf(
		buffer, "%s.png",EnemySetting::enemy_imgs_root_path[static_cast<int>(type)]);
	bitmap = IC->get(buffer);
	shape.reset(new Rectangle{0, 0, 0, 0});

	// dir = Dir::RIGHT;
    shape->update_center_x(x);
    shape->update_center_y(y);
	counter=0;
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
Enemy::update() {
	DataCenter *DC = DataCenter::get_instance();
	ImageCenter *IC = ImageCenter::get_instance();
	// if(DC->enemyFires.empty())
	// debug_log("here\n");
	// printf("here\n");
	if(counter)counter--;
	else{
		if(type==EnemyType::ENEMY2){
			DC->enemyFires.emplace_back(Fire::create_fire(FireType::FIRE2,shape->center_x(),shape->center_y(),0,10+DC->level->difficulty*2,0,10));
		}
		else if(type==EnemyType::ENEMY3){
			for(int i=0;i<atk_num;i++){
				DC->enemyFires.emplace_back(Fire::create_fire(FireType::FIRE3,shape->center_x(),shape->center_y(),0,0,i*(2*PI/atk_num),15));
			}
			
		}
		else if(type==EnemyType::ENEMY4){
			DC->enemyFires.emplace_back(Fire::create_fire(FireType::FIRE4,shape->center_x(),shape->center_y(),0,20,0,20));
		}
		else if(type==EnemyType::ENEMY5){
			if(fire_angle<fire_density-1){
                fire_angle+= 1;
            }
            else{
                fire_angle=0;
            }
			for(int i=0;i<atk_num;i++){
				// printf("here\n");
				//調整參數，速度也會影響旋轉效果
				DC->enemyFires.emplace_back(Fire::create_fire(FireType::FIRE5,shape->center_x(),shape->center_y(),
				3*cos(i*(2*PI/atk_num)+3*fire_angle*(2*PI/(atk_num*fire_density))),
				3*sin(i*(2*PI/atk_num)+3*fire_angle*(2*PI/(atk_num*fire_density))),
				i*(2*PI/atk_num),25));
				
				// DC->enemyFires.emplace_back(Fire::create_fire(FireType::FIRE5,shape->center_x(),shape->center_y(),
				// 3*cos(i*(2*PI/atk_num)+3*fire_angle*(2*PI/(atk_num*fire_density))),
				// 3*sin(i*(2*PI/atk_num)+3*fire_angle*(2*PI/(atk_num*fire_density))),
				// i*(2*PI/atk_num),10));
			}
			
		}
		counter=atk_freq;
	}
	
	// After a period, the bitmap for this monster should switch from (i)-th image to (i+1)-th image to represent animation.
	// if(bitmap_switch_counter) --bitmap_switch_counter;
	// else {
	// 	bitmap_img_id = (bitmap_img_id + 1) % (bitmap_img_ids[static_cast<int>(dir)].size());
	// 	bitmap_switch_counter = bitmap_switch_freq;
	// }
	// v (velocity) divided by FPS is the actual moving pixels per frame.
	// double movement = v / DC->FPS;
	// Keep trying to move to next destination in "path" while "path" is not empty and we can still move.
	// while(!path.empty() && movement > 0) {
	// 	const Point &grid = this->path.front();
	// 	const Rectangle &region = DC->level->grid_to_region(grid);
	// 	const Point &next_goal = Point{region.center_x(), region.center_y()};

	// 	// Extract the next destination as "next_goal". If we want to reach next_goal, we need to move "d" pixels.
	// 	double d = Point::dist(Point{shape->center_x(), shape->center_y()}, next_goal);
	// 	Dir tmpdir;
	// 	if(d < movement) {
	// 		// If we can move more than "d" pixels in this frame, we can directly move onto next_goal and reduce "movement" by "d".
	// 		movement -= d;
	// 		tmpdir = convert_dir(Point{next_goal.x - shape->center_x(), next_goal.y - shape->center_y()});
	// 		shape.reset(new Rectangle{
	// 			next_goal.x, next_goal.y,
	// 			next_goal.x, next_goal.y
	// 	});
	// 		path.pop();
	// 	} else {
	// 		// Otherwise, we move exactly "movement" pixels.
	// 		double dx = (next_goal.x - shape->center_x()) / d * movement;
	// 		double dy = (next_goal.y - shape->center_y()) / d * movement;
	// 		tmpdir = convert_dir(Point{dx, dy});
	// 		shape->update_center_x(shape->center_x() + dx);
	// 		shape->update_center_y(shape->center_y() + dy);
	// 		movement = 0;
	// 	}
	// 	// Update facing direction.
	// 	dir = tmpdir;
	// }
	// Update real hit box for monster.
	// char buffer[50];
	// sprintf(
	// 	buffer, "%s/%s_%d.png",
	// 	MonsterSetting::monster_imgs_root_path[static_cast<int>(type)],
	// 	MonsterSetting::dir_path_prefix[static_cast<int>(dir)],
	// 	bitmap_img_ids[static_cast<int>(dir)][bitmap_img_id]);
	// ALLEGRO_BITMAP *bitmap = IC->get(buffer);

    // if(shape->center_y()<end_y)shape->update_center_y(shape->center_y()+vy);

	// if(exist_counter>0) exist_counter--;
	// else
	// {
	// 	shape->update_center_y(shape->center_y()-vy);
	// 	// exist_counter = 300;
	// 	printf("testtest!!!!!!!!!!!!!!!\n");
	// }

	if(type==EnemyType::ENEMY1)
	{
		shape->update_center_y(shape->center_y()+vy);	
	}
	else
	{
		if(exist_counter>0)
		{
			if(shape->center_y()<end_y)shape->update_center_y(shape->center_y()+vy);
			exist_counter--;
		}
		else
		{ //exist_counter <= 0
			shape->update_center_y(shape->center_y()-vy*2);
			// exist_counter = 300;
			printf("testtest!!!!!!!!!!!!!!!\n");
		}
	}

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
Enemy::draw() {
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
