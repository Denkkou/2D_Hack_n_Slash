#include "GameWorld.h"

GameWorld::GameWorld() {
    SDL_Log("GameWorld.cpp        | GameWorld created");
}

GameWorld::~GameWorld() {
    //deallocate music
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(coinSound);
    Mix_CloseAudio();
    SDL_Log("GameWorld.cpp        | Audio deallocated");
    SDL_Log("GameWorld.cpp        | GameWorld destroyed");
}

void GameWorld::Init() {
    //create window and renderer
    window = SDL_CreateWindow("[Joe Schofield - SCH18683720] CGP2015M - 2D Hack 'n' Slash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //progress bars
    TimeSprite.Load(renderer, "./content/sprites/hourglass.png", false);
    TimeSprite.Init(20, 20, 32, 42);
    countDownBar.Init(70, 19, 600, 30, 5, 30);

    ScoreSprite.Load(renderer, "./content/sprites/score.png", false);
    ScoreSprite.Init(20, 69, 32, 42);
    scoreBar.Init(70, 70, 600, 30, 5, coinContainer.aListOfCoins.size());

    //initialise player sprite
    player.playerSprite.Load(renderer, "./content/sprites/player_sheet.png", false);
    SDL_Log("GameWorld.cpp        | Player sprite loaded");

    //initialise splash sprite
    SplashGraphicSprite.Init(10, 10, 1580, 880);
    SplashGraphicSprite.Load(renderer, "./content/sprites/splashScreen.png", false);

    //initialise background sprite
    GameBackgroundSprite.Init(0, 0, 1600, 900);
    GameBackgroundSprite.Load(renderer, "./content/sprites/background.png", false);

    //initialise gameover sprite
    GameOverGraphicSprite.Init(10, 10, 1580, 880);
    GameOverGraphicSprite.Load(renderer, "./content/sprites/gameOver.png");

    //initialise for splash
    countdownTimer = 5;

    //initialise music and sfx files
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        SDL_Log("WARNING: Audio has not been found!");
    }
    else {
        //load files
        backgroundMusic = Mix_LoadMUS("./content/audio/backgroundMusic.wav");
        coinSound = Mix_LoadWAV("./content/audio/coinDing.wav");

        //volume
        Mix_VolumeMusic(musicVolume);
        Mix_VolumeChunk(coinSound, sfxVolume);
    }

    //play music
    if (Mix_PlayingMusic() == 0)
        Mix_PlayMusic(backgroundMusic, -1);
    else
        Mix_HaltMusic();
    
    //log initialisation
    SDL_Log("GameWorld.cpp        | Game World initialised");
}

//implement a timer sync function
void GameWorld::Run() {
    //splash screen
    SplashScreen();

    //reset timer
    countdownTimer = 30;

    //core game loop
    while (!done) {
        //reset timer, begin counting
        timer.resetTicks();

        //countdown timer code
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 1000) {
            lastTime = currentTime;
            SDL_Log("[GAME EVENT] Timer: %i", countdownTimer);
            countdownTimer--;
        }

        //receive input and handle
        inputHandler.HandleInput(done, player, timeGetter, window, musicVolume, sfxVolume);   
       
        //update state of the game world
        Update();

        //render when updated
        Render();

        //delay for rest of frame
        if (timer.getTicks() < DELTA_TIME)
            SDL_Delay(DELTA_TIME - timer.getTicks());

        //game over check
        if (countdownTimer <= 0) {
            done = true;
            countdownTimer = 5;
            GameOverScreen();
        }
    }
}

//initial splash screen, lasts 5 seconds
void GameWorld::SplashScreen() {
    bool splashDone = false;

    while (!splashDone) {
        //reset timer, begin counting
        timer.resetTicks();

        //countdown timer code
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 1000) {
            lastTime = currentTime;
            SDL_Log("[GAME EVENT] Splash Timer: %i", countdownTimer);
            countdownTimer--;
        }

        //draw something on screen
        SDL_SetRenderDrawColor(renderer, 180, 0, 0, 255);
        SDL_RenderClear(renderer);

        //render graphic
        SplashGraphicSprite.Render(renderer);

        //push changes
        SDL_RenderPresent(renderer);

        //delay for rest of frame
        if (timer.getTicks() < DELTA_TIME)
            SDL_Delay(DELTA_TIME - timer.getTicks());

        //check for timeout
        if (countdownTimer <= 0) {
            splashDone = true;
            SDL_Log("[GAME EVENT] Splash Screen Closing");
        }
    }
}

