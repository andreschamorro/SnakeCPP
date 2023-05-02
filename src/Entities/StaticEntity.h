#pragma once
#include "Entity.h"

class StaticEntity : public Entity
{
private:
    int x, y;
public:
    StaticEntity(int x, int y);
    ~StaticEntity();
};

StaticEntity::StaticEntity(int x, int y)
{
    this->x = x;
    this->y = y;
}

StaticEntity::~StaticEntity()
{
}
