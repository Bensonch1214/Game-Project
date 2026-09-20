#include "OperationCenter.h"
#include "DataCenter.h"
#include "../monsters/Monster.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
#include "../Player.h"
/*-----I2P Revise start-----*/
#include "../Hero.h"
#include"../Light.h"
#include"../Bomb.h"
#include"../enemies/Enemy.h"
#include"../enemies/Fire.h"

#include <allegro5/bitmap_draw.h>

/*-----I2P Revise end-----*/

void OperationCenter::update()
{
	// Update monsters.
	_update_monster();
	_update_enemy();
	// Update towers.
	_update_tower();
	// Update tower bullets.
	_update_towerBullet();
	_update_enemyFire();
	_update_heroLight();
	_update_heroBomb();
	// If any bullet overlaps with any monster, we delete the bullet, reduce the HP of the monster, and delete the monster if necessary.
	_update_monster_towerBullet();
	_update_enemy_heroLight();
	_update_enemyFire_hero();
	_update_enemy_hero();
	// If any monster reaches the end, hurt the player and delete the monster.
	_update_monster_player();
	_update_enemy_player();
	/*-----I2P Revise start-----*/
	_update_monster_hero();
	/*-----I2P Revise end-----*/
}

void OperationCenter::_update_monster()
{
	std::vector<Monster *> &monsters = DataCenter::get_instance()->monsters;
	for (Monster *monster : monsters)
		monster->update();
}
void OperationCenter::_update_enemy(){
	std::vector<Enemy *> &enemies = DataCenter::get_instance()->enemies;
	DataCenter *DC = DataCenter::get_instance();
	for (Enemy *enemy : enemies)
	{
		enemy->update();
	}

	for (size_t i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i]->shape->center_y() < -DC->window_height*1 || enemies[i]->shape->center_y() > DC->window_height+100)
		{
			enemies.erase(enemies.begin() + i);
			--i;
		}
	}
}
void OperationCenter::_update_tower()
{
	std::vector<Tower *> &towers = DataCenter::get_instance()->towers;
	for (Tower *tower : towers)
		tower->update();
}

void OperationCenter::_update_towerBullet()
{
	std::vector<Bullet *> &towerBullets = DataCenter::get_instance()->towerBullets;
	for (Bullet *towerBullet : towerBullets)
		towerBullet->update();
	// Detect if a bullet flies too far (exceeds its fly distance limit), which means the bullet lifecycle has ended.
	for (size_t i = 0; i < towerBullets.size(); ++i)
	{
		if (towerBullets[i]->get_fly_dist() <= 0)
		{
			towerBullets.erase(towerBullets.begin() + i);
			--i;
		}
	}
}
void OperationCenter::_update_enemyFire(){
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Fire *> &enemyFires = DC->enemyFires;
	for (Fire *enemyFire : enemyFires)
		enemyFire->update();
	// Detect if a bullet flies too far (exceeds its fly distance limit), which means the bullet lifecycle has ended.
	for (size_t i = 0; i < enemyFires.size(); ++i)
	{
		if (enemyFires[i]->shape->center_x()<0||enemyFires[i]->shape->center_x()>DC->game_field_length - al_get_bitmap_width(enemyFires[i]->bitmap)/2 || enemyFires[i]->shape->center_y()<0||enemyFires[i]->shape->center_y()>DC->window_height)
		{
			enemyFires.erase(enemyFires.begin() + i);
			--i;
		}
	}
}
void OperationCenter::_update_heroLight(){
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Light *> &heroLights = DC->heroLights;
	for (Light *heroLight : heroLights)
		heroLight->update();
	for (size_t i = 0; i < heroLights.size(); ++i)
	{
		if (heroLights[i]->shape->center_x()<0 || heroLights[i]->shape->center_x()>DC->game_field_length-al_get_bitmap_width(heroLights[i]->bitmap)/5 || heroLights[i]->shape->center_y()<0||heroLights[i]->shape->center_y()>DC->window_height)
		{
			heroLights.erase(heroLights.begin() + i);
			--i;
		}
	}
}
void OperationCenter::_update_heroBomb(){
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Bomb *> &heroBombs = DC->heroBombs;
	for (Bomb *heroBomb : heroBombs)
		heroBomb->update();
	for (size_t i = 0; i < heroBombs.size(); ++i)
	{
		if (heroBombs[i]->shape->center_x()<0||heroBombs[i]->shape->center_x()>DC->window_width||heroBombs[i]->shape->center_y()<0||heroBombs[i]->shape->center_y()>DC->window_height||heroBombs[i]->get_distance()<0)
		{
			heroBombs.erase(heroBombs.begin() + i);
			--i;
		}
	}
}
void OperationCenter::_update_monster_towerBullet()
{
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Monster *> &monsters = DC->monsters;
	std::vector<Bullet *> &towerBullets = DC->towerBullets;
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		for (size_t j = 0; j < towerBullets.size(); ++j)
		{
			// Check if the bullet overlaps with the monster.
			if (monsters[i]->shape->overlap(*(towerBullets[j]->shape)))
			{
				// Reduce the HP of the monster. Delete the bullet.
				monsters[i]->HP -= towerBullets[j]->get_dmg();
				towerBullets.erase(towerBullets.begin() + j);
				--j;
			}
		}
	}
}
void OperationCenter::_update_enemy_heroLight()
{
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Enemy *> &enemies = DC->enemies;
	std::vector<Light *> &heroLights = DC->heroLights;
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		for (size_t j = 0; j < heroLights.size(); ++j)
		{
			// Check if the bullet overlaps with the monster.
			if (enemies[i]->shape->overlap(*(heroLights[j]->shape)))
			{
				// Reduce the HP of the monster. Delete the bullet.
				enemies[i]->HP -= heroLights[j]->get_dmg();
				heroLights.erase(heroLights.begin() + j);
				--j;
			}
		}
	}
}

