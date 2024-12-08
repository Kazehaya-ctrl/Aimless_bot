#include "Game.h"

void Game::initVariable() {
  this->window = nullptr;
}

void Game::initWindow() {
  this->videoMode.width = 800;
  this->videoMode.height = 800;
  this->window = new sf::RenderWindow(this->videoMode, "Aimless-bot");
  this->window->setFramerateLimit(60);
  this->enemy_position_x = (rand() % this->window->getSize().x);
}

void Game::initEnemy() {
  this->enemy.setSize(sf::Vector2f(50.f, 50.f));
  this->enemy.setFillColor(sf::Color::Red);
  this->enemy.setPosition(sf::Vector2f(this->enemy_position_x, 0.f));
}

Game::Game() {
  this->initVariable();
  this->initWindow();
  this->initEnemy();
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

void Game::enemy_update() {
  this->enemy.move(0, 10.f);
  if(this->enemy.getPosition().y > this->window->getSize().y) {
    this->enemy_position_x = rand() % this->window->getSize().x;
    this->enemy.setPosition(this->enemy_position_x, 0.f);
  }

}

void Game::render_enemy() {
  this->enemy_update();
  this->window->draw(this->enemy);
}

void Game::game_update() {
  this->event_polling();
}

void Game::game_render() {
  this->window->clear();
  this->render_enemy();
  this->window->display();
}