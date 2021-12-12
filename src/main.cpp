#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(1200, 1200), "boids");

#include "boid.hpp"

int main(/*int argc, char* argv[]*/)
{
	sf::Vector2f center = static_cast<sf::Vector2f>(window.getSize()) * 0.5f;

	// generate a block of boids in the top-left
	for(int x{10}; x < 100; x += 10)
	{
		for(int y{10}; y < 100; y += 10)
		{
			new boids::boid(sf::Vector2f(x, y), sf::Vector2f(0,0));
		}
	}
	// generate a block of boids in the bottom-right
	for(int x{10}; x < 100; x += 10)
	{
		for(int y{10}; y < 100; y += 10)
		{
			new boids::boid(sf::Vector2f(window.getSize().x - x, window.getSize().y - y), sf::Vector2f(0,0));
		}
	}

	sf::Clock frame;
	frame.restart();
	while(window.isOpen())
	{
		if(frame.getElapsedTime().asMilliseconds() > 1.6)
		{
			boids::update_all(frame.restart().asMilliseconds());
		}

		window.clear();

		boids::draw_all(window);
		
		window.display();

		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				default:
					break;
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
	}

	boids::deallocate_all();

	return 0;
}
