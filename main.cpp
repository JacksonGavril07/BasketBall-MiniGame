#include "raylib.h"
#include "raymath.h"

#include <cmath>
#include <stdexcept>
#include <string>

// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

const float INITIAL_BALL_X = 25.0f;
const float INITIAL_BALL_Y = 375.0f;
const float GRAVITY = 500.0f;

const float BALL_RADIUS = 12.0f;
const float HOOP_RADIUS = 16.0f;

const float INITIAL_SHOT_ANGLE = 45.0f;
const float INITIAL_SHOT_POWER = 200.0f;
const float SHOT_LINE_SCALE = 0.25f;

const float MIN_SHOT_ANGLE = 10.0f;
const float MAX_SHOT_ANGLE = 80.0f;
const float MIN_SHOT_POWER = 100.0f;
const float MAX_SHOT_POWER = 700.0f;

const float ANGLE_ADJUST_SPEED = 120.0f; // degrees per second while holding arrow keys
const float POWER_ADJUST_SPEED = 200.0f; // units per second while holding arrow keys

const float INITIAL_TIMER = 60.0f;

// -----------------------------------------------------------------------------
// Globals
// -----------------------------------------------------------------------------

Texture2D ballTexture {};
Texture2D hoopTexture {};

Vector2 ballPos {};
Vector2 ballVel {};
Vector2 hoopPos {};
Vector2 shotVector {};

bool isFlying = false;
float shotAngle = INITIAL_SHOT_ANGLE;
float shotPower = INITIAL_SHOT_POWER;
int score = 0;
float timer = INITIAL_TIMER;

// -----------------------------------------------------------------------------
// Helper functions
// -----------------------------------------------------------------------------

static void ResetBall()
{
    ballPos = {INITIAL_BALL_X, INITIAL_BALL_Y};
    ballVel = {0.0f, 0.0f};
    isFlying = false;
}

static void RandomizeHoopPosition()
{
    const int minX = SCREEN_WIDTH / 2;
    const int maxX = SCREEN_WIDTH - 50;
    const int minY = 60;
    const int maxY = SCREEN_HEIGHT - 80;

    hoopPos.x = static_cast<float>(GetRandomValue(minX, maxX));
    hoopPos.y = static_cast<float>(GetRandomValue(minY, maxY));
}

static void UpdateShotVector()
{
    shotVector = {0.0f, -shotPower};
    shotVector = Vector2Rotate(shotVector, DEG2RAD * shotAngle);
}

// -----------------------------------------------------------------------------
// Game loop functions
// -----------------------------------------------------------------------------

void UpdateFrame()
{
    float deltaTime = GetFrameTime();

    if (timer <= 0.0f) {
        return;
    }

    timer -= deltaTime;
    if (timer <= 0.0f) {
        timer = 0.0f;
        ResetBall();
        return;
    }

    if (isFlying) {
        ballVel.y += GRAVITY * deltaTime;
        ballPos.x += ballVel.x * deltaTime;
        ballPos.y += ballVel.y * deltaTime;

        if (ballPos.y >= INITIAL_BALL_Y) {
            ResetBall();
            return;
        }

        bool madeShot = CheckCollisionCircles(ballPos, BALL_RADIUS, hoopPos, HOOP_RADIUS);
        if (madeShot) {
            score += 1;
            ResetBall();
            RandomizeHoopPosition();
        }
    }
    else {
        ballPos = {INITIAL_BALL_X, INITIAL_BALL_Y};

        if (IsKeyDown(KEY_LEFT)) {
            shotAngle -= ANGLE_ADJUST_SPEED * deltaTime;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            shotAngle += ANGLE_ADJUST_SPEED * deltaTime;
        }
        if (shotAngle < MIN_SHOT_ANGLE)
            shotAngle = MIN_SHOT_ANGLE;
        if (shotAngle > MAX_SHOT_ANGLE)
            shotAngle = MAX_SHOT_ANGLE;

        if (IsKeyDown(KEY_DOWN)) {
            shotPower -= POWER_ADJUST_SPEED * deltaTime;
        }
        if (IsKeyDown(KEY_UP)) {
            shotPower += POWER_ADJUST_SPEED * deltaTime;
        }
        if (shotPower < MIN_SHOT_POWER)
            shotPower = MIN_SHOT_POWER;
        if (shotPower > MAX_SHOT_POWER)
            shotPower = MAX_SHOT_POWER;

        UpdateShotVector();

        if (IsKeyPressed(KEY_SPACE)) {
            isFlying = true;
            ballVel = shotVector;
        }
    }
}

void DrawFrame()
{
    DrawText("Arrow keys aim/power. Press SPACE to shoot.", 10, 10, 12, DARKGRAY);

    std::string scoreStr = "Score: " + std::to_string(score);
    DrawText(scoreStr.c_str(), 325, 10, 12, BLACK);

    int timeDisplay = static_cast<int>(std::ceil(timer));
    if (timeDisplay < 0)
        timeDisplay = 0;
    std::string timerStr = "Time: " + std::to_string(timeDisplay);
    DrawText(timerStr.c_str(), 10, 28, 12, BLACK);

    if (!isFlying && timer > 0.0f) {
        Vector2 scaledShot = Vector2Scale(shotVector, SHOT_LINE_SCALE);
        Vector2 lineEnd = Vector2Add(ballPos, scaledShot);
        DrawLineEx(ballPos, lineEnd, 2.0f, RED);
    }

    Vector2 hoopDrawPos = {hoopPos.x - hoopTexture.width * 0.5f, hoopPos.y - hoopTexture.height * 0.5f};
    DrawTextureEx(hoopTexture, hoopDrawPos, 0.0f, 1.0f, WHITE);

    Vector2 ballDrawPos = {ballPos.x - ballTexture.width * 0.5f, ballPos.y - ballTexture.height * 0.5f};
    DrawTextureEx(ballTexture, ballDrawPos, 0.0f, 1.0f, WHITE);

    if (timer <= 0.0f) {
        const char* gameOverText = "Game Over!";
        int textWidth = MeasureText(gameOverText, 24);
        DrawText(gameOverText, SCREEN_WIDTH / 2 - textWidth / 2, SCREEN_HEIGHT / 2 - 20, 24, MAROON);
    }
}

// -----------------------------------------------------------------------------
// Entry point
// -----------------------------------------------------------------------------

void Startup()
{
    ballTexture = LoadTexture("assets/basketball.png");
    if (!ballTexture.id) {
        throw std::runtime_error("Failed to load basketball texture.");
    }

    hoopTexture = LoadTexture("assets/hoop.png");
    if (!hoopTexture.id) {
        throw std::runtime_error("Failed to load hoop texture.");
    }

    ResetBall();
    RandomizeHoopPosition();
    UpdateShotVector();
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basketball");
    SetTargetFPS(60);

    Startup();

    while (!WindowShouldClose()) {
        UpdateFrame();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFrame();
        EndDrawing();
    }

    UnloadTexture(ballTexture);
    UnloadTexture(hoopTexture);
    CloseWindow();

    return 0;
}

