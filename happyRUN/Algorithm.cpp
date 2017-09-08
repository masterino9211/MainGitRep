#include "Algorithm.h"

using sf::Vector2u;

vector<Sprite > Algorithm::spriteVec(vector< Texture > &textures, Vector2f position)
{
    vector<Sprite> sprites;


    for(int i = 0, n = textures.size(), width = textures[i].getSize().x; i < n; i++) {
        Sprite tmp;
        tmp.setTexture(textures[i]);
        tmp.setPosition(position + Vector2f(i * width, 0));
        sprites.push_back(tmp);
    }

    return sprites;
}


vector< Texture > Algorithm::textureVec(Image &image)
{
    vector<Texture> textures;

    //Idea: image is split into columns.
    //Pros: easier for implementation and storing
    //Cons: texture size is less then maximum posible texture size.

    int maxSize = Texture::getMaximumSize();
    Vector2u imageSize = image.getSize();
    unsigned int width = maxSize / imageSize.y;
    unsigned int n = imageSize.x / width;
    unsigned int remainder = imageSize.x % width;


    for(int i = 0; i < n; i++) {
        Texture tmp;
        tmp.loadFromImage(image, IntRect(i * width, 0, width, imageSize.y));
        textures.push_back(tmp);
    }



    if(remainder) {
        Texture tmp;
        tmp.loadFromImage(image);
        textures.push_back(tmp);
    }


    return textures;
}

float Algorithm::distance(Vector2f point1, Vector2f point2)
{
	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}


