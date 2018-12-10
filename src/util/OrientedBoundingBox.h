//
// Created by fab on 10/12/2018.
//

#ifndef FORESTGUMPLITE_ORIENTEDBOUNDINGBOX_H
#define FORESTGUMPLITE_ORIENTEDBOUNDINGBOX_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class OrientedBoundingBox // Used in the BoundingBoxTest
{
public:
    OrientedBoundingBox (const sf::Sprite& Object); // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite

    OrientedBoundingBox(const sf::RectangleShape& rectangleShape);

    sf::Vector2f Points[4];

    void ProjectOntoAxis (const sf::Vector2f& Axis, float& Min, float& Max); // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points

};


#endif //FORESTGUMPLITE_ORIENTEDBOUNDINGBOX_H
