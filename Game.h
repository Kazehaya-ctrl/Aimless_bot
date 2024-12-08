#pragma once
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
  void initVariable();
  void initWindow();
public:
  Game();
  virtual ~Game();

  bool is_running();
  void event_polling();
  void game_update();
  void game_render();
};