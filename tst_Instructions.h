#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Instructions.h"

using namespace testing;

TEST(InstructionBase, constructor)
{
    InstructionBase testInstruction;

    auto testContents = testInstruction.getContents();

    EXPECT_TRUE(testContents->constantsPtr->getConstants().empty());
    EXPECT_TRUE(testContents->labelsPtr->getLabels().empty());
    EXPECT_TRUE(testContents->memoryPtr->getMemory().empty());
    EXPECT_TRUE(testContents->variablesPtr->getVariables().empty());
    EXPECT_TRUE(testContents->programPtr->empty());
}
