#include "baseship.h"
#include "../utils/utils.h"
#include "global_types.h"


#define PLAYER_SPEED 1.5f
#define PLAYER_SIZE 30
#define COLLISION_RANGE 3
#define SHIP_THRUST 0.02f
#define SHIP_ROT_SPEED 90.0f
#define AIR_FRICTION 0.99f


class PlayerShip : public BaseShip, public SignalObserver {
    public:
    PlayerShip(Vector2 _position);
    ~PlayerShip() override;
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(collisionResult &collision_data) override;
    void DoMovement(float dt, int *level_array);
    void DoWeapons();
    void OnSignal(SIGNAL signal) override;

    
    Rectangle collision_rect;
    bool collided;

    Vector2 velocity;
    Vector2 position;
    float rotation;
    Vector2 centered_offset;

    Texture2D turret_texture;
    Sprite turret;
    Camera2D *camera;

    Timer *gun_timer;
    bool can_fire;

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