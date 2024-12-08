#pragma once
#include<ctime>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>


class Game {
private:
  sf::RenderWindow* window;
  sf::Event event;
  sf::VideoMode videoMode;
  sf::RectangleShape enemy;
  float enemy_position_x;

  void initVariable();
  void initWindow();
  void initEnemy();
public:
  Game();
  virtual ~Game();

  bool is_running();
  void event_polling();
  void enemy_update();
  void render_enemy();
  void game_update();
  void game_render();
};