//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_WORLD_H
#define CPP_WORLD_H


#include <cstdint>
#include <mutex>
#include <thread>

class World {
public:
    static World& getInstance();
    uint32_t get_point_count() const;
    void inc_point_count();

private:
    World();
    virtual ~World();
    std::mutex _m;
    uint32_t _point_count;
};


#endif //CPP_WORLD_H
