#pragma once

const int MAP_W = 40;
const int MAP_H = 23;

const float MAP_CHIP_SIZE = 32.f;

const float GRAVITY = 0.1f;
const float WEIGHT = 1.f;

// 空気抵抗を考慮しての最高速度を考える
const float MAX_SPEED = 6.f;

// 摩擦は最終的にブロックに持たせたい
const float FRICTION = 0.15f;