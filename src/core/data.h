#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

struct ShipData {
    std::string ship_name = "";
    float capacity;

};

enum PART_TYPE {
    TYPE_MAIN_GUN,
    TYPE_THRUSTERS,
};

struct PartMainGun{
    std::string part_name = "";
    float weight;
    float GUN_MAX_POWER;
    float GUN_POWER_USE;
    float GUN_REGEN;
    float GUN_DELAY;
    int cost;
};

struct PartThrusters{
    std::string part_name = "";
    float weight;
    float THRUSTER_SPEED;
    float THRUSTER_SHIP_THRUST;
    float THRUSTER_SHIP_ROT_SPEED;
    int cost;
};

struct PartArmor{
    std::string part_name = "";
    float weight;
    int ARMOR;
    int cost;
};


struct PlayerData {
    int id;

    float SIZE;

    float AIR_FRICTION;
    float SHIP_BOUNCE_SCALEAR;

    int MAX_HEALTH;

    int health;
    int shots;
    int points;
    int scrap_amount;
    float gun_power;

    PartMainGun main_gun_part;
    PartThrusters thrusters_part;
    PartArmor armor_part;

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

extern std::unordered_map<int, PartMainGun> main_gun_data;
extern std::unordered_map<int, PartThrusters> thrusters_data;
extern std::unordered_map<int, PartArmor> armors_data;

inline void LoadGameData() {
    TraceLog(LOG_INFO, "LOADING GAME DATA....data.json");

    std::ifstream file("assets/data.json");
    if (!file.is_open()) {
        TraceLog(LOG_INFO, "CANNOT OPEN FILE");
        return;
    }
    

    json j;
    file>>j;
    TraceLog(LOG_INFO, "==========LOADING GAME DATA FROM FILE================");
    for(int i = 0; i < j["part_main_gun"].size(); i++) {

        std::string gun_name = "";
        float weight;
        float max_power;
        float power_use;
        float regen;
        float delay;
        int cost;

        gun_name = j["part_main_gun"][i]["part_name"];
        weight = j["part_main_gun"][i]["weight"];
        max_power = j["part_main_gun"][i]["GUN_MAX_POWER"];
        power_use = j["part_main_gun"][i]["GUN_POWER_USE"];
        regen = j["part_main_gun"][i]["GUN_REGEN"];
        delay = j["part_main_gun"][i]["GUN_DELAY"];
        cost = j["part_main_gun"][i]["cost"];

        TraceLog(LOG_INFO, "-gun name %i %s", i, gun_name.c_str());
        TraceLog(LOG_INFO, "-gun weight %f", weight);
        TraceLog(LOG_INFO, "-gun max power %f", max_power);
        TraceLog(LOG_INFO, "-gun power use %f", power_use);
        TraceLog(LOG_INFO, "-gun regen speed %f", regen);
        TraceLog(LOG_INFO, "-gun shot delay %f\n", delay);
        TraceLog(LOG_INFO, "-thruseter cost %i\n", cost);

        PartMainGun gun_data = {
            .part_name = gun_name,
            .weight = weight,
            .GUN_MAX_POWER = max_power,
            .GUN_POWER_USE = power_use,
            .GUN_REGEN = regen,
            .GUN_DELAY = delay,
            .cost = cost
        };

        main_gun_data[i] = gun_data;
    }
 
    TraceLog(LOG_INFO, "==========end main gun================");

//sdffffffffffffffffffffffffffffffffffffffffffffffffffffff

    for(int i = 0; i < j["part_thrusters"].size(); i++) {

        std::string thruster_name = "";
        float weight;
        float speed;
        float thrust;
        float rot;
        int cost;

        thruster_name = j["part_thrusters"][i]["part_name"];
        weight = j["part_thrusters"][i]["weight"];
        speed = j["part_thrusters"][i]["THRUSTER_SPEED"];
        thrust = j["part_thrusters"][i]["THRUSTER_SHIP_THRUST"];
        rot = j["part_thrusters"][i]["THRUSTER_SHIP_ROT_SPEED"];
        cost = j["part_thrusters"][i]["cost"];


        TraceLog(LOG_INFO, "-thruseter %i %s", i, thruster_name.c_str());
        TraceLog(LOG_INFO, "-thruseter weight %f", weight);
        TraceLog(LOG_INFO, "-thruseter speed %f", speed);
        TraceLog(LOG_INFO, "-thruseter thrust %f", thrust);
        TraceLog(LOG_INFO, "-thruseter rot speed %f", rot);
        TraceLog(LOG_INFO, "-thruseter cost %i\n", cost);

        PartThrusters thruster_data = {
            .part_name = thruster_name,
            .weight = weight,
            .THRUSTER_SPEED = speed,
            .THRUSTER_SHIP_THRUST = thrust,
            .THRUSTER_SHIP_ROT_SPEED = rot,
            .cost = cost
        };

        thrusters_data[i] = thruster_data;
    }

    TraceLog(LOG_INFO, "==========end thrusters================");





    for(int i = 0; i < j["part_armor"].size(); i++) {

        std::string armor_name = "";
        float weight;
        int armor;
        int cost;

        armor_name = j["part_armor"][i]["part_name"];
        weight = j["part_armor"][i]["weight"];
        armor =  j["part_armor"][i]["ARMOR"];
        cost = j["part_armor"][i]["cost"];


        TraceLog(LOG_INFO, "-armor %i %s", i, armor_name.c_str());
        TraceLog(LOG_INFO, "-armor weight %f", weight);
        TraceLog(LOG_INFO, "-armor speed %i", armor);
        TraceLog(LOG_INFO, "-armor cost %i\n", cost);

        PartArmor armor_data = {
            .part_name = armor_name,
            .weight = weight,
            .ARMOR = armor,
            .cost = cost
        };

        armors_data[i] = armor_data;
    }

    TraceLog(LOG_INFO, "==========end armor================");






    TraceLog(LOG_INFO, "DATA LOADED");
}

