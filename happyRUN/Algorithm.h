#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include <vector>
#include <cmath>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
using std::vector;
using sf::Image;
using sf::Texture;
using sf::Sprite;
using sf::Vector2f;
using sf::IntRect;

/**
 * Useful static functions and constants.
 */
class Algorithm {
public:
    /**
     * Creating vector of sf::Texture from sf::Image.
     * Maximum texture size usually is less than size of image,
     * and therefor, image must be split to textures.
     */
    static vector<Texture> textureVec(Image &image);
    /**
     * Creating vector of sf::Sprites from vector sf::Texture and positioning them.
     */
    static vector<Sprite> spriteVec(vector<Texture> &textures, Vector2f position);
    static float distance(Vector2f point1, Vector2f point2);
    static constexpr double PI = 3.14159265359; /**< PI double precision.*/
};


#endif
