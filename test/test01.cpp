#include <gtest/gtest.h>
#include "NPC.h"
#include "utils.h"

TEST(NPCTest, CreationAndMovement) {
    NPC npc(NPCType::Druid, 10, 20);
    
    EXPECT_EQ(npc.getType(), NPCType::Druid);
    EXPECT_EQ(npc.getX(), 10);
    EXPECT_EQ(npc.getY(), 20);
    EXPECT_TRUE(npc.isAlive());
    
    npc.move(30, 40);
    EXPECT_EQ(npc.getX(), 30);
    EXPECT_EQ(npc.getY(), 40);
}

TEST(NPCTest, Kill) {
    NPC npc(NPCType::Orc, 0, 0);
    EXPECT_TRUE(npc.isAlive());
    
    npc.kill();
    EXPECT_FALSE(npc.isAlive());
}

TEST(NPCTest, Distances) {
    NPC druid(NPCType::Druid, 0, 0);
    EXPECT_EQ(druid.getMoveDistance(), 10);  // Проверка для Друида
    EXPECT_EQ(druid.getKillDistance(), 10);
    
    NPC dragon(NPCType::Dragon, 0, 0);
    EXPECT_EQ(dragon.getMoveDistance(), 50);
    EXPECT_EQ(dragon.getKillDistance(), 30);
}

TEST(UtilsTest, RandomNPCType) {
    NPCType type = utils::randomNPCType();
    EXPECT_GE(type, NPCType::Orc);
    EXPECT_LE(type, NPCType::Bull);
}

TEST(UtilsTest, TypeToString) {
    EXPECT_EQ(utils::npcTypeToString(NPCType::Druid), "Druid");
    EXPECT_EQ(utils::npcTypeToString(NPCType::Dragon), "Dragon");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
