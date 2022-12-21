#include "BaseCharacter.h" 
#include "raymath.h"


BaseCharacter::BaseCharacter()
{
   
}

void BaseCharacter::undoMovement()
{
    worldPos =WorldPosLastFrame;
}
Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width*scale,
        height*scale
    };
    
}
void BaseCharacter::tick (float deltaTime)
{
    WorldPosLastFrame = worldPos;
     // update animation frame
    runningtime += deltaTime;
    if (runningtime >= updatetime)
    {
        frame++;
        runningtime = 0.f;
        if (frame > maxframes)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity ={};
    // draw the character
    Rectangle source{frame * width, 0.f, rightleft *width , height};

    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}


