#include "Game.h"

void Game::initVariable() {
  this->window = nullptr;
  this->enemy_timer = 100.f;
  this->enemy_timer_max = 100.f;
  this->pause = false;
  this->points = 0;
  this->colors = {sf::Color::Cyan, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green};
}

void Game::initWindow() {
  this->videoMode.width = 800;
  this->videoMode.height = 800;
  this->window = new sf::RenderWindow(this->videoMode, "Aimless-lab");
  this->window->setFramerateLimit(60);
  this->deskTop = sf::VideoMode::getDesktopMode();
}

void Game::game_text() {
  if(!this->font.loadFromFile("operius-mono.ttf")) {
    std::cerr << "Error: Could not load font 'arial.ttf'" << std::endl;
    this->text.setString("****");
  }
  this->text.setFont(this->font);
  this->text.setFillColor(sf::Color::White);
  this->text.setString("Pause");
  this->text.setCharacterSize(50);

  sf::FloatRect textRect = this->text.getLocalBounds();
  this->text.setOrigin(textRect.width/2,textRect.height/2);
  this->text.setPosition((this->videoMode.width)/2.0f, (this->videoMode.height)/2.0f);

  this->pl_pt.setFont(this->font);
  this->pl_pt.setFillColor(sf::Color::White);
  this->pl_pt.setString("Points: " + std::to_string(this->points));
  this->pl_pt.setPosition(10.f, 10.f);
  this->pl_pt.setCharacterSize(20);
}

Game::Game() {
  this->initVariable();
  this->initWindow();
  this->game_text();
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
  this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>((this->window->getSize().x) - this->enemy.getSize().x)), 0.f);
  this->enemies.push_back(this->enemy);
}

void Game::spawn_enemies_random(float position_y) {

  this->enemy.setFillColor(this->colors[rand() % (this->colors.size())]);
  this->enemy.setSize(sf::Vector2f(50.f, 50.f));
  this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>((this->window->getSize().x) - this->enemy.getSize(). x)), position_y);
  this->enemies.push_back(this->enemy);
}

void Game::event_polling() {
  while(this->window->pollEvent(this->event)) {
    if(this->event.type == sf::Event::Closed) {
      this->window->close();
    }

    if(this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape) {
      this->pause = !this->pause;
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
    this->enemy_timer += 3.f;
  }

  for(auto i = this->enemies.begin(); i != (this->enemies.end());) {
    i->move(0, 10.f);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if(i->getGlobalBounds().contains(static_cast<float>(this->mouse_position.x), static_cast<float>(this->mouse_position.y))) {
        this->enemies.erase(i);
        this->points++;
        this->pl_pt.setString("Points: " + std::to_string(this->points));
      } else {
        ++i;
      } 
    } else if (i->getGlobalBounds().contains(static_cast<float>(this->mouse_position.x), static_cast<float>(this->mouse_position.y))) {
        this->enemies.erase(i);
        this->spawn_enemies_random(this->mouse_position.y);
    }
      else if(i->getPosition().y > this->window->getSize().y) {
        this->enemies.erase(i);
        this->points--;
        this->pl_pt.setString("Points: " + std::to_string(this->points));
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
  if(!this->pause) {
    this->render_enemies();
  } else {
    this->window->draw(this->text);
  }
  this->window->draw(this->pl_pt);
  this->window->display();
}