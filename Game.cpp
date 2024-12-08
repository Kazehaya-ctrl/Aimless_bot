#include "Game.h"

void Game::initVariable() {
  this->window = nullptr;
}

void Game::initWindow() {
  this->videoMode.width = 800;
  this->videoMode.height = 800;
  this->window = new sf::RenderWindow(this->videoMode, "Aimless-bot");
  this->window->setFramerateLimit(60);
}

Game::Game() {
  this->initVariable();
  this->initWindow();
}

Game::~Game() {
  delete this->window;
}

bool Game::is_running() {
  return this->window->isOpen();
}

void Game::event_polling() {
  while(this->window->pollEvent(this->event)) {
    if(this->event.type == sf::Event::Closed) {
      this->window->close();
    }
  }
}

void Game::game_update() {
  this->event_polling();
}

void Game::game_render() {
  this->window->clear();
  this->window->display();
}