#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Constants.h"

using namespace testing;

TEST(Constants, constructor)
{
    Constants testConstants;
    auto testConstantsMap = testConstants.getConstants();
    EXPECT_TRUE(testConstantsMap.empty());
}

TEST(Constants, addConstant_single_pass)
{
    Constants testConstants;
    string testName = "constantA";
    int testValue = 5;

    testConstants.addConstant(testName, testValue);

    auto testConstantsMap = testConstants.getConstants();
    EXPECT_EQ(testConstantsMap.size(), 1);

    auto constantIter = testConstantsMap.begin();
    EXPECT_EQ(constantIter->first, testName);
    EXPECT_EQ(constantIter->second, testValue);
}

TEST(Constants, addConstant_multiple_pass)
{
    Constants testConstants;
    string testName = "constantA";
    int testValue = 5;

    testConstants.addConstant(testName, testValue);

    string testNameB = "constantB";
    int testValueB = -2;

    testConstants.addConstant(testNameB, testValueB);

    string testNameC = "gamma";
    int testValueC = 4009;

    testConstants.addConstant(testNameC, testValueC);

    auto testConstantsMap = testConstants.getConstants();
    EXPECT_EQ(testConstantsMap.size(), 3);

    auto constantIter = testConstantsMap.begin();
    EXPECT_EQ(constantIter->first, testName);
    EXPECT_EQ(constantIter->second, testValue);

    ++constantIter;
    EXPECT_EQ(constantIter->first, testNameB);
    EXPECT_EQ(constantIter->second, testValueB);

    ++constantIter;
    EXPECT_EQ(constantIter->first, testNameC);
    EXPECT_EQ(constantIter->second, testValueC);
}

TEST(Constants, lookupConstant_multipleInMap_pass)
{
    Constants testConstants;
    string testName = "constantA";
    int testValue = 5;

    testConstants.addConstant(testName, testValue);

    string testNameB = "constantB";
    int testValueB = -2;

    testConstants.addConstant(testNameB, testValueB);

    string testNameC = "gamma";
    int testValueC = 4009;

    testConstants.addConstant(testNameC, testValueC);

    auto testConstantsMap = testConstants.getConstants();
    EXPECT_EQ(testConstantsMap.size(), 3);

    auto constantIter = testConstantsMap.begin();
    EXPECT_EQ(constantIter->first, testName);
    EXPECT_EQ(constantIter->second, testValue);

    ++constantIter;
    EXPECT_EQ(constantIter->first, testNameB);
    EXPECT_EQ(constantIter->second, testValueB);

    auto lookupResult = testConstants.lookupConstant(testNameB);
    EXPECT_EQ(lookupResult->first, constantIter->first);
    EXPECT_EQ(lookupResult->second, constantIter->second);

    ++constantIter;
    EXPECT_EQ(constantIter->first, testNameC);
    EXPECT_EQ(constantIter->second, testValueC);
}

TEST(Constants, setConstants_pass)
{
    Constants testConstants;
    string testName = "constantA";
    int testValue = 5;

    testConstants.addConstant(testName, testValue);

    string testNameB = "constantB";
    int testValueB = -2;

    testConstants.addConstant(testNameB, testValueB);

    string testNameC = "gamma";
    int testValueC = 4009;

    testConstants.addConstant(testNameC, testValueC);

    auto testConstantsMap = testConstants.getConstants();
    EXPECT_EQ(testConstantsMap.size(), 3);

    auto constantIter = testConstantsMap.begin();
    EXPECT_EQ(constantIter->first, testName);
    EXPECT_EQ(constantIter->second, testValue);

    ++constantIter;
    EXPECT_EQ(constantIter->first, testNameB);
    EXPECT_EQ(constantIter->second, testValueB);

    auto lookupResult = testConstants.lookupConstant(testNameB);
    EXPECT_EQ(lookupResult->first, constantIter->first);
    EXPECT_EQ(lookupResult->second, constantIter->second);

    ++constantIter;
    EXPECT_EQ(constantIter->first, testNameC);
    EXPECT_EQ(constantIter->second, testValueC);

    Constants testConstants2;

    testConstants2.setConstants(testConstantsMap);
    auto secondConstantsMap = testConstants2.getConstants();

    EXPECT_EQ(secondConstantsMap.size(), 3);

    auto secondConstantIter = secondConstantsMap.begin();
    EXPECT_EQ(secondConstantIter->first, testName);
    EXPECT_EQ(secondConstantIter->second, testValue);

    ++secondConstantIter;
    EXPECT_EQ(secondConstantIter->first, testNameB);
    EXPECT_EQ(secondConstantIter->second, testValueB);

    auto secondLookupResult = testConstants2.lookupConstant(testNameB);
    EXPECT_EQ(secondLookupResult->first, secondConstantIter->first);
    EXPECT_EQ(secondLookupResult->second, secondConstantIter->second);

    ++secondConstantIter;
    EXPECT_EQ(secondConstantIter->first, testNameC);
    EXPECT_EQ(secondConstantIter->second, testValueC);

}

