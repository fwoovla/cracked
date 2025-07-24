#include "baseship.h"

class PlayerShip : public BaseShip {
    public:
    PlayerShip(Vector2 _position);
    ~PlayerShip();
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(Vector4 &collision_data, int *level_array) override;
    void DoMovement(float dt, int *level_array);

    Sprite sprite;
    Rectangle collision_rect;
    bool player_collided;

    Vector2 velocity;
    Vector2 position;
    float rotation;
    Vector2 centered_offset;

    Texture2D turret_texture;
    Sprite turret;
    Camera2D *camera;


};

/* 

float thrust = 0.1f;
float rotationSpeed = 180.0f; // degrees per second
float friction = 0.99f;

if (IsKeyDown(KEY_LEFT))  rotation -= rotationSpeed * deltaTime;
if (IsKeyDown(KEY_RIGHT)) rotation += rotationSpeed * deltaTime;

if (IsKeyDown(KEY_UP)) {
    // Convert angle to radians
    float rad = rotation * DEG2RAD;
    // Apply acceleration in facing direction
    velocity.x += cosf(rad) * thrust;
    velocity.y += sinf(rad) * thrust;
}

// Apply friction
velocity.x *= friction;
velocity.y *= friction;

// Update position
position.x += velocity.x;
position.y += velocity.y;

// Screen wrapping
if (position.x < 0) position.x = screenWidth;
if (position.x > screenWidth) position.x = 0;
if (position.y < 0) position.y = screenHeight;
if (position.y > screenHeight) position.y = 0;



 */