#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Labels.h"

using namespace testing;

TEST(Labels, constructor)
{
    Labels testLabels;
    auto testLabelsMap = testLabels.getLabels();
    EXPECT_TRUE(testLabelsMap.empty());
}

//TEST(Labels, addLabel_single_pass)
//{
//    Labels testLabels;

//    string testName = "label1:";
//    string testType = ".data";
//    unsigned testAddress = 0;

//    EXPECT_TRUE(testLabels.addLabel(testName, testType, testAddress));

//    auto lookupIter = testLabels.lookupLabel(testName);
//    EXPECT_EQ(lookupIter->first, testName);
//    EXPECT_EQ(lookupIter->second.first, testType);
//    EXPECT_EQ(lookupIter->second.second, testAddress);
//}

//TEST(Labels, addLabel_multiple_pass)
//{
//    Labels testLabels;

//    string testName = "label1:";
//    string testType = ".data";
//    unsigned testAddress = 0;

//    EXPECT_TRUE(testLabels.addLabel(testName, testType, testAddress));

//    auto lookupIter = testLabels.lookupLabel(testName);
//    EXPECT_EQ(lookupIter->first, testName);
//    EXPECT_EQ(lookupIter->second.first, testType);
//    EXPECT_EQ(lookupIter->second.second, testAddress);

//    string testNameB = "label2:";
//    string testTypeB = ".data";
//    unsigned testAddressB = 4;

//    EXPECT_TRUE(testLabels.addLabel(testNameB, testTypeB, testAddressB));

//    lookupIter = testLabels.lookupLabel(testNameB);
//    EXPECT_EQ(lookupIter->first, testNameB);
//    EXPECT_EQ(lookupIter->second.first, testTypeB);
//    EXPECT_EQ(lookupIter->second.second, testAddressB);

//    string testNameC = "labelC:";
//    string testTypeC = ".text";
//    unsigned testAddressC = 12;

//    EXPECT_TRUE(testLabels.addLabel(testNameC, testTypeC, testAddressC));

//    lookupIter = testLabels.lookupLabel(testNameC);
//    EXPECT_EQ(lookupIter->first, testNameC);
//    EXPECT_EQ(lookupIter->second.first, testTypeC);
//    EXPECT_EQ(lookupIter->second.second, testAddressC);
//}
