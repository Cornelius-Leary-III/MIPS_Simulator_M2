#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Registers.h"

using namespace testing;

TEST(Registers, constructor)
{
    Registers testRegisters;
    auto testRegistersMap = testRegisters.getRegisters();
    EXPECT_TRUE(testRegistersMap.empty());
}

TEST(Registers, addRegister_single_pass)
{
    Registers testRegisters;

    string testNameA = "$t0";
    int testValueA = 0;
    EXPECT_TRUE(testRegisters.addRegister(testNameA, testValueA));

    auto registersMap = testRegisters.getRegisters();
    auto registerIter = registersMap.begin();

    EXPECT_EQ(registersMap.size(), 1);
    EXPECT_EQ(registerIter->first, testNameA);
    EXPECT_EQ(registerIter->second, testValueA);
}

TEST(Registers, addRegister_multiple_pass)
{
    Registers testRegisters;

    string testNameA = "$t0";
    int testValueA = 0;
    EXPECT_TRUE(testRegisters.addRegister(testNameA, testValueA));

    string testNameB = "$pc";
    int testValueB = -10;
    EXPECT_TRUE(testRegisters.addRegister(testNameB, testValueB));

    string testNameC = "$31";
    int testValueC = 4;
    EXPECT_TRUE(testRegisters.addRegister(testNameC, testValueC));

    auto registersMap = testRegisters.getRegisters();
    auto registerIter = registersMap.begin();

    EXPECT_EQ(registersMap.size(), 3);
    EXPECT_EQ(registerIter->first, testNameC);
    EXPECT_EQ(registerIter->second, testValueC);

    ++registerIter;
    EXPECT_EQ(registerIter->first, testNameB);
    EXPECT_EQ(registerIter->second, testValueB);

    ++registerIter;
    EXPECT_EQ(registerIter->first, testNameA);
    EXPECT_EQ(registerIter->second, testValueA);
}

TEST(Registers, updateRegister_pass)
{
    Registers testRegisters;

    string testNameA = "$t0";
    int testValueA = 0;
    EXPECT_TRUE(testRegisters.addRegister(testNameA, testValueA));

    string testNameB = "$pc";
    int testValueB = -10;
    EXPECT_TRUE(testRegisters.addRegister(testNameB, testValueB));

    string testNameC = "$31";
    int testValueC = 4;
    EXPECT_TRUE(testRegisters.addRegister(testNameC, testValueC));

    int replacementValue = -8;
    EXPECT_TRUE(testRegisters.updateRegister(testNameC, replacementValue));

    string newNameD = "$h2";
    int newValueD = 9;
    EXPECT_TRUE(testRegisters.updateRegister(newNameD, newValueD));

    auto registersMap = testRegisters.getRegisters();
    EXPECT_EQ(registersMap.size(), 4);

    auto registerLookupIter = registersMap.find(newNameD);
    EXPECT_EQ(registerLookupIter->first, newNameD);
    EXPECT_EQ(registerLookupIter->second, newValueD);

    registerLookupIter = registersMap.find(testNameA);
    EXPECT_EQ(registerLookupIter->first, testNameA);
    EXPECT_EQ(registerLookupIter->second, testValueA);

    registerLookupIter = registersMap.find(testNameB);
    EXPECT_EQ(registerLookupIter->first, testNameB);
    EXPECT_EQ(registerLookupIter->second, testValueB);

    registerLookupIter = registersMap.find(testNameC);
    EXPECT_EQ(registerLookupIter->first, testNameC);
    EXPECT_EQ(registerLookupIter->second, replacementValue);
}

TEST(Registers, lookupRegister_pass)
{
    Registers testRegisters;

    string testNameA = "$t0";
    int testValueA = 0;
    EXPECT_TRUE(testRegisters.addRegister(testNameA, testValueA));

    string testNameB = "$pc";
    int testValueB = -10;
    EXPECT_TRUE(testRegisters.addRegister(testNameB, testValueB));

    string testNameC = "$31";
    int testValueC = 4;
    EXPECT_TRUE(testRegisters.addRegister(testNameC, testValueC));

    int replacementValue = -8;
    EXPECT_TRUE(testRegisters.updateRegister(testNameC, replacementValue));

    string newNameD = "$h2";
    int newValueD = 9;
    EXPECT_TRUE(testRegisters.updateRegister(newNameD, newValueD));

    auto registersMap = testRegisters.getRegisters();
    EXPECT_EQ(registersMap.size(), 4);

    auto registerLookupIter = testRegisters.lookupRegister(newNameD);
    EXPECT_EQ(registerLookupIter->first, newNameD);
    EXPECT_EQ(registerLookupIter->second, newValueD);

    registerLookupIter = testRegisters.lookupRegister(testNameA);
    EXPECT_EQ(registerLookupIter->first, testNameA);
    EXPECT_EQ(registerLookupIter->second, testValueA);

    registerLookupIter = testRegisters.lookupRegister(testNameB);
    EXPECT_EQ(registerLookupIter->first, testNameB);
    EXPECT_EQ(registerLookupIter->second, testValueB);

    registerLookupIter = testRegisters.lookupRegister(testNameC);
    EXPECT_EQ(registerLookupIter->first, testNameC);
    EXPECT_EQ(registerLookupIter->second, replacementValue);
}

TEST(Registers, moveRegister_pass)
{
    Registers testRegisters;

    string testNameA = "$t0";
    int testValueA = 0;
    EXPECT_TRUE(testRegisters.addRegister(testNameA, testValueA));

    string testNameB = "$pc";
    int testValueB = -10;
    EXPECT_TRUE(testRegisters.addRegister(testNameB, testValueB));

    string testNameC = "$31";
    int testValueC = 4;
    EXPECT_TRUE(testRegisters.addRegister(testNameC, testValueC));

    int replacementValue = -8;
    EXPECT_TRUE(testRegisters.updateRegister(testNameC, replacementValue));

    string newNameD = "$h2";
    int newValueD = 9;
    EXPECT_TRUE(testRegisters.updateRegister(newNameD, newValueD));

    auto registersMap = testRegisters.getRegisters();
    EXPECT_EQ(registersMap.size(), 4);

    auto registerLookupIter = testRegisters.lookupRegister(newNameD);
    EXPECT_EQ(registerLookupIter->first, newNameD);
    EXPECT_EQ(registerLookupIter->second, newValueD);

    registerLookupIter = testRegisters.lookupRegister(testNameA);
    EXPECT_EQ(registerLookupIter->first, testNameA);
    EXPECT_EQ(registerLookupIter->second, testValueA);

    registerLookupIter = testRegisters.lookupRegister(testNameB);
    EXPECT_EQ(registerLookupIter->first, testNameB);
    EXPECT_EQ(registerLookupIter->second, testValueB);

    registerLookupIter = testRegisters.lookupRegister(testNameC);
    EXPECT_EQ(registerLookupIter->first, testNameC);
    EXPECT_EQ(registerLookupIter->second, replacementValue);

    testRegisters.moveRegisterContents(testNameB, testNameA);

    registerLookupIter = testRegisters.lookupRegister(testNameA);
    EXPECT_EQ(registerLookupIter->first, testNameA);
    EXPECT_EQ(registerLookupIter->second, 0);

    registerLookupIter = testRegisters.lookupRegister(testNameB);
    EXPECT_EQ(registerLookupIter->first, testNameB);
    EXPECT_EQ(registerLookupIter->second, testValueA);
}
