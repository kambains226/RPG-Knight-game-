

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 GetworldPos() { return worldPos; }
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos()=0;
    bool getAlive(){ return alive;}
    void setAlive(bool isAlive) { alive = isAlive;}
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 WorldPosLastFrame{}; 
    float rightleft{1.f};
    // animation variables
    float runningtime{};
    int frame{};
    int maxframes{6};
    float updatetime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};
private:
    bool alive{true};
};

#endif