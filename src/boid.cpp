#ifndef _BOID_CPP_
#define _BOID_CPP_

#include "boid.hpp"
#include "context.hpp"
#include "Vector2.hpp"

#include "behaviours/separation.cpp"
#include "behaviours/cohesion.cpp"
#include "behaviours/alignment.cpp"
#include "behaviours/to_mouse.cpp"
#include <math.h>


namespace boids {
vector<boid*> boid::m_boids = vector<boid*>();

void deallocate_all()
{
	boid* b{nullptr};

	while(boid::m_boids.size() > 0)
	{
		b = boid::m_boids.at(0);
		boid::m_boids.erase( boid::m_boids.begin() );
		delete b;
	}
}

void update_all(float dt)
{
	for(boid* boid: boid::m_boids)
	{
		context_t context(boid->position(), boid->velocity(), dt, boid::m_boids, boid);

		for(behaviour beh: boid->behaviours())
			boid->add_force(beh(context) / boid->mass()); 

		boid->update_position();
	}
}

void draw_all(sf::RenderWindow& target)
{
	float radius = 5;
	sf::CircleShape circle(radius, 6);
	circle.setOrigin(radius, radius);
	circle.setFillColor(sf::Color::White);
	circle.setOutlineColor(sf::Color::White);

	for(auto b: boid::m_boids)
	{
		circle.setPosition(b->position());
		target.draw(circle);
	}
}

void boid::update_position()
{
	m_position += m_velocity;

	if (m_position.x < 0)
	{
		m_position.x += static_cast<float>(window.getSize().x);
	}
	else if (m_position.x > window.getSize().x)
	{
		m_position.x -= static_cast<float>(window.getSize().x);
	}

	if (m_position.y < 0)
	{
		m_position.y += static_cast<float>(window.getSize().y);
	}
	else if (m_position.y > window.getSize().y)
	{
		m_position.y -= static_cast<float>(window.getSize().y);
	}
}

// default constructor
boid::boid()
: boid(Vector2f(0,0), Vector2f(0,0))
{}

// position-velocity constructor
boid::boid(Vector2f position,
		   Vector2f velocity)
: m_position{position}
, m_velocity{velocity}
{
	m_boids.push_back(this);
	add_behaviour(&boids::separation);
	add_behaviour(&boids::cohesion);
	add_behaviour(&boids::alignment);
	add_behaviour(&boids::to_mouse);
}
} // namespace boids

#endif // _BOID_CPP_
