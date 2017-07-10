#include <iostream>
#include "cat.hpp"
#include <time.h>
#include "wave.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Window/Mouse.hpp>
//Linha referente para remover o cmd no windows.
//#include <windows.h>
int main()
{
	//Linhas referentes para remover o cmd no windows.
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow( hWnd, SW_HIDE );
    if(!monster::texture_Monster->loadFromFile("textures/Monster/monster.png")){
        std::cout<<"failed to load monster texture";
    }

    srand(time(NULL));

    int  WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

    bool lose_screen = false;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cat Fury");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    
    //load nas texturas
    sf::Texture texture_Scenery;
    if(!texture_Scenery.loadFromFile("textures/Chinese_Temple/Chinese_Temple.png"))
    	std::cout << "failed to load temple texture" << std::endl;

    sf::Texture button;
    if(!button.loadFromFile("textures/Button/normal.png")){
        std::cout << "failed to load button texture" << std::endl;
    }

    //construindo gato
    cat gato(WINDOW_WIDTH,WINDOW_HEIGHT);
    sf::Sprite button_sprite(button);
    button_sprite.setTextureRect(sf::IntRect(102,0,102,34));
    button_sprite.setOrigin(button_sprite.getTextureRect().width/2,0);
    button_sprite.setPosition(gato.cat_sprite.getPosition().x,WINDOW_HEIGHT/2);
    monster_list lista_esquerda; //andando pra direita
    monster_list lista_direita; //andando pra esquerda
    wave* mywave = new wave;
    
    

    //sprite cenario
    sf::Sprite scenery(texture_Scenery);
    scenery.setTextureRect(sf::IntRect(65,53,30,27));
    scenery.scale(4.f,4.f);
    scenery.setPosition(WINDOW_WIDTH-4*scenery.getTextureRect().width, ((float)5/6)*WINDOW_HEIGHT-4*scenery.getTextureRect().height);


    //chao
    sf::RectangleShape ground(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    ground.setFillColor(sf::Color(51,25,0));
    ground.setPosition(sf::Vector2f( 0, ((float)5/6)*WINDOW_HEIGHT) );

    sf::Music music;
    if(!music.openFromFile("Music/holdtheline_1.ogg")){ 
        std::cout<<"failed to load music file\n";
    }
    music.setLoop(true);    
    music.play();
    sf::Clock clock;
    sf::Time time;
    sf::Time time_passed;
    sf::Time monster_time;
    sf::Time spawn_time;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
        	switch (event.type){

        		case sf::Event::Closed:
                	window.close();
                	break;
                case  sf::Event::KeyPressed:
                	switch(event.key.code){
                		case sf::Keyboard::Right:
                            if(gato.punching_left){
                				gato.punching_left = false;
                				gato.src=0;
                			}
                			gato.punching_right = true;
                			break;
                		case sf::Keyboard::Left:
                			if(gato.punching_right){
                					gato.punching_right = false;
                					gato.src=0;
                				}
                			gato.punching_left = true;
                			break;
                	}
                break;
        	}
		}
        sf::Time time_passed = clock.getElapsedTime();
        clock.restart();
		time += time_passed;
        monster_time+=time_passed;
        spawn_time+=time_passed;

        if(lista_esquerda.tem_elementos()){ //se gato morre pra monstro lista esquerda
            if(lista_esquerda.primeiro_elemento->info->monster_sprite.getPosition().x>=gato.cat_sprite.getPosition().x)
                lose_screen = true;
        }
        if(lista_direita.tem_elementos()){ //se gato morre pra monstro lista direita
            if(lista_direita.primeiro_elemento->info->monster_sprite.getPosition().x<=gato.cat_sprite.getPosition().x)
                lose_screen = true;
        }

        if(lose_screen){
            
            music.stop();
            window.draw(button_sprite);
            window.draw(gato.dead_sprite);
            if(sf::Mouse::getPosition(window).x>=(button_sprite.getPosition().x-button_sprite.getTextureRect().width/2)&&sf::Mouse::getPosition(window).x<=(button_sprite.getPosition().x+button_sprite.getTextureRect().width/2)&&sf::Mouse::getPosition(window).y>=(WINDOW_HEIGHT/2)&&sf::Mouse::getPosition(window).y<=(WINDOW_HEIGHT/2)+(button_sprite.getTextureRect().height)){
                button_sprite.setTextureRect(sf::IntRect(102,0,102,34));
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    lista_direita.limpa_elementos();
                    lista_esquerda.limpa_elementos();
                    wave::number_of_wave = 0;
                    mywave = new wave;
                    lose_screen = false;
                    music.play();
                }
            }
            else{
                button_sprite.setTextureRect(sf::IntRect(0,0,102,34));
            }
        }
       

        if(mywave->dead_monsters==mywave->monsters_in_wave){ //começar nova wave se preciso
            delete mywave;
            mywave = new wave;
        }
        
        
        if(monster_time.asMilliseconds()>=150*((float)1/mywave->speed_of_wave)){ //move monstros
            if(!lose_screen){
                if(spawn_time.asMilliseconds()>=(float)1500){
                    spawn_time = spawn_time - spawn_time;
                    if(mywave->monsters_summoned<mywave->monsters_in_wave){
                        mywave->summon(WINDOW_WIDTH,WINDOW_HEIGHT, &lista_esquerda, &lista_direita);
                    }
                }
            }
                                    
            monster_time = time-time; //reseta tempo
            lista_esquerda.increase_src();
            lista_direita.increase_src();
        }
        

        if( time.asMilliseconds()>=50 ){ //gato move

            time = time-time;

            if(gato.punching_right||gato.punching_left){
				gato.src++;
				if(gato.src*50>=gato.texture_Cat.getSize().x){
					gato.src=0;
					gato.punching_right = false;
					gato.punching_left = false;
				}
                else if(gato.src*50==200||gato.src*50==250){
                    if(gato.punching_right&&lista_direita.tem_elementos()){
                        if(lista_direita.primeiro_elemento->info->monster_sprite.getPosition().x-16<=gato.cat_sprite.getPosition().x+25 && lista_direita.primeiro_elemento->info->monster_sprite.getPosition().x+22>=gato.cat_sprite.getPosition().x+25){
                            lista_direita.retira_monstro();
                            mywave->dead_monsters++;
                        }
                    }                   
                    else if(gato.punching_left&&lista_esquerda.tem_elementos()){
                        if(lista_esquerda.primeiro_elemento->info->monster_sprite.getPosition().x+16>=gato.cat_sprite.getPosition().x-25&&lista_esquerda.primeiro_elemento->info->monster_sprite.getPosition().x-22<=gato.cat_sprite.getPosition().x-25){
                            lista_esquerda.retira_monstro();
                            mywave->dead_monsters++;
                        }
                    }
                }
				gato.cat_sprite.setTextureRect(sf::IntRect( 50*gato.src, 0, 50, 58) );

				if(gato.punching_left && (gato.turned==RIGHT) ){
					gato.turned=LEFT;
					gato.cat_sprite.scale(-1.f,1.f);
				}
				else if(gato.punching_right && (gato.turned==LEFT)){
					gato.turned=RIGHT;
					gato.cat_sprite.scale(-1.f,1.f);
				}
			}
		}

        if(!lose_screen){
            window.draw(gato.cat_sprite);
        }
            window.draw(ground);
            window.draw(scenery);
            sf::RenderWindow* pont_window = &window;
            lista_esquerda.draw_elementos(pont_window);
            lista_direita.draw_elementos(pont_window);	       
            window.display();
            window.clear(sf::Color(255,178,102));
    }

    return 0;
}

