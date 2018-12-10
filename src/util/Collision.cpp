//
// Created by fab on 10/12/2018.
//

#include "Collision.h"

bool Collision::BoundingBoxTest(const sf::Sprite &Object1, const sf::Sprite &Object2)
{
    OrientedBoundingBox OBB1 (Object1);
    OrientedBoundingBox OBB2 (Object2);

    return BoundingBoxTest(OBB1, OBB2);
}

bool Collision::BoundingBoxTest(const sf::Sprite &Object1, const sf::RectangleShape &Object2)
{
    OrientedBoundingBox OBB1 (Object1);
    OrientedBoundingBox OBB2 (Object2);

    return BoundingBoxTest(OBB1, OBB2);
}

bool Collision::BoundingBoxTest(OrientedBoundingBox &OBB1, OrientedBoundingBox &OBB2) {


    // Create the four distinct axes that are perpendicular to the edges of the two rectangles
    sf::Vector2f Axes[4] = {
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[0].x,
                          OBB1.Points[1].y-OBB1.Points[0].y),
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[2].x,
                          OBB1.Points[1].y-OBB1.Points[2].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[3].x,
                          OBB2.Points[0].y-OBB2.Points[3].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[1].x,
                          OBB2.Points[0].y-OBB2.Points[1].y)
    };

    for (int i = 0; i<4; i++) // For each axis...
    {
        float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

        // ... project the points of both OBBs onto the axis ...
        OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
        OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

        // ... and check whether the outermost projected points of both OBBs overlap.
        // If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
        if (!((MinOBB2<=MaxOBB1)&&(MaxOBB2>=MinOBB1)))
            return false;
    }
    return true;
}
