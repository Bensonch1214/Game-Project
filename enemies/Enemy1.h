#ifndef ENEMY1_H_INCLUDED
#define ENEMY1_H_INCLUDED

#include "Enemy.h"
#include "../data/DataCenter.h"
#include "../Level.h"

// fixed settings: MonsterCaveMan attributes
class Enemy1 : public Enemy
{
public:
	Enemy1(int start_x,int start_y,int _end_x,int _end_y,int _vx,int _vy) : Enemy{ EnemyType::ENEMY1,start_x,start_y,_end_x,_end_y,_vx,_vy} {
		HP = 100 + DataCenter::get_instance()->level->difficulty*3;
		v = 20;
		vy += DataCenter::get_instance()->level->difficulty;
		money = 10 + DataCenter::get_instance()->level->difficulty*2;
		exist_counter = 500;
		// bitmap_img_ids.emplace_back(std::vector<int>({0, 1, 2, 3})); // UP
		// bitmap_img_ids.emplace_back(std::vector<int>({0, 1, 2, 3})); // DOWN
		// bitmap_img_ids.emplace_back(std::vector<int>({0, 1, 2, 3})); // LEFT
		// bitmap_img_ids.emplace_back(std::vector<int>({0, 1, 2, 3})); // RIGHT
		// bitmap_switch_freq = 20;
	}
};

#endif
