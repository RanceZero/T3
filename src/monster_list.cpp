#include "monster_list.hpp"

monster_list::monster_list(){
	primeiro_elemento = NULL;
	ultimo_elemento = NULL;
}

void monster_list::adiciona_monstro(monster* x){
	if(!this->tem_elementos()){
		primeiro_elemento = new node();
		primeiro_elemento->info = x;
		primeiro_elemento->next = primeiro_elemento;
		ultimo_elemento = primeiro_elemento;
	}
	else{
		ultimo_elemento->next = new node();
		ultimo_elemento = ultimo_elemento->next;
		ultimo_elemento->info = x;
		ultimo_elemento->next = primeiro_elemento;
	}
}

void monster_list::retira_monstro(){
	if(primeiro_elemento->next==primeiro_elemento){
		delete primeiro_elemento;
		primeiro_elemento = NULL;
		ultimo_elemento = NULL;
	}
	else{
		node* P = primeiro_elemento;
		primeiro_elemento = primeiro_elemento->next;
		delete P;
		P=NULL;
		ultimo_elemento->next = primeiro_elemento;
	}	
}

void monster_list::increase_src(){
	if(this->tem_elementos()){
		node* P = primeiro_elemento;
		do{
			P->info->src++;
			if(P->info->src*60>=120&&P->info->src*60<300){
				P->info->monster_sprite.move(P->info->walking_dir*9,0);
			}
			else if(P->info->src*60==P->info->texture_Monster->getSize().x){
        		P->info->src=0;
        	}
        	P->info->monster_sprite.setTextureRect(sf::IntRect( 60*P->info->src, 0, 60, 72 ) );
        	P = P->next;
		}	while(P!=primeiro_elemento);
	}
}

bool monster_list::tem_elementos(){
	if(primeiro_elemento==NULL)
		return false;
	else 
		return true;
}

void monster_list::limpa_elementos(){
	if(this->tem_elementos()){		
		node* P = primeiro_elemento;
		do{
			if(primeiro_elemento == ultimo_elemento->next){
				delete primeiro_elemento;
				primeiro_elemento = NULL;
				ultimo_elemento = NULL;
				P=NULL;
			}
			else{
				primeiro_elemento = primeiro_elemento->next;
				delete P;
				P=primeiro_elemento;
			}			
		} while (P!=NULL);
	}
}


void monster_list::draw_elementos(sf::RenderWindow* pont_window){
	if(this->tem_elementos()){
		node* P = primeiro_elemento;
		do{
			pont_window->draw(P->info->monster_sprite);
			P = P->next;
		} while(P!=primeiro_elemento);
	}
}
