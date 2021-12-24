#ifndef _BOID_HPP_
#define _BOID_HPP_

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "context.hpp"

using sf::Vector2f;
using std::vector;

namespace boids {
struct boid;

using behaviour = Vector2f(*)(const context_t& context);
using behaviourList = std::vector<behaviour>;

struct boid {
public: // constructors
	boid();
	boid(Vector2f position, Vector2f velocity);

	// non-copyable
	boid(const boid&) = delete;
	boid operator=(const boid&) = delete;

private: // member variables
	Vector2f m_position;
	Vector2f m_velocity;
	float m_mass{1000.0f};

private: // behaviours
	behaviourList m_behaviours;

public: // member functions
	void add_behaviour(behaviour b) { m_behaviours.push_back(b); }
	void update_position();

public: // getters
	behaviourList behaviours() { return m_behaviours; }
	Vector2f position() const { return m_position; }
	Vector2f velocity() const { return m_velocity; }
	float mass() { return m_mass; }
	void add_force(Vector2f force) { m_velocity += force; }

public: // static
	static vector<boid*> m_boids;
}; // class boid

void deallocate_all();
void update_all(float dt);
void draw_all(sf::RenderWindow& target);
} // namespace boids

#include "boid.cpp"

#endif // _BOID_HPP_
