#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>
int main()
{
    const int wwidth{384};
    const int wheight{384};
    InitWindow(wwidth, wheight, "SHUSH");

    Texture2D map = LoadTexture("nature_tileset/World_map.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{wwidth, wheight};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}

    };
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),

    };

    Enemy slime{
        Vector2{500.f, 700.f} ,
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),

    };

    Enemy* enemies[]{
        &goblin,
        &slime};
    for (auto enemy : enemies)
    {
        
        enemy->setTarget(&knight);
    }

        
        SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // update animation frame
        mapPos = Vector2Scale(knight.GetworldPos(), -1.f);
        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.GetworldPos());
        }
        if (!knight.getAlive())
        {
            DrawText("Game over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            main();
            continue;
        }
        else
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.gethealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.GetworldPos().x < 0.f ||
            knight.GetworldPos().y < 0.f ||
            knight.GetworldPos().x + wwidth > map.width * mapScale ||
            knight.GetworldPos().y + wheight > map.height * mapScale)
        {
            knight.undoMovement();
        }
        // check prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.GetworldPos()), knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        for (auto enemy : enemies)

        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy: enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
}