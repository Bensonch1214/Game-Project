#include "Level.h"
#include <string>
#include "Utils.h"
#include "monsters/Monster.h"
#include"enemies/Enemy.h"
#include "data/DataCenter.h"
#include <allegro5/allegro_primitives.h>
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <array>

using namespace std;

// fixed settings
namespace LevelSetting {
	constexpr char level_path_format[] = "./assets/level/LEVEL%d.txt";
	constexpr char level_format[] = "./assets/my_level/level%d.txt";
	//! @brief Grid size for each level.
	constexpr array<int, 4> grid_size = {
		40, 40, 40, 40
	};
	constexpr int monster_spawn_rate = 90;
	constexpr int enemy_spawn_rate = 500;
};

void
Level::init() {
	level = -1;
	grid_w = -1;
	grid_h = -1;
	monster_spawn_counter = 0;
	enemy_spawn_counter=0;
	difficulty = 2;
}

/**
 * @brief Loads level data from input file. The input file is required to follow the format.
 * @param lvl level index. The path format is a fixed setting in code.
 * @details The content of the input file should be formatted as follows:
 *          * Total number of monsters.
 *          * Number of each different number of monsters. The order and number follows the definition of MonsterType.
 *          * Indefinite number of Point (x, y), represented in grid format.
 * @see level_path_format
 * @see MonsterType
 */
void
Level::load_level(int lvl) {
	DataCenter *DC = DataCenter::get_instance();

	char buffer[50];
	sprintf(buffer, LevelSetting::level_path_format, lvl);
	FILE *f = fopen(buffer, "r");
	GAME_ASSERT(f != nullptr, "cannot find level.");
	level = lvl;
	grid_w = DC->game_field_length / LevelSetting::grid_size[lvl];
	grid_h = DC->game_field_length / LevelSetting::grid_size[lvl];
	num_of_monsters.clear();
	road_path.clear();

	int num;
	// read total number of monsters & number of each monsters
	fscanf(f, "%d", &num);
	for(size_t i = 0; i < static_cast<size_t>(MonsterType::MONSTERTYPE_MAX); ++i) {
		fscanf(f, "%d", &num);
		num_of_monsters.emplace_back(num);
	}

	// read road path
	while(fscanf(f, "%d", &num) != EOF) {
		int w = num % grid_w;
		int h = num / grid_h;
		road_path.emplace_back(w, h);
	}

	char buf[50];
	sprintf(buf, LevelSetting::level_format, lvl);


	
	FILE *lf = fopen(buf, "r");
	GAME_ASSERT(lf != nullptr, "cannot find level.");
	level = lvl;
	// grid_w = DC->game_field_length / LevelSetting::grid_size[lvl];
	// grid_h = DC->game_field_length / LevelSetting::grid_size[lvl];
	times_of_enemies.clear();
	info_of_enemies.clear();
	// road_path.clear();

	int t,n,type,vx,vy;
	double sx,sy,ex,ey;
	// read total number of monsters & number of each monsters
	fscanf(lf, "%d", &t);
	for(size_t i = 0; i < t; ++i) {
		fscanf(lf, "%d", &n);
		times_of_enemies.emplace_back(n);
		for(size_t j=0;j<n;j++){
			fscanf(lf, "%d%lf%lf%lf%lf%d%d", &type,&sx,&sy,&ex,&ey,&vx,&vy);
			info_of_enemies.emplace_back(type,sx,sy,ex,ey,vx,vy);
		}
	}
	fclose(lf);
	debug_log("<Level> load level %d.\n", lvl);
	
}

/**
 * @brief Updates monster_spawn_counter and create monster if needed.
*/
void
Level::update() {
	// if(monster_spawn_counter) {
	// 	monster_spawn_counter--;
	// 	return;
	// }
	// DataCenter *DC = DataCenter::get_instance();
	// // DC->enemies.emplace_back(Enemy::create_enemy(EnemyType::ENEMY1,0,0,0,0));
	// for(size_t i = 0; i < num_of_monsters.size(); ++i) {
	// 	if(num_of_monsters[i] == 0) continue;
	// 	DC->monsters.emplace_back(Monster::create_monster(static_cast<MonsterType>(i), DC->level->get_road_path()));
	// 	num_of_monsters[i]--;
	// 	break;
	// }
	// monster_spawn_counter = LevelSetting::monster_spawn_rate;

	if(enemy_spawn_counter) {
		enemy_spawn_counter--;
		return;
	}
	DataCenter *DC = DataCenter::get_instance();
	
	// if(!times_of_enemies.empty()){
	// 	int n=times_of_enemies.front();
	// 	times_of_enemies.erase(times_of_enemies.begin());
	// 	for(size_t i = 0; i < n; ++i) {
	// 		auto [type,sx,sy,ex,ey,vx,vy]=info_of_enemies.front();
	// 		DC->enemies.emplace_back(Enemy::create_enemy(static_cast<EnemyType>(type),static_cast<int>(DC->game_field_length*sx),static_cast<int>(DC->window_height*sy),static_cast<int>(DC->game_field_length*ex),static_cast<int>(DC->window_height*ey),vx,vy));
	// 		if(!info_of_enemies.empty())
	// 			info_of_enemies.erase(info_of_enemies.begin());
	// 	}
	// }

	if(!times_of_enemies.empty()){
		int n=times_of_enemies.front();
		times_of_enemies.erase(times_of_enemies.begin());

		times_of_enemies.push_back(n);

		for(size_t i = 0; i < n; ++i) {
			auto [type,sx,sy,ex,ey,vx,vy]=info_of_enemies.front(); //push_back

			DC->enemies.emplace_back(Enemy::create_enemy(static_cast<EnemyType>(type),static_cast<int>(DC->game_field_length*sx),static_cast<int>(DC->window_height*sy),static_cast<int>(DC->game_field_length*ex),static_cast<int>(DC->window_height*ey),vx,vy));
			if(!info_of_enemies.empty())
			{
				info_of_enemies.erase(info_of_enemies.begin());
				info_of_enemies.emplace_back(type,sx,sy,ex,ey,vx,vy);
			}
		}
	}
	
	enemy_spawn_counter = LevelSetting::enemy_spawn_rate;

	difficulty++;
}

void
Level::draw() {
	if(level == -1) return;
	// for(auto &[i, j] : road_path) {
	// 	int x1 = i * LevelSetting::grid_size[level];
	// 	int y1 = j * LevelSetting::grid_size[level];
	// 	int x2 = x1 + LevelSetting::grid_size[level];
	// 	int y2 = y1 + LevelSetting::grid_size[level];
	// 	al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 244, 173));
	// }
}

bool
Level::is_onroad(const Rectangle &region) {
	for(const Point &grid : road_path) {
		if(grid_to_region(grid).overlap(region))
			return true;
	}
	return false;
}

Rectangle
Level::grid_to_region(const Point &grid) const {
	int x1 = grid.x * LevelSetting::grid_size[level];
	int y1 = grid.y * LevelSetting::grid_size[level];
	int x2 = x1 + LevelSetting::grid_size[level];
	int y2 = y1 + LevelSetting::grid_size[level];
	return Rectangle{x1, y1, x2, y2};
}
