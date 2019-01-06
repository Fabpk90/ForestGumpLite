//
// Created by fab on 14/11/18.
//

#ifndef FORESTGUMPLITE_SCENE_H
#define FORESTGUMPLITE_SCENE_H


class Scene
{
public:
    virtual ~Scene() = default;

    virtual void update() = 0;
};


#endif //FORESTGUMPLITE_SCENE_H
