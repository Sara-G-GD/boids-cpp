#ifndef _SEPARATION_CPP_
#define _SEPARATION_CPP_

#include <SFML/System/Vector2.hpp>
#include "../boid.hpp"
#include "../Vector2.hpp"

namespace boids
{
	sf::Vector2f separation(const context_t& context)
	{
		sf::Vector2f velocity_target(0,0);

		size_t num{0};
		for(boid* b: context.all_boids)
		{
			if(b != context.self)
			{
				float dist = Vector2::distance(b->position(), context.position);
				if(dist < context.separation_range)
				{
					num++;
					velocity_target += (context.position - b->position()) * Vector2::distance(context.position, b->position());
				}
			}
		}

		velocity_target = Vector2::normalized(velocity_target) * context.max_desired_velocity;

		if(velocity_target == sf::Vector2f(0,0))
			return velocity_target;

		return Vector2::normalized(velocity_target - context.velocity) * context.separation_force * context.delta_time;
	}
}

#endif