void OperationCenter::_update_monster_player()
{
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Monster *> &monsters = DC->monsters;
	Player *&player = DC->player;
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		// Check if the monster is killed.
		if (monsters[i]->HP <= 0)
		{
			// Monster gets killed. Player receives money.
			player->coin += monsters[i]->get_money();
			monsters.erase(monsters.begin() + i);
			--i;
			// Since the current monsster is killed, we can directly proceed to next monster.
			break;
		}
		// Check if the monster reaches the end.
		if (monsters[i]->get_path().empty())
		{
			monsters.erase(monsters.begin() + i);
			player->HP--;
			--i;
		}
	}
}
void OperationCenter::_update_enemyFire_hero(){
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Fire *> &enemyFires = DC->enemyFires;
	Player *&player = DC->player;

	for (size_t i = 0; i < enemyFires.size(); ++i)
	{
		// Check if the monster is killed.
		if (enemyFires[i]->shape->overlap(*(DC->hero->shape)))
			{
				// Reduce the HP of the monster. Delete the bullet.
				if(!DC->player->super) DC->player->HP -= enemyFires[i]->get_dmg();
				enemyFires.erase(enemyFires.begin() + i);
				--i;
			}
	}
}
void OperationCenter::_update_enemy_hero(){
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Enemy *> &enemies = DC->enemies;
	Player *&player = DC->player;
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		// Check if the monster is killed.
		if (enemies[i]->shape->overlap(*(DC->hero->shape)))
			{
				// Reduce the HP of the monster. Delete the bullet.
				if(!DC->player->super) DC->player->HP -= 10;
				// enemies.erase(enemies.begin() + i);
				// --i;
				enemies[i]->HP = 0;
			}
	}
}
void OperationCenter::_update_enemy_player()
{
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Enemy *> &enemies = DC->enemies;
	Player *&player = DC->player;
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		// Check if the monster is killed.
		if (enemies[i]->HP <= 0)
		{
			// Monster gets killed. Player receives money.
			player->coin += enemies[i]->get_money();
			player->score += enemies[i]->get_money();
			enemies.erase(enemies.begin() + i);
			--i;
			// Since the current monsster is killed, we can directly proceed to next monster.
			break;
		}
		// Check if the monster reaches the end.
	}
}
/*-----I2P Revise start-----*/
void OperationCenter::_update_monster_hero()
{
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Monster *> &monsters = DC->monsters;
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		if (monsters[i]->shape->overlap(*(DC->hero->shape)))
		{
			monsters[i]->HP = 0;
		}
	}
}
/*-----I2P Revise end-----*/

void OperationCenter::draw()
{
	_draw_monster();
	_draw_enemy();
	_draw_tower();
	_draw_towerBullet();
	_draw_enemyFire();
	_draw_heroLight();
	_draw_heroBomb();
}

void OperationCenter::_draw_monster()
{
	std::vector<Monster *> &monsters = DataCenter::get_instance()->monsters;
	for (Monster *monster : monsters)
		monster->draw();
}
void OperationCenter::_draw_enemy()
{
	std::vector<Enemy *> &enemies = DataCenter::get_instance()->enemies;
	for (Enemy *enemy : enemies)
		enemy->draw();
}
void OperationCenter::_draw_tower()
{
	std::vector<Tower *> &towers = DataCenter::get_instance()->towers;
	for (Tower *tower : towers)
		tower->draw();
}

void OperationCenter::_draw_towerBullet()
{
	std::vector<Bullet *> &towerBullets = DataCenter::get_instance()->towerBullets;
	for (Bullet *towerBullet : towerBullets)
		towerBullet->draw();
}
void OperationCenter::_draw_enemyFire()
{
	std::vector<Fire *> &enemyFires = DataCenter::get_instance()->enemyFires;
	for (Fire *enemyFire : enemyFires)
		enemyFire->draw();
}
void OperationCenter::_draw_heroLight()
{
	std::vector<Light *> &heroLights = DataCenter::get_instance()->heroLights;
	for (Light *heroLight : heroLights)
		heroLight->draw();
}
void OperationCenter::_draw_heroBomb()
{
	std::vector<Bomb *> &heroBombs = DataCenter::get_instance()->heroBombs;
	for (Bomb *heroBomb : heroBombs)
		heroBomb->draw();
}