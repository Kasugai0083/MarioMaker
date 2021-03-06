#pragma once

// マップの最大サイズ
const int MAX_MAP_W = 80;
const int MAX_MAP_H = 23;

const float MAP_CHIP_SIZE = 32.f;

const float GRAVITY = 0.3f;
const float WEIGHT = 1.f;

// 空気抵抗を考慮しての最高速度を考える
const float MAX_SPEED = 6.f;

// 摩擦は最終的にブロックに持たせたい
const float FRICTION = 0.3f;

// 死亡アニメーションの長さ
const int DEATH_ANIMATION_TIME = 180;
// 死亡アニメーションが開始するまでの時間
const int DEATH_WAIT = 16;