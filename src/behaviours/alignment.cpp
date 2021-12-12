#ifndef _ALIGNMENT_CPP_
#define _ALIGNMENT_CPP_

#include <SFML/System/Vector2.hpp>
#include "../boid.hpp"
#include "../Vector2.hpp"

namespace boids
{
	sf::Vector2f alignment(const context_t& context)
	{
		sf::Vector2f velocity_target(0,0);

		size_t num{0};
		for(boid* b: context.all_boids)
		{
			if(b != context.self)
			{
				float dist = Vector2::distance(b->position(), context.position);
				if(dist < context.alignment_range)
				{
					num++;
					velocity_target += b->velocity();
				}
			}
		}

		if(num == 0) return Vector2f(0,0);

		// average position of surrounding boids
		velocity_target = velocity_target / float(num);

		// direction towards average position of surrounding boids
		// normalized and scale
		velocity_target = Vector2::normalized(velocity_target) * context.max_desired_velocity;

		return Vector2::normalized(velocity_target - context.velocity) * context.alignment_force * context.delta_time;
	}
}

#endif
