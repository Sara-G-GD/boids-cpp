#ifndef _CONTEXT_HPP_
#define _CONTEXT_HPP_

#include <SFML/System/Vector2.hpp>
#include <vector>
using sf::Vector2f;


namespace boids
{
struct boid;
using boid_list = std::vector<boids::boid*>&;

struct context_t
{
	Vector2f position;
	Vector2f velocity;
	boid_list all_boids;

	const boid* self;

	float delta_time;

	const float max_desired_velocity{0.55f};

	const float cohesion_range{75.0f};
	const float alignment_range{50.0f};
	const float separation_range{20.0f};
	const float targeting_range{0.0f};

	const float cohesion_force{0.5f};
	const float alignment_force{0.75f};
	const float separation_force{3.0f};
	const float targeting_force{0.0f};

	context_t(Vector2f pos, Vector2f vel, float dt, boid_list boids, boid* self_);
};

context_t::context_t(Vector2f pos, Vector2f vel, float dt, boid_list boids, boid* self_)
: position{pos}
, velocity{vel}
, all_boids{boids}
, delta_time{dt}
, self{self_}
{}
}

#endif
