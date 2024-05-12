#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#include <list>
#include <math.h>
using namespace std;

float s = 1;
SDL_FRect phitbox;
float playerhp = 5;
int score = 0;
SDL_FRect energyBar = {energyBar.x = 50, energyBar.y = 500, energyBar.w = 200, energyBar.h = 20};
SDL_Rect _energyBar = {_energyBar.x = 50, _energyBar.y = 500, _energyBar.w = 200, _energyBar.h = 20};
SDL_Rect hpBar = {hpBar.x = 50, hpBar.y = 520, hpBar.w = playerhp*40, hpBar.h =20};
SDL_Rect _hpBar = {_hpBar.x = 50, _hpBar.y = 520, _hpBar.w = playerhp*40, _hpBar.h =20};

// Make bullet
struct Bullet
{
    SDL_FRect rect;
    float speed;
    float angle;
};

std::list<Bullet> bullets;
void shootBullet(float x, float y, float angle)
{
    Bullet bullet;
    bullet.rect.x = x;
    bullet.rect.y = y;
    bullet.rect.w = 32;
    bullet.rect.h = 6;
    bullet.angle = angle;
    bullet.speed = 15;
    bullets.push_back(bullet);
}

void updateBullets()
{
    for (auto &bullet : bullets)
    {
        bullet.rect.x += cos(bullet.angle) * bullet.speed * s;
        bullet.rect.y += sin(bullet.angle) * bullet.speed * s;
    }
}

// Make enemy
struct Enemy
{
    SDL_FRect rect;
    SDL_FRect hitbox;
    float speed;
    float angle;
};

list<Enemy> enemies;
void spawnEnemy(float x, float y, float angle)
{
    Enemy enemy;
    enemy.rect.x = x;
    enemy.rect.y = y;
    enemy.rect.w = 50;
    enemy.rect.h = 50;
    enemy.speed = 4;
    enemy.angle = angle;
    enemies.push_back(enemy);
}

void updateEnemies()
{
    for (auto &enemy : enemies)
    {
        enemy.rect.x += cos(enemy.angle) * enemy.speed * s;
        enemy.rect.y += sin(enemy.angle) * enemy.speed * s;
    }
}

struct Enemy2
{
    SDL_FRect rect;
    SDL_FRect hitbox;
    float hp = 3;
    float speed;
    float angle;
};

list<Enemy2> enemies2;
void spawnEnemy2(float x, float y, float angle)
{
    Enemy2 enemy2;
    enemy2.rect.x = x;
    enemy2.rect.y = y;
    enemy2.rect.w = 50;
    enemy2.rect.h = 50;
    enemy2.speed = 3.5;
    enemy2.angle = angle;
    enemies2.push_back(enemy2);
}

void updateEnemies2()
{
    for (auto &enemy2 : enemies2)
    {
        enemy2.rect.x += cos(enemy2.angle) * enemy2.speed * s;
        enemy2.rect.y += sin(enemy2.angle) * enemy2.speed * s;
    }
}

struct Enemy3
{
    SDL_FRect rect;
    SDL_FRect hitbox;
    float hp = 5;
    float speed;
    float angle;
};

list<Enemy3> enemies3;
void spawnEnemy3(float x, float y, float angle)
{
    Enemy3 enemy3;
    enemy3.rect.x = x;
    enemy3.rect.y = y;
    enemy3.rect.w = 50;
    enemy3.rect.h = 50;
    enemy3.speed = 3;
    enemy3.angle = angle;
    enemies3.push_back(enemy3);
}

void updateEnemies3()
{
    for (auto &enemy3 : enemies3)
    {
        enemy3.rect.x += cos(enemy3.angle) * enemy3.speed * s;
        enemy3.rect.y += sin(enemy3.angle) * enemy3.speed * s;
    }
}

struct EnemyBullet
{
    SDL_FRect rect;
    float speed;
    float angle;
};

