#pragma once
#include "StaticEntity.h"

class Rock : public StaticEntity
{
private:
public:
    Rock(int x, int y) : StaticEntity(x, y)
    {
    }
    ~Rock();

    void draw();
};
