#include "Game.h"

void Game::initVariable() {
  this->window = nullptr;
  this->enemy_timer = 100.f;
  this->enemy_timer_max = 100.f;
}

void Game::initWindow() {
  this->videoMode.width = 800;
  this->videoMode.height = 800;
  this->window = new sf::RenderWindow(this->videoMode, "Aimless-bot");

  this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
  this->enemy.setSize(sf::Vector2f(50.f, 50.f));
  this->enemy.setFillColor(sf::Color::Red);
  this->enemy.setPosition(sf::Vector2f(static_cast<float>(rand() % static_cast<int>(this->window->getSize().y)), 0.f));

}

Game::Game() {
  this->initVariable();
  this->initWindow();
  // this->initEnemies();
}

Game::~Game() {
  delete this->window;
}

bool Game::is_running() {
  return this->window->isOpen();
}

void Game::spawn_enemies() {
  this->enemy.setFillColor(sf::Color::Red);
  this->enemy.setSize(sf::Vector2f(50.f, 50.f));
  this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x)), 0.f);
  this->enemies.push_back(this->enemy);
}

void Game::event_polling() {
  while(this->window->pollEvent(this->event)) {
    if(this->event.type == sf::Event::Closed) {
      this->window->close();
    }
  }
}

void Game::update_mouse_position() {
  this->mouse_position = sf::Mouse::getPosition(*this->window);
}

void Game::enemies_update() {

  if(this->enemy_timer >= this->enemy_timer_max) {
    this->spawn_enemies();
    this->enemy_timer = 0.f;
  } else {
    this->enemy_timer += 7.f;
  }

  for(auto i = this->enemies.begin(); i != (this->enemies.end());) {
    i->move(0, 10.f);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if(i->getGlobalBounds().contains(static_cast<float>(this->mouse_position.x), static_cast<float>(this->mouse_position.y))) {
        this->enemies.erase(i);
      } else {
        ++i;
      }
    } else if(this->enemy.getPosition().y > this->window->getSize().y) {
      this->enemies.erase(i);
    } else {
      ++i;
    }
  }

}

void Game::render_enemies() {
  this->enemies_update();
  for(auto &a : this->enemies) {
    this->window->draw(a);
  }
}

void Game::game_update() {
  this->update_mouse_position();
  this->event_polling();
}

void Game::game_render() {
  this->window->clear();
  this->render_enemies();
  this->window->display();
}