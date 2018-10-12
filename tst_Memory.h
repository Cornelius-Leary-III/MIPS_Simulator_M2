#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Memory.h"

using namespace testing;

TEST(Memory, constructor)
{
    Memory testMemory;

    auto testMemoryVector = testMemory.getMemory();
    EXPECT_TRUE(testMemoryVector.empty());
}

TEST(Memory, addByteToMemory_single_pass)
{
    Memory testMemory;
    uint8_t testByte = '1';

    EXPECT_TRUE(testMemory.addByteToMemory(testByte));

    auto testMemoryVector = testMemory.getMemory();
    EXPECT_EQ(testMemoryVector.size(), 1);

    auto memIter = testMemoryVector.begin();
    EXPECT_EQ(*memIter, testByte);
}

TEST(Memory, addByteToMemory_multiple_pass)
{
    Memory testMemory;

    uint8_t testByte = '1';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte));

    uint8_t testByte2 = '2';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte2));

    uint8_t testByte3 = '8';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte3));

    auto testMemoryVector = testMemory.getMemory();
    EXPECT_EQ(testMemoryVector.size(), 3);

    auto memIter = testMemoryVector.begin();
    EXPECT_EQ(*memIter, testByte);

    ++memIter;
    EXPECT_EQ(*memIter, testByte2);

    ++memIter;
    EXPECT_EQ(*memIter, testByte3);
}

TEST(Memory, updateMemory_pass)
{
    Memory testMemory;

    uint8_t testByte = '1';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte));

    uint8_t testByte2 = '2';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte2));

    uint8_t testByte3 = '8';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte3));

    uint8_t replacementByte = '5';
    unsigned replacementIndex = 1;
    testMemory.updateMemory(replacementIndex, replacementByte);

    auto testMemoryVector = testMemory.getMemory();
    EXPECT_EQ(testMemory.getMemorySize(), 3);

    auto memIter = testMemoryVector.begin();
    EXPECT_EQ(*memIter, testByte);

    ++memIter;
    EXPECT_EQ(*memIter, replacementByte);

    ++memIter;
    EXPECT_EQ(*memIter, testByte3);
}

TEST(Memory, getByteFromMemory_pass)
{
    Memory testMemory;

    uint8_t testByte = '1';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte));

    uint8_t testByte2 = '2';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte2));

    uint8_t testByte3 = '8';
    EXPECT_TRUE(testMemory.addByteToMemory(testByte3));

    uint8_t replacementByte = '5';
    unsigned replacementIndex = 1;
    testMemory.updateMemory(replacementIndex, replacementByte);

    auto testMemoryVector = testMemory.getMemory();
    EXPECT_EQ(testMemory.getMemorySize(), 3);

    auto memIter = testMemoryVector.begin();
    EXPECT_EQ(*memIter, testByte);

    ++memIter;
    EXPECT_EQ(*memIter, replacementByte);

    ++memIter;
    EXPECT_EQ(*memIter, testByte3);

    EXPECT_EQ(testMemory.getByteFromMemory(0), testByte);
    EXPECT_EQ(testMemory.getByteFromMemory(1), replacementByte);
    EXPECT_EQ(testMemory.getByteFromMemory(2), testByte3);
    EXPECT_EQ(testMemory.getByteFromMemory(5), '*');
}
