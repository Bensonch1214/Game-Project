#include "DataCenter.h"
#include <cstring>
#include "../Level.h"
#include "../Player.h"
#include "../monsters/Monster.h"
#include"../enemies/Enemy.h"
#include"../enemies/Fire.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
/*-----I2P Revise start-----*/
#include "../Hero.h"
#include"../Light.h"
#include"../Bomb.h"
/*-----I2P Revise end-----*/

// fixed settings
namespace DataSetting
{
	constexpr double FPS = 60;
	constexpr int window_width = 1679; //1880
	constexpr int window_height = 1000;
	constexpr int game_field_length = 1679;
}

DataCenter::DataCenter()
{
	this->FPS = DataSetting::FPS;
	this->window_width = DataSetting::window_width;
	this->window_height = DataSetting::window_height;
	this->game_field_length = DataSetting::game_field_length;
	memset(key_state, false, sizeof(key_state));
	memset(prev_key_state, false, sizeof(prev_key_state));
	mouse = Point(0, 0);
	memset(mouse_state, false, sizeof(mouse_state));
	memset(prev_mouse_state, false, sizeof(prev_mouse_state));
	player = new Player();
	level = new Level();
	/*-----I2P Revise start-----*/
	hero = new Hero();
	/*-----I2P Revise end-----*/
}

DataCenter::~DataCenter()
{
	delete player;
	delete level;
	for (Monster *&m : monsters)
	{
		delete m;
	}
	for (Enemy *&e : enemies)
	{
		delete e;
	}
	for (Tower *&t : towers)
	{
		delete t;
	}
	for (Bullet *&b : towerBullets)
	{
		delete b;
	}
	for (Fire *&f : enemyFires)
	{
		delete f;
	}
	for (Light *&L : heroLights)
	{
		delete L;
	}
	for (Bomb *&b : heroBombs)
	{
		delete b;
	}
}