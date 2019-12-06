#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/TextLabelComponent.h"
#include "./Components/ProjectileEmitterComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, 50};
Map* map;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL TTF" << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
    srand(time(NULL));
    LoadLevel(0);

    isRunning = true;
    return;
}


//Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));
Entity& player(manager.AddEntity("spaceship", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {
    /* Start including new assets to the assetmanager list */
    assetManager->AddTexture("ship-image", std::string("./assets/images/Ship.png").c_str());
    assetManager->AddTexture("space-tiletexture", std::string("./assets/tilemaps/generic.png").c_str());
    assetManager->AddTexture("asteroid-image", std::string("./assets/images/asteroid.png").c_str());
    assetManager->AddTexture("goal-image", std::string("./assets/images/goal.png").c_str());
    assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);
    

    map = new Map("space-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/generic.map", 25, 10);

    /* Start including entities and also components to them */

    player.AddComponent<TransformComponent>(150, 106, 0, 0, 64, 64, 1);
    player.AddComponent<SpriteComponent>("ship-image", 1, 1, true, false);
    player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    player.AddComponent<ColliderComponent>("PLAYER", 150, 106, 64, 64);

    int ramdomY=10+rand()%550;
    int randomS=1+rand()%5;
    Entity& asteroid1(manager.AddEntity("asteroid-1", ENEMY_LAYER));
    asteroid1.AddComponent<TransformComponent>(400, ramdomY, -10, 0, 32, 32, randomS);
    asteroid1.AddComponent<SpriteComponent>("asteroid-image");
    asteroid1.AddComponent<ColliderComponent>("ENEMY", 400, ramdomY, 32, 32);

    ramdomY=10+rand()%550;
    randomS=1+rand()%5;
    Entity& asteroid2(manager.AddEntity("asteroid-2", ENEMY_LAYER));
    asteroid2.AddComponent<TransformComponent>(600, ramdomY, -10, 0, 32, 32, randomS);
    asteroid2.AddComponent<SpriteComponent>("asteroid-image");
    asteroid2.AddComponent<ColliderComponent>("ENEMY", 600, ramdomY, 32, 32);

    ramdomY=10+rand()%550;
    randomS=1+rand()%5;
    Entity& asteroid3(manager.AddEntity("asteroid-3", ENEMY_LAYER));
    asteroid3.AddComponent<TransformComponent>(800, ramdomY, -10, 0, 32, 32, randomS);
    asteroid3.AddComponent<SpriteComponent>("asteroid-image");
    asteroid3.AddComponent<ColliderComponent>("ENEMY", 800, ramdomY, 32, 32);

    ramdomY=10+rand()%550;
    randomS=1+rand()%5;
    Entity& asteroid4(manager.AddEntity("asteroid-4", ENEMY_LAYER));
    asteroid4.AddComponent<TransformComponent>(1000, ramdomY, -10, 0, 32, 32, randomS);
    asteroid4.AddComponent<SpriteComponent>("asteroid-image");
    asteroid4.AddComponent<ColliderComponent>("ENEMY", 1000, ramdomY, 32, 32);

    ramdomY=10+rand()%550;
    randomS=1+rand()%5;
    Entity& asteroid5(manager.AddEntity("asteroid-5", ENEMY_LAYER));
    asteroid5.AddComponent<TransformComponent>(1200, ramdomY, -10, 0, 32, 32, randomS);
    asteroid5.AddComponent<SpriteComponent>("asteroid-image");
    asteroid5.AddComponent<ColliderComponent>("ENEMY", 1200, ramdomY, 32, 32);

    ramdomY=10+rand()%550;
    randomS=1+rand()%5;
    Entity& asteroid6(manager.AddEntity("asteroid-6", ENEMY_LAYER));
    asteroid6.AddComponent<TransformComponent>(1400, ramdomY, -10, 0, 32, 32, randomS);
    asteroid6.AddComponent<SpriteComponent>("asteroid-image");
    asteroid6.AddComponent<ColliderComponent>("ENEMY", 1400, ramdomY, 32, 32);

    ramdomY=10+rand()%550;
    randomS=1+rand()%5;
    Entity& asteroid7(manager.AddEntity("asteroid-7", ENEMY_LAYER));
    asteroid7.AddComponent<TransformComponent>(1600, ramdomY, -10, 0, 32, 32, randomS);
    asteroid7.AddComponent<SpriteComponent>("asteroid-image");
    asteroid7.AddComponent<ColliderComponent>("ENEMY", 1600, ramdomY, 32, 32);

    ramdomY=10+rand()%550;
    randomS=1+rand()%5;
    Entity& asteroid8(manager.AddEntity("asteroid-8", ENEMY_LAYER));
    asteroid8.AddComponent<TransformComponent>(1800, ramdomY, -10, 0, 32, 32, randomS);
    asteroid8.AddComponent<SpriteComponent>("asteroid-image");
    asteroid8.AddComponent<ColliderComponent>("ENEMY", 1800, ramdomY, 32, 32);

    Entity& goal1(manager.AddEntity("Goal-1", OBSTACLE_LAYER));
    goal1.AddComponent<TransformComponent>(1555, 300, 0, 0, 42, 42, 1);
    goal1.AddComponent<SpriteComponent>("goal-image");
    goal1.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    Entity& goal2(manager.AddEntity("Goal-2", OBSTACLE_LAYER));
    goal2.AddComponent<TransformComponent>(1555, 342, 0, 0, 42, 42, 1);
    goal2.AddComponent<SpriteComponent>("goal-image");
    goal2.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    Entity& goal3(manager.AddEntity("Goal-3", OBSTACLE_LAYER));
    goal3.AddComponent<TransformComponent>(1555, 384, 0, 0, 42, 42, 1);
    goal3.AddComponent<SpriteComponent>("goal-image");
    goal3.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
    labelLevelName.AddComponent<TextLabelComponent>(10, 10, "Asteroids", "charriot-font", WHITE_COLOR);

    
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

void Game::Update() {
    // Wait until 16ms has ellapsed since the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    // Delta time is the difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);

    HandleCameraMovement();
    CheckCollisions();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
    TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 4);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions() {
    CollisionType collisionType = manager.CheckCollisions();
    if (collisionType == PLAYER_ENEMY_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_PROJECTILE_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
        ProcessNextLevel(1);
    }
}

void Game::ProcessNextLevel(int levelNumber) {
    std::cout << "Level Complete" << std::endl;
    isRunning = false;
}

void Game::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    isRunning = false;
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
