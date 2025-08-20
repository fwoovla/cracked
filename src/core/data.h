#pragma once

#include <raylib.h>
#include <vector>
#include <string>



enum PART_TYPE {
    TYPE_MAIN_GUN,
    TYPE_THRUSTERS,
};

/* struct SHIP_PART {
  PART_TYPE type;
}; */

struct PART_MAIN_GUN{
    std::string part_name = "S.A.D. 1k";
    float weight = 4.6f;
    float GUN_MAX_POWER = 10.0f;
    float GUN_POWER_USE = 1.0f;
    float GUN_REGEN = 3.0f;
    float GUN_DELAY = 0.2f;
};

struct PART_THRUSTERS{
    std::string part_name = "ForWARD 20.1 kV";
    float weight = 10.0f;
    float THRUSTER_SPEED = 3.0f;
    float THRUSTER_SHIP_THRUST = 0.1f;
    float THRUSTER_SHIP_ROT_SPEED = 180.0f;
};


struct PlayerData {
    int id = 1;
    float SPEED = 3.0f;
    float SIZE = 30;
    float SHIP_THRUST = 0.1f;
    float SHIP_ROT_SPEED = 180.0f;
    float AIR_FRICTION = 0.99f;
    float SHIP_BOUNCE_SCALEAR = 0.6f;
    float GUN_MAX_POWER = 10.0f;
    float GUN_POWER_USE = 1.0f;
    float GUN_REGEN = 3.0f;
    float GUN_DELAY = 0.2f;
    int MAX_HEALTH = 10;

    float gun_power = GUN_MAX_POWER;
    int shots = 0;
    int health = MAX_HEALTH;
    int points = 0;
    int scrap_amount = 0;

    //std::vector<SHIP_PART> ship_parts;

    PART_MAIN_GUN main_gun_part;
    PART_THRUSTERS thrusters_part;

};


struct EnemyData {
    int id = GetRandomValue(1000, 100000);
    int TYPE;
    float SPEED = 3.0;
    float SIZE = 30;
    float SHIP_THRUST = 0.1f;
    float SHIP_ROT_SPEED = 180.0f;
    float AIR_FRICTION = 0.99f;
    float SHIP_BOUNCE_SCALEAR = 0.6f;
    float MIN_THRUST_TIME = 50.0f;
    float MAX_THRUST_TIME = 150.0f;
    float MIN_THRUST_WAIT = 20.0f;
    float MAX_THRUST_WAIT = 100.0f;
    float MIN_BURST_TIME = 3.0f;
    float MAX_BURST_TIME = 10.0f;
    float MIN_BURST_WAIT = 50.0f;
    float MAX_BURST_WAIT = 80.0f;
    float GUN_DELAY = 0.1f;
    int DETECT_RANGE = 4;
    float ROTATION_SPEED = PI * 0.4f;
    float SHOOT_RANGE = 150000.0f;
    Texture2D texture;
    int MAX_HEALTH = 1;

    int health = MAX_HEALTH;
    int shots = 0;
};