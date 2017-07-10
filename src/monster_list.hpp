#ifndef MONSTER_LIST
#define MONSTER_LIST
#include "node.hpp"
#include <SFML/Graphics.hpp>
class monster_list{
	public:
		monster_list();
		void adiciona_monstro(monster* x);
		void retira_monstro();
		void increase_src();
		bool tem_elementos();
		void limpa_elementos();
		void draw_elementos(sf::RenderWindow* pont_window);
	
		node *primeiro_elemento;
		node *ultimo_elemento;
};
#endif