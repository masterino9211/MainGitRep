#ifndef BEZIER_H
#define BEZIER_H
#include <SFML/System/Vector2.hpp>
#include <vector>

using std::vector;
using sf::Vector2i;
using sf::Vector2f;

class Bezier
{
public:
	Bezier(Vector2f p1, Vector2f p2);
	Bezier(Vector2f p1, Vector2f p2, Vector2f p3);
	Vector2f position(float arg);
	Vector2f direction(float arg);
	float angle(float arg);
	vector<Vector2i> stops() const;
private:
	int mOrder;
	Vector2f mP1;
	Vector2f mP2;
	Vector2f mP3;
};

#endif // BEZIER_H
