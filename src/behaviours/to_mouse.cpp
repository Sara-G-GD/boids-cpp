#ifndef _TO_MOUSE_CPP_
#define _TO_MOUSE_CPP_

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../boid.hpp"
#include "../Vector2.hpp"

namespace boids
{
	sf::Vector2f to_mouse(const context_t& context)
	{
		sf::Vector2f velocity_target(0,0);
		sf::Vector2f position_target{ static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) };

		if(Vector2::distance(position_target, context.position) <= context.targeting_range)
		{
			velocity_target = Vector2::normalized( position_target - context.position ) * context.max_desired_velocity;
		}
		else return sf::Vector2f(0,0);

		return Vector2::normalized(velocity_target - context.velocity) * context.targeting_force * context.delta_time;
	}
}

#endif // _TO_MOUSE_CPP_
