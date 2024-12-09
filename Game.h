#pragma once
#include<iostream>
#include<ctime>
#include<vector>
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
  sf::VideoMode deskTop;
  sf::RectangleShape enemy;
  std::vector<sf::RectangleShape> enemies;
  sf::Vector2i mouse_position;
  sf::Text text;
  sf::Font font;

  bool pause;
  float enemy_timer;
  float enemy_timer_max;

  void initVariable();
  void initWindow();
  void game_text();

public:
  Game();
  virtual ~Game();

  void spawn_enemies();
  void update_mouse_position();
  bool is_running();
  void event_polling();
  void enemies_update();
  void render_enemies();
  void game_update();
  void game_render();
};