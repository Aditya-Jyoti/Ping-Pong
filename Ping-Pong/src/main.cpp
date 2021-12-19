#include <iostream>
#include <random>
#include <vector>

#include <globals.hpp>
#include <ping-pong.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

Game::Velocity Game::normalize(double pos1, double pos2)
{
	float magnitude = sqrt(pos1 * pos1 + pos2 * pos2);
	double unit1 = pos1 / magnitude;
	double unit2 = pos2 / magnitude;

	Game::Velocity vel;
	vel.x = unit1;
	vel.y = unit2;
	return vel;
};

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initEnemy();
	this->initBall();
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	this->isWinOpen = true;
	this->window = new sf::RenderWindow(
		sf::VideoMode(WIDTH, HEIGHT),
		"PING PONG",
		sf::Style::Titlebar | sf::Style::Close);
	this->window->setPosition(sf::Vector2i(START_X, START_Y));
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	this->enemy.setSize(sf::Vector2f(P_WIDTH, P_HEIGHT));
	this->enemy.setPosition(sf::Vector2f((WIDTH - (2.f * P_WIDTH)), (HEIGHT / 2) - (P_HEIGHT / 2)));
	this->enemy.setFillColor(sf::Color::White);
}

void Game::initPlayer()
{
	this->player.setSize(sf::Vector2f(P_WIDTH, P_HEIGHT));
	this->player.setPosition(sf::Vector2f(30.f, (HEIGHT / 2) - (P_HEIGHT / 2)));
	this->player.setFillColor(sf::Color::White);
}

void Game::initBall()
{
	this->isCollision = false;

	this->ball.setRadius(B_RADIUS);
	this->ball.setPosition((WIDTH / 2) - B_RADIUS, (HEIGHT / 2) - B_RADIUS);
	this->ball.setFillColor(sf::Color::White);

	std::uniform_int_distribution<int> dis{0, 360};
	this->angle = dis(this->gen);

	this->velocity.x = cos(this->angle * 3.14159 / 180);
	this->velocity.y = sin(this->angle * 3.14159 / 180);

	Game::Velocity vel = this->normalize(velocity.x, velocity.y);
	this->velocity.x = vel.x * B_SPEED;
	this->velocity.y = vel.y * B_SPEED;
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			this->isWinOpen = false;
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				this->isWinOpen = false;
			}
			if (this->event.key.code == sf::Keyboard::Up)
			{
				this->moveDirec = 'u';
			}
			if (this->event.key.code == sf::Keyboard::Down)
			{
				this->moveDirec = 'd';
			}
			break;
		}
	}
}

void Game::updateBall()
{

	sf::Vector2f ballPos = this->ball.getPosition();
	sf::Vector2f enemyBallPos;
	enemyBallPos.y = ballPos.y;
	enemyBallPos.x = ballPos.x + P_WIDTH;

	if (ballPos.y <= 1.f || ballPos.y + B_RADIUS >= HEIGHT - 17.f)
	{
		this->velocity.y = -this->velocity.y;
	}

	else if (ballPos.x >= WIDTH - 17.f || ballPos.x <= 1.f)
	{
		this->velocity.x = -this->velocity.x;
	}

	else if (this->player.getGlobalBounds().contains(this->ball.getPosition()))
	{
		std::uniform_int_distribution<int> dis{0, 180};
		this->angle = dis(this->gen);

		this->velocity.y = sin(this->angle * 3.14159 / 180) * B_SPEED;
		this->velocity.x = -this->velocity.x;
	}

	else if (this->enemy.getGlobalBounds().contains(enemyBallPos))
	{
		std::uniform_int_distribution<int> dis{180, 360};
		this->angle = dis(this->gen);

		this->velocity.y = sin(this->angle * 3.14159 / 180) * B_SPEED;
		this->velocity.x = -this->velocity.x;
	}

	Game::Velocity vel = this->normalize(velocity.x, velocity.y);
	this->velocity.x = vel.x * B_SPEED;
	this->velocity.y = vel.y * B_SPEED;

	this->ball.move(this->velocity.x, this->velocity.y);
}

void Game::updatePlayer()
{

	if (this->moveDirec == 'u')
	{
		this->player.move(0.f, -P_SPEED);
	}
	else if (this->moveDirec == 'd')
	{
		this->player.move(0.f, P_SPEED);
	}

	sf::Vector2f playerPos = this->player.getPosition();
	if (playerPos.y + P_HEIGHT > HEIGHT - 5.f)
	{
		this->player.setPosition(30.f, (HEIGHT - P_HEIGHT) - 5.f);
	}
	else if (playerPos.y < 5.f)
	{
		this->player.setPosition(30.f, 5.f);
	}
}

void Game::updateEnemy()
{
	
	this->enemy.move(0.f, this->velocity.y);
}

void Game::update()
{
	this->updateEvents();
	this->updatePlayer();
	this->updateEnemy();
	this->updateBall();
}

void Game::render()
{
	this->window->clear(sf::Color(32, 33, 38, 255));

	sf::RectangleShape line(sf::Vector2f(10.f, HEIGHT));
	line.setFillColor(sf::Color::White);
	line.setPosition((WIDTH / 2) - 5.f, 0);
	this->window->draw(line);

	this->window->draw(this->ball);
	this->window->draw(this->enemy);
	this->window->draw(this->player);
	this->window->display();
}

int main()
{
	Game game;
	while (game.isWinOpen)
	{
		game.update();
		game.render();
	}
}