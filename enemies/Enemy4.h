#ifndef ENEMY4_H_INCLUDED
#define ENEMY4_H_INCLUDED

#include "Enemy.h"

// fixed settings: MonsterCaveMan attributes
class Enemy4 : public Enemy
{
public:
	Enemy4(int start_x,int start_y,int _end_x,int _end_y,int _vx,int _vy) : Enemy{ EnemyType::ENEMY4,start_x,start_y,_end_x,_end_y,_vx,_vy} {
		HP = 400 + DataCenter::get_instance()->level->difficulty*3;
		atk_freq=30;
		atk_num=0;
		v = 40;
		money = 10 + DataCenter::get_instance()->level->difficulty*2;
		exist_counter = 500;


		// bitmap_img_ids.emplace_back(std::vector<int>({0, 4, 2, 3})); // UP
		// bitmap_img_ids.emplace_back(std::vector<int>({0, 4, 2, 3})); // DOWN
		// bitmap_img_ids.emplace_back(std::vector<int>({0, 4, 2, 3})); // LEFT
		// bitmap_img_ids.emplace_back(std::vector<int>({0, 4, 2, 3})); // RIGHT
		// bitmap_switch_freq = 20;
	}
};

#endif