//game over screen, lasts 5 seconds
void GameWorld::GameOverScreen() {
    bool gameOverDone = false;

    while (!gameOverDone) {
        //reset timer, begin counting
        timer.resetTicks();

        //countdown timer code
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 1000) {
            lastTime = currentTime;
            SDL_Log("[GAME EVENT] Game Over Timer: %i", countdownTimer);
            countdownTimer--;
        }

        //draw something on screen
        SDL_SetRenderDrawColor(renderer, 180, 0, 0, 255);
        SDL_RenderClear(renderer);

        //render graphic
        GameOverGraphicSprite.Render(renderer);

        //push changes
        SDL_RenderPresent(renderer);

        //delay for rest of frame
        if (timer.getTicks() < DELTA_TIME)
            SDL_Delay(DELTA_TIME - timer.getTicks());

        //check for timeout
        if (countdownTimer <= 0) {
            gameOverDone = true;
            SDL_Log("[GAME EVENT] Game Over Screen Closing");
        }
    }
}

void GameWorld::Update() {
    //call the update function of all containers
    terrainContainer.Update();
    player.Update(timeGetter);

    countDownBar.Update(countdownTimer);
    scoreBar.Update(gameScore);

    //update volume values
    Mix_VolumeMusic(musicVolume);
    Mix_VolumeChunk(coinSound, sfxVolume);

    //reset grounding
    player.stateMachine.IS_GROUNDED = false;

    //detect for collision of platform terrain
    for (int i = 0; i < terrainContainer.aListOfPlatformObjects.size(); i++) {
        if (detectedCollision(player, terrainContainer.aListOfPlatformObjects[i])) {
            //move player up to object's y
            player.MoveUpOnCollision(terrainContainer.aListOfPlatformObjects[i]->Y);
        }
    }

    //detect for collision of pillar terrain
    for (int i = 0; i < terrainContainer.aListOfPillarObjects.size(); i++) {
        //if colliding from the sides
        if (detectedCollision(player, terrainContainer.aListOfPillarObjects[i])) {
            //reposition player, cancel their velocity
            player.MoveSidewaysOnCollision(terrainContainer.aListOfPillarObjects[i]->X, terrainContainer.aListOfPillarObjects[i]->W);
        }
    }

    //detect coin collision
    for (int i = 0; i < coinContainer.aListOfCoins.size(); i++) {
        if (detectedCoinCollision(player, coinContainer.aListOfCoins[i])) {
            SDL_Log("[GAME EVENT] Coin collected at x: %i, y: %i", player.posX, player.posY);

            //call coins getPickedUp()
            coinContainer.aListOfCoins[i]->GetPickedUp();
            gameScore++;
            SDL_Log("[GAME EVENT] Current Score: %i", gameScore);

            //play sfx
            Mix_PlayChannel(-1, coinSound, 0);
        }
    }
}

void GameWorld::Render() {
    //clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //draw background
    GameBackgroundSprite.Render(renderer);
    TimeSprite.Render(renderer);
    ScoreSprite.Render(renderer);

    //call the render function of all containers
    terrainContainer.Render(renderer);
    coinContainer.Render(renderer);
    player.Render(renderer);

    //draw bars
    countDownBar.Render(renderer);
    scoreBar.Render(renderer);

    //push changes
    SDL_RenderPresent(renderer);
}

bool GameWorld::detectedCollision(Player &player, TerrainObject* object) {
    //detect collision
    if (player.posX  < object->X + object->W &&
        player.posX + player.width > object->X &&
        player.posY + (player.height - object->H) < object->Y &&
        player.posY + (player.height + player.feetBoxOffset) > object->Y) {
        return true;
    }
    return false;
}

bool GameWorld::detectedCoinCollision(Player& player, Coin* object) {
    //detect collision
    if (player.posX  < object->X + object->W &&
        player.posX + player.width > object->X &&
        player.posY < object->Y + object->H &&
        player.posY + player.height > object->Y) {
        return true;
    }
    return false;
}