list<EnemyBullet> enemyBullets;
void spawnEnemyBullet(float x, float y, float angle)
{
    EnemyBullet enemyBullet;
    enemyBullet.rect.x = x;
    enemyBullet.rect.y = y;
    enemyBullet.rect.w = 15;
    enemyBullet.rect.h = 15;
    enemyBullet.angle = angle;
    enemyBullet.speed = 2;
    enemyBullets.push_back(enemyBullet);
}

void updateEnemyBullets()
{
    for (auto &enemyBullet : enemyBullets)
    {
        enemyBullet.rect.x += cos(enemyBullet.angle) * enemyBullet.speed * s;
        enemyBullet.rect.y += sin(enemyBullet.angle) * enemyBullet.speed * s;
    }
}

struct Fuel
{
    SDL_FRect rect;
    float speed;
};

list<Fuel> fuels;
void spawnFuel(float x, float y)
{
    Fuel fuel;
    fuel.rect.x = x;
    fuel.rect.y = y;
    fuel.rect.w = 25;
    fuel.rect.h = 30;
    fuel.speed = 2;
    fuels.push_back(fuel);
}

void updateFuel()
{
    for (auto &fuel : fuels)
    {
        fuel.rect.y += fuel.speed * s;
    }
}

void checkCollisions()
{
    for (auto bullet = bullets.begin(); bullet != bullets.end();)
    {
        for (auto enemy2 = enemies2.begin(); enemy2 != enemies2.end();)
        {
            if (SDL_HasIntersectionF(&bullet->rect, &enemy2->hitbox))
            {
                enemy2->hp--;
                bullet = bullets.erase(bullet);
                if (enemy2->hp <= 0)
                {
                    int f = rand() % 90;
                    if (f == 10) spawnFuel(enemy2->rect.x, enemy2->rect.y);
                    enemy2 = enemies2.erase(enemy2);
                    score += 3;
                }
            }
            else
            {
                ++enemy2;
            }
        }

        for (auto enemy = enemies.begin(); enemy != enemies.end();)
        {
            if (SDL_HasIntersectionF(&bullet->rect, &enemy->hitbox))
            {
                int f = rand() % 120;
                if (f == 10) spawnFuel(enemy->rect.x, enemy->rect.y);
                bullet = bullets.erase(bullet);
                enemy = enemies.erase(enemy);
                score++;
            }
            else
            {
                ++enemy;
            }
        }

        for (auto enemy3 = enemies3.begin(); enemy3 != enemies3.end();)
        {
            if (SDL_HasIntersectionF(&bullet->rect, &enemy3->hitbox))
            {
                enemy3->hp--;
                bullet = bullets.erase(bullet);
                if (enemy3->hp <= 0)
                {
                    int f = rand() % 50;
                    if (f == 10) spawnFuel(enemy3->rect.x, enemy3->rect.y);
                    enemy3 = enemies3.erase(enemy3);
                    score += 6;
                }
            }
            else
            {
                ++enemy3;
            }
        }

        if (bullet != bullets.end())
        {
            ++bullet;
        }
    }
}

void checkplayercollsion()
{
    for (auto enemy = enemies.begin(); enemy != enemies.end();)
    {
        if (SDL_HasIntersectionF(&enemy->rect, &phitbox))
        {
            enemy = enemies.erase(enemy);
            playerhp--;
        }
        else
            ++enemy;
    }
    for (auto enemy2 = enemies2.begin(); enemy2 != enemies2.end();)
    {
        if (SDL_HasIntersectionF(&enemy2->rect, &phitbox))
        {
            enemy2 = enemies2.erase(enemy2);
            playerhp--;
        }
        else
            ++enemy2;
    }
    for (auto enemy3 = enemies3.begin(); enemy3 != enemies3.end();)
    {
        if (SDL_HasIntersectionF(&enemy3->rect, &phitbox))
        {
            enemy3 = enemies3.erase(enemy3);
            playerhp--;
        }
        else
            ++enemy3;
    }
    for (auto enemyBullet = enemyBullets.begin(); enemyBullet != enemyBullets.end();)
    {
        if (SDL_HasIntersectionF(&enemyBullet->rect, &phitbox))
        {
            enemyBullet = enemyBullets.erase(enemyBullet);
            playerhp--;
        }
        else
            ++enemyBullet;
    }
    for (auto fuel = fuels.begin(); fuel != fuels.end();)
    {
        if (SDL_HasIntersectionF(&fuel->rect, &phitbox))
        {
            fuel = fuels.erase(fuel);
            energyBar.w += 30;
            if (energyBar.w > 200) energyBar.w = 200;
        }
        else
            ++fuel;
    }
}

