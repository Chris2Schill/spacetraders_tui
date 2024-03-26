#pragma once

#include "entity.h"

class ScriptableEntity
{
public:
    virtual ~ScriptableEntity() {}

    template<typename T>
    T& GetComponent()
    {
        return entity.getComponent<T>();
    }
protected:
    virtual void OnCreate() {}
    virtual void OnDestroy() {}
    virtual void OnUpdate(double ts) {}
private:
    Entity entity;

    friend class Scene;
};
