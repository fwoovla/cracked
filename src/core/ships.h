#include "baseship.h"

class PlayerShip : public BaseShip {
    public:
    PlayerShip();
    ~PlayerShip();
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(Vector4 &collision_data, int *level_array) override;

    Sprite sprite;
    Rectangle collision_rect;
    bool player_collided;

};