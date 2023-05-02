#pragma once

class Entity
{
private:
public:
    Entity();
    ~Entity();
    virtual void draw() = 0;
};

Entity::Entity()
{
}

Entity::~Entity()
{
}
