#ifndef GLOBALS_h
#define GLOBALS_h


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>


const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;
const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
const int WIDTH = WINDOW_WIDTH / 2;
const int HEIGHT = WINDOW_HEIGHT / 2;

const int START_X = WINDOW_WIDTH / 2 - 700;
const int START_Y = WINDOW_HEIGHT / 2 - 400;

const float P_WIDTH = 25.f;
const float P_HEIGHT = 125.f;
const float P_SPEED = 9.f;
const float B_SPEED = 11.f;
const float B_RADIUS = 15.f;

#endif