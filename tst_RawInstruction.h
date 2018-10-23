#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "RawInstruction.h"

using namespace testing;

//TODO: update for new class member: "lineNumber"


TEST(RawInstruction, constructor)
{
    RawInstruction testRawInstruction;
    EXPECT_EQ(testRawInstruction.getOperation(), "nop");
    EXPECT_TRUE(testRawInstruction.getArguments().empty());
}

TEST(RawInstruction, setArguments_appendArguments_pass)
{
    string testOperation = "lw";
    vector<string> testArguments;
    string arg1 = "$t3";
    string arg2 = "0";

    RawInstruction testRawInstruction;
    testRawInstruction.setOperation(testOperation);

    testArguments.push_back(arg1);
    testRawInstruction.setArguments(testArguments);
    testRawInstruction.appendArgument(arg2);

    EXPECT_EQ(testRawInstruction.getOperation(), testOperation);

    auto rawInstructionSet = testRawInstruction.getArguments();
    EXPECT_FALSE(rawInstructionSet.empty());

    auto argumentIter = rawInstructionSet.begin();
    EXPECT_EQ(*argumentIter, arg1);

    ++argumentIter;
    EXPECT_EQ(*argumentIter, arg2);
}
