#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Instruction.h"

using namespace testing;

TEST(Instruction, constructor)
{
    Instruction testInstruction;
    EXPECT_EQ(testInstruction.getOperation(), "nop");
    EXPECT_TRUE(testInstruction.getArguments().empty());
}

TEST(Instruction, setArguments_appendArguments_pass)
{
    string testOperation = "lw";
    vector<string> testArguments;
    string arg1 = "$t3";
    string arg2 = "0";

    Instruction testInstruction;
    testInstruction.setOperation(testOperation);

    testArguments.push_back(arg1);
    testInstruction.setArguments(testArguments);
    testInstruction.appendArgument(arg2);

    EXPECT_EQ(testInstruction.getOperation(), testOperation);

    auto instructionSet = testInstruction.getArguments();
    EXPECT_FALSE(instructionSet.empty());

    auto argumentIter = instructionSet.begin();
    EXPECT_EQ(*argumentIter, arg1);

    ++argumentIter;
    EXPECT_EQ(*argumentIter, arg2);
}