int main(int argc, char *args[])
{

    //initialization
    SDL_Window *gWindow = SDL_CreateWindow("space", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 600, 0);
    SDL_Renderer *gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(128);

    TTF_Init();
    TTF_Font* gFont = TTF_OpenFont("font.otf", 16);
    SDL_Color textColor = {255, 255, 255};
    
    //sound
    Mix_Chunk* shootSound = Mix_LoadWAV("sound/shoot.mp3");

    // player
    SDL_Surface *newSurface = IMG_Load("img/sship.png");
    SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 255, 255, 255));
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(gRenderer, newSurface);
    SDL_FreeSurface(newSurface);
    SDL_FRect r1 = {r1.x = 500, r1.y = 500, r1.w = 100, r1.h = 70};

    // background
    SDL_Surface *newSurface2 = IMG_Load("img/background.png");
    SDL_Texture *newTexture2 = SDL_CreateTextureFromSurface(gRenderer, newSurface2);
    SDL_FreeSurface(newSurface2);
    SDL_FRect r2 = {r2.x = 0, r2.y = -600, r2.w = 960, r2.h = 600};
    SDL_FRect r3 = {r3.x = 0, r3.y = 0, r3.w = 960, r3.h = 600};

    // bullet
    SDL_Surface *newSurface3 = IMG_Load("img/bullet3.png");
    SDL_SetColorKey(newSurface3, SDL_TRUE, SDL_MapRGB(newSurface3->format, 255, 255, 255));
    SDL_Texture *newTexture3 = SDL_CreateTextureFromSurface(gRenderer, newSurface3);
    SDL_FreeSurface(newSurface3);

    // enemy1
    SDL_Surface *newSurface4 = IMG_Load("img/enemy1.png");
    SDL_SetColorKey(newSurface4, SDL_TRUE, SDL_MapRGB(newSurface4->format, 255, 255, 255));
    SDL_Texture *newTexture4 = SDL_CreateTextureFromSurface(gRenderer, newSurface4);
    SDL_FreeSurface(newSurface4);

    // New cursor
    SDL_Surface *newSurface5 = IMG_Load("img/crosshair.png");
    SDL_SetColorKey(newSurface5, SDL_TRUE, SDL_MapRGB(newSurface5->format, 0, 255, 0));
    SDL_Cursor *cursor = SDL_CreateColorCursor(newSurface5, 15, 15);
    SDL_FreeSurface(newSurface5);
    SDL_SetCursor(cursor);

    // enemy2
    SDL_Surface *newSurface6 = IMG_Load("img/enemy2.png");
    SDL_SetColorKey(newSurface6, SDL_TRUE, SDL_MapRGB(newSurface6->format, 255, 255, 255));
    SDL_Texture *newTexture6 = SDL_CreateTextureFromSurface(gRenderer, newSurface6);
    SDL_FreeSurface(newSurface6);

    // enemy3
    SDL_Surface *newSurface7 = IMG_Load("img/enemy3.png");
    SDL_SetColorKey(newSurface7, SDL_TRUE, SDL_MapRGB(newSurface7->format, 255, 255, 255));
    SDL_Texture *newTexture7 = SDL_CreateTextureFromSurface(gRenderer, newSurface7);
    SDL_FreeSurface(newSurface7);

    // bullet2
    SDL_Surface *newSurface8 = IMG_Load("img/bullet2.png");
    SDL_SetColorKey(newSurface8, SDL_TRUE, SDL_MapRGB(newSurface8->format, 0, 255, 0));
    SDL_Texture *newTexture8 = SDL_CreateTextureFromSurface(gRenderer, newSurface8);
    SDL_FreeSurface(newSurface8);

    //energyBar
    SDL_Surface  *newSurface9 = IMG_Load("img/energy.png");
    SDL_Texture *newTexture9 = SDL_CreateTextureFromSurface(gRenderer, newSurface9);
    SDL_FreeSurface(newSurface9);

    //hpBar
    SDL_Surface *newSurface10 = IMG_Load("img/hp.png");
    SDL_Texture *newTexture10 = SDL_CreateTextureFromSurface(gRenderer, newSurface10);
    SDL_FreeSurface(newSurface10);

    //fuel
    SDL_Surface *newSurface11 = IMG_Load("img/fuel.png");
    SDL_SetColorKey(newSurface11, SDL_TRUE, SDL_MapRGB(newSurface11->format, 0, 255, 0));
    SDL_Texture *newTexture11 = SDL_CreateTextureFromSurface(gRenderer, newSurface11);
    SDL_FreeSurface(newSurface11);

    float x_vel = 0;
    float y_vel = 0;
    float x = 3;
    float n = 0;
    float mouseX;
    float mouseY;
    float Angle;
    float spawnRate = 0;
    float fireRate = 0;
    float playerFireRate = 0;
    int scollingOffset = 1;
    bool shot = false;
    bool slow = false;
    int Time = 0;

    bool running = true;
    SDL_Event e;
    while (running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || playerhp < 1)
            {
                running = false;
                std::cout << "Your score is:"
                          << " " << score;
            }
            else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                if (e.key.keysym.sym == SDLK_w)
                    y_vel -= x;
                else if (e.key.keysym.sym == SDLK_s)
                    y_vel += x;
                else if (e.key.keysym.sym == SDLK_a)
                    x_vel -= x;
                else if (e.key.keysym.sym == SDLK_d)
                    x_vel += x;
                else if (e.key.keysym.sym == SDLK_e)
                {
                    float n = 640;
                    float spawnX = n * rand() / RAND_MAX;
                    float spawnY = 0;
                    float angle3 = atan2(r1.y - spawnY, r1.x - spawnX);
                    spawnEnemy(spawnX, spawnY, angle3);
                }
                else if (e.key.keysym.sym == SDLK_LSHIFT)
                {
                    slow = true;
                }
            }
            else if (e.type == SDL_KEYUP && e.key.repeat == 0)
            {
                if (e.key.keysym.sym == SDLK_w)
                    y_vel += x;
                else if (e.key.keysym.sym == SDLK_s)
                    y_vel -= x;
                else if (e.key.keysym.sym == SDLK_a)
                    x_vel += x;
                else if (e.key.keysym.sym == SDLK_d)
                    x_vel -= x;
                else if (e.key.keysym.sym == SDLK_LSHIFT)
                {
                    slow = false;
                }
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                mouseX = e.motion.x;
                mouseY = e.motion.y;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {

                    shot = true;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    shot = false;
                }
            }
        }
        // Manage skill
        if (slow == true && energyBar.w > 0)
        {
            energyBar.w--;
            s = 0.1;
        }
        else
            s = 1;

        // Control
        r1.x += x_vel;
        r1.y += y_vel;
        if (r1.x < -20 || r1.x > 880)
        {
            r1.x -= x_vel;
        }
        if (r1.y < -10 || r1.y > 540)
        {
            r1.y -= y_vel;
        }

        // Manage shooting
        playerFireRate++;
        if (shot)
        {
            if (playerFireRate >= 4)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                float angle2 = atan2((float)mouseY - r1.y - 35, (float)mouseX - r1.x - 50);
                shootBullet(r1.x + 37, r1.y + 30, angle2);
                Mix_PlayChannel(-1, shootSound, 0);
                playerFireRate = 0;
            }
        }

        // Manage scolling background
        r2.y += 1 ;
        r3.y += 1 ;
        if (r2.y >= 600)
            r2.y = -600;
        if (r3.y >= 600)
            r3.y = -600;
        
        //spawn enemy
        fireRate += 1 * s;
        Time += 1 * s;
        spawnRate += 1 * s;
        if (spawnRate > 5)
        {
            int f = rand() % 100;
            if (f < 65)
            {
                float spawnX = 950 * rand() / RAND_MAX;
                float spawnY = -100;
                float angle = atan2(r1.y - spawnY, r1.x - spawnX);
                spawnEnemy(spawnX, spawnY, angle);
                spawnRate = 0;
            }
            if (f >= 65 && f < 95 && Time > 400)
            {
                float spawnX = 950 * rand() / RAND_MAX;
                float spawnY = -100;
                float angle = atan2(r1.y - spawnY, r1.x - spawnX);
                spawnEnemy2(spawnX, spawnY, angle);
                spawnRate = 0;
            }
            if (f >= 95 && Time > 800)
            {
                float spawnX = 950 * rand() / RAND_MAX;
                float spawnY = -100;
                float angle = atan2(r1.y - spawnY, r1.x - spawnX);
                spawnEnemy3(spawnX, spawnY, angle);
                spawnRate = 0;
            }
        }

        if (fireRate > 30)
        {
            for (auto &enemy3 : enemies3)
            {
                float angle1 = enemy3.angle + (M_PI / 4);
                float angle2 = enemy3.angle + (3 * M_PI / 4);
                float angle3 = enemy3.angle - (M_PI / 4);
                float angle4 = enemy3.angle - (3 * M_PI / 4);
                spawnEnemyBullet(enemy3.rect.x + 25, enemy3.rect.y + 25, angle1);
                spawnEnemyBullet(enemy3.rect.x + 25, enemy3.rect.y + 25, angle2);
                spawnEnemyBullet(enemy3.rect.x + 25, enemy3.rect.y + 25, angle3);
                spawnEnemyBullet(enemy3.rect.x + 25, enemy3.rect.y + 25, angle4);
            }
            fireRate = 0;
        }

        updateEnemyBullets();
        updateEnemies3();
        updateEnemies();
        updateEnemies2();
        updateBullets();
        updateFuel();

        Angle = atan2(((double)mouseY - r1.y - 35), ((double)mouseX - r1.x - 50)) * (180 / M_PI);

        for (auto enemy = enemies.begin(); enemy != enemies.end();)
        {
            enemy->hitbox.x = enemy->rect.x + 15;
            enemy->hitbox.y = enemy->rect.y + 15;
            enemy->hitbox.w = enemy->rect.w - 15;
            enemy->hitbox.h = enemy->rect.h - 15;
            if (enemy->rect.y > 600 || enemy->rect.x < -100 || enemy->rect.x > 960)
            {
                enemy = enemies.erase(enemy);
            }
            else
                ++enemy;
        }

        for (auto enemy2 = enemies2.begin(); enemy2 != enemies2.end();)
        {
            enemy2->hitbox.x = enemy2->rect.x + 10;
            enemy2->hitbox.y = enemy2->rect.y + 10;
            enemy2->hitbox.w = enemy2->rect.w - 10;
            enemy2->hitbox.h = enemy2->rect.h - 10;
            if (enemy2->rect.y > 600 || enemy2->rect.x < -100 || enemy2->rect.x > 960)
            {
                enemy2 = enemies2.erase(enemy2);
            }
            else
                ++enemy2;
        }

        for (auto enemy3 = enemies3.begin(); enemy3 != enemies3.end();)
        {
            enemy3->hitbox.x = enemy3->rect.x + 10;
            enemy3->hitbox.y = enemy3->rect.y + 10;
            enemy3->hitbox.w = enemy3->rect.w - 10;
            enemy3->hitbox.h = enemy3->rect.h - 10;
            if (enemy3->rect.y > 600 || enemy3->rect.x < -100 || enemy3->rect.x > 960)
            {
                enemy3 = enemies3.erase(enemy3);
            }
            else
                ++enemy3;
        }

        for (auto bullet = bullets.begin(); bullet != bullets.end();)
        {
            if (bullet->rect.y > 600 || bullet->rect.y < -100 || bullet->rect.x < -100 || bullet->rect.x > 960)
            {
                bullet = bullets.erase(bullet);
            }
            else
                bullet++;
        }

        for (auto enemyBullet = enemyBullets.begin(); enemyBullet != enemyBullets.end();)
        {
            if (enemyBullet->rect.y > 600 || enemyBullet->rect.y < -100 || enemyBullet->rect.x < -100 || enemyBullet->rect.x > 960)
            {
                enemyBullet = enemyBullets.erase(enemyBullet);
            }
            enemyBullet++;
        }

        // Update player hitbox;
        phitbox.x = r1.x + 50;
        phitbox.y = r1.y + 32.5;
        phitbox.w = 5;
        phitbox.h = 5;

        checkCollisions();
        checkplayercollsion();

        //update player hp bar;
        hpBar.w = playerhp*40;

        //update score
        string _score = to_string(score);
        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, _score.c_str(), textColor);
        SDL_Rect textRect = {20, 15, textSurface->w, textSurface->h};
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_FreeSurface(textSurface);

        //Render
        SDL_RenderClear(gRenderer);
        SDL_RenderCopyF(gRenderer, newTexture2, NULL, &r2);
        SDL_RenderCopyF(gRenderer, newTexture2, NULL, &r3);
        SDL_RenderFillRectF(gRenderer, &phitbox);
        SDL_RenderCopyExF(gRenderer, newTexture, NULL, &r1, Angle, NULL, SDL_FLIP_NONE);
        for (auto &bullet : bullets)
        {
            SDL_RenderCopyExF(gRenderer, newTexture3, NULL, &bullet.rect, bullet.angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
        }
        for (auto &fuel : fuels)
        {
            SDL_RenderCopyF(gRenderer, newTexture11, NULL, &fuel.rect);
        }
        for (auto &enemy : enemies)
        {
            SDL_RenderCopyExF(gRenderer, newTexture4, NULL, &enemy.rect, enemy.angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
        }
        for (auto &enemy2 : enemies2)
        {
            float angle = atan2(r1.y - enemy2.rect.y, r1.x - enemy2.rect.x);
            enemy2.angle = angle;
            SDL_RenderCopyExF(gRenderer, newTexture6, NULL, &enemy2.rect, enemy2.angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
        }
        for (auto &enemy3 : enemies3)
        {
            SDL_RenderCopyExF(gRenderer, newTexture7, NULL, &enemy3.rect, enemy3.angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
        }
        for (auto &enemyBullet : enemyBullets)
        {
            SDL_RenderCopyExF(gRenderer, newTexture8, NULL, &enemyBullet.rect, enemyBullet.angle * (180 / M_PI), NULL, SDL_FLIP_NONE);
        }
        SDL_RenderFillRect(gRenderer, &_energyBar);
        SDL_RenderCopyF(gRenderer, newTexture9, NULL, &energyBar);
        SDL_RenderFillRect(gRenderer, &_hpBar);
        SDL_RenderCopy(gRenderer, newTexture10, NULL, &hpBar);
        SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();

    r1.x = 30;
    r1.y = 30;

    return 0;
}
