#include "monster.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture* monster::texture_Monster = new sf::Texture;

monster::monster(int dir,int WINDOW_WIDTH, int WINDOW_HEIGHT, int given_speed){
	//if(!texture_Monster.loadFromFile("../textures/Monster/monster.png"))
    //	std::cout << "failed to load monster texture" << std::endl;
	monster_sprite.setTexture(*texture_Monster);
    monster_sprite.setTextureRect(sf::IntRect(0,0,texture_Monster->getSize().x/5,texture_Monster->getSize().y));
    if(dir==RIGHT){
    	monster_sprite.setPosition(sf::Vector2f( 0, ((float)5/6)*WINDOW_HEIGHT - monster_sprite.getTextureRect().height)  );
    }
    else if(dir==LEFT){
    	dir=-1;
    	monster_sprite.scale(-1.f,1.f);
    	monster_sprite.setPosition(sf::Vector2f( WINDOW_WIDTH , ((float)5/6)*WINDOW_HEIGHT - monster_sprite.getTextureRect().height)  );
    }
    monster_sprite.setOrigin(monster_sprite.getTextureRect().width/2,0);
    walking_dir = dir;
    src=0;
    speed = given_speed;
}


