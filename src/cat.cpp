#include "cat.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


cat::cat(int WINDOW_WIDTH, int WINDOW_HEIGHT){
	if(!texture_Cat.loadFromFile("textures/Cat_Fighter/cat_texture.png"))
    	std::cout << "failed to load cat texture" << std::endl;
    if(!texture_dead.loadFromFile("textures/Cat_Fighter/dead.png"))
    	std::cout<<"failed to load cat dead texture" << std::endl;
    dead_sprite.setTexture(texture_dead);
    dead_sprite.setTextureRect(sf::IntRect(0,0,87,42));
    dead_sprite.setOrigin((dead_sprite.getTextureRect().width+1)/2,0);
    cat_sprite.setTexture(texture_Cat);
	cat_sprite.setTextureRect(sf::IntRect(0,0,texture_Cat.getSize().x/7,texture_Cat.getSize().y));
	cat_sprite.setPosition(sf::Vector2f( (float)WINDOW_WIDTH/2, ((float)5/6)*WINDOW_HEIGHT-cat_sprite.getTextureRect().height));
	dead_sprite.setPosition(cat_sprite.getPosition().x,(WINDOW_HEIGHT/2)-dead_sprite.getTextureRect().height);
	cat_sprite.setOrigin(cat_sprite.getTextureRect().width/2,0);
	punching_right=false;
	punching_left=false;
	turned = ::RIGHT; 
	src = 0;
}

