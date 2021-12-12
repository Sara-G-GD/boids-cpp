#ifndef _VECTOR2_EXTENTIONS_HPP_
#define _VECTOR2_EXTENTIONS_HPP_

#include <SFML/System/Vector2.hpp>
#include <math.h>

namespace Vector2
{
template <typename T>
T dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b);

template <typename T>
T cross(const sf::Vector2<T>& a, const sf::Vector2<T>& b);

template<typename T>
sf::Vector2<T> normalized(const sf::Vector2<T>& vec);

template <typename T>
T magnitude(const sf::Vector2<T>& vec);

template <typename T>
T distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b);

template <typename T>
sf::Vector2<T> lerp(sf::Vector2<T> from, sf::Vector2<T> to, float time);

template <typename T>
sf::Vector2<T> clamp_magnitude(sf::Vector2<T> v, T max_magnitude);

template <typename T>
sf::Vector2<T> clamp_magnitude(sf::Vector2<T> v, T max_magnitude)
{
	if(magnitude<T>(v) > max_magnitude)
	{
		return normalized<T>(v) * max_magnitude;
	}
	else
	{
		return v;
	}
}

template <typename T>
T dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}

template <typename T>
T cross(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	return (a.x*b.y) - (a.y*b.x);
}

template <typename T>
sf::Vector2<T> lerp(sf::Vector2<T> from, sf::Vector2<T> to, float time)
{
	float mag = distance<T>(from, to);
	sf::Vector2<T> dir = to - from;
	
	// clamp time
	if(time < 0) time = 0;
	if(time > 1) time = 1;

	return from + dir * mag * time;
}

template<typename T>
sf::Vector2<T> normalized(const sf::Vector2<T>& vec)
{
	T mag = magnitude<T>(vec);
	if(mag == 0) return vec;
	return sf::Vector2<T>(vec.x, vec.y) / mag;
}

template <typename T>
T magnitude(const sf::Vector2<T>& vec)
{
	T x{vec.x}, y{vec.y};
	if(x == 0 && y == 0) return 0;

	if(x < 0) x = -x;
	if(y < 0) y = -y;

	return sqrt(x * x + y * y);
}

template <typename T>
T distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	T x = (a.x > b.x) ? a.x - b.x : b.x - a.x;
	T y = (a.y > b.y) ? a.y - b.y : b.y - a.y;

	if(a == b) return 0;

	return sqrt(x * x + y * y);
}
}

#endif // _VECTOR2_EXTENTIONS_HPP_
