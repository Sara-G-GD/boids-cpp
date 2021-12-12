#ifndef _COHESION_CPP_
#define _COHESION_CPP_

#include <SFML/System/Vector2.hpp>
#include "../boid.hpp"
#include "../Vector2.hpp"

namespace boids
{
	sf::Vector2f cohesion(const context_t& context)
	{
		sf::Vector2f velocity_target(0,0);
		sf::Vector2f position_target(0,0);

		size_t num{0};
		for(boid* b: context.all_boids)
		{
			if(b != context.self)
			{
				float dist = Vector2::distance(b->position(), context.position);
				if(dist < context.cohesion_range)
				{
					num++;
					position_target += b->position();
				}
			}
		}

		if(num == 0) return Vector2f(0,0);

		// average position of surrounding boids
		position_target = position_target / float(num);

		// direction towards average position of surrounding boids
		velocity_target = position_target - context.position;

		// normalized and scale
		velocity_target = Vector2::normalized(velocity_target) * context.max_desired_velocity;

		return Vector2::normalized(velocity_target - context.velocity) * context.cohesion_force * context.delta_time;
	}
}

#endif
