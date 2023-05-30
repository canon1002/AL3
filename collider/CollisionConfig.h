#pragma once

#include<cstdint>

// ・・・・・ｬ・・､・・､・・ｼ・・｣・・ｶ
const uint32_t kCollisionAttributePlayer = 0b1;
// ・・ｵ・・｣・・ｶ
const uint32_t kCollisionAttributeEnemy = 0b1 << 1;
// ・ｱ・・ｧ (・・ｪ・・・・・ｮ・ｼｾ)
const uint32_t kCollisionAttributePlayerBullet = 0b1 << 2;
// ・ｱ・・ｧ (・・ｵ・・ｮ・ｼｾ)
const uint32_t kCollisionAttributeEnemyBullet = 0b1 << 3;
// ・ｱ・・ｧ (・ｹｲ・ｸ・・・ｯ・・ｽ・ｼｾ)
const uint32_t kCollisionAttributeHitBullet = 0b1 << 4;
