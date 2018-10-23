#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Variables.h"

using namespace testing;

TEST(Variables, constructor)
{
    Variables testVariables;
    auto testVariablesMap = testVariables.getVariables();
    EXPECT_TRUE(testVariablesMap.empty());
}

TEST(Variables, variableDataStruct)
{
    unsigned testMemoryIndex = 0;
    unsigned testVariableSizeInBytes = 1;
    string testInitialValue = "starting value";
    string testCurrentValue = "different value";

    variableData testVarData;

    testVarData.memoryIndex = testMemoryIndex;
    testVarData.variableSizeInBytes = testVariableSizeInBytes;
    testVarData.initialValue = testInitialValue;
    testVarData.currentValue = testVarData.initialValue;

    EXPECT_EQ(testVarData.memoryIndex, testMemoryIndex);
    EXPECT_EQ(testVarData.variableSizeInBytes, testVariableSizeInBytes);
    EXPECT_EQ(testVarData.initialValue, testInitialValue);
    EXPECT_EQ(testVarData.currentValue, testInitialValue);

    testVarData.currentValue = testCurrentValue;
    EXPECT_EQ(testVarData.currentValue, testCurrentValue);
    EXPECT_NE(testVarData.initialValue, testVarData.currentValue);
}

TEST(Variables, addVariable_single_pass)
{
    string testVariableName = "variableA";
    unsigned startingAddress = 0;
    unsigned testSizeInBytes = 4;
    string testValue = "4005";

    Variables testVariables;
    EXPECT_TRUE(testVariables.addVariable(testVariableName, testSizeInBytes, testValue));

    auto lookupIter = testVariables.lookupVariable(testVariableName);
    auto variablesEnd = testVariables.getVariables().end();
    EXPECT_NE(lookupIter, variablesEnd);
    EXPECT_EQ(lookupIter->first, testVariableName);
    EXPECT_EQ(lookupIter->second.memoryIndex, startingAddress);
    EXPECT_EQ(lookupIter->second.variableSizeInBytes, testSizeInBytes);
    EXPECT_EQ(lookupIter->second.initialValue, testValue);
    EXPECT_EQ(lookupIter->second.currentValue, testValue);
}

TEST(Variables, addVariable_multiple_pass)
{
    string testVariableName = "variableA";
    unsigned startingAddress = 0;
    unsigned testSizeInBytes = 4;
    string testValue = "4005";

    Variables testVariables;
    EXPECT_TRUE(testVariables.addVariable(testVariableName, testSizeInBytes, testValue));

    auto lookupIter = testVariables.lookupVariable(testVariableName);
    auto variablesEnd = testVariables.getVariables().end();
    EXPECT_NE(lookupIter, variablesEnd);
    EXPECT_EQ(lookupIter->first, testVariableName);
    EXPECT_EQ(lookupIter->second.memoryIndex, startingAddress);
    EXPECT_EQ(lookupIter->second.variableSizeInBytes, testSizeInBytes);
    EXPECT_EQ(lookupIter->second.initialValue, testValue);
    EXPECT_EQ(lookupIter->second.currentValue, testValue);

    string testVariableNameB = "variableB";
    unsigned testSizeInBytesB = 2;
    string testValueB = "22000";

    EXPECT_TRUE(testVariables.addVariable(testVariableNameB, testSizeInBytesB, testValueB));

    auto lookupIterB = testVariables.lookupVariable(testVariableNameB);
    EXPECT_NE(lookupIterB, variablesEnd);
    EXPECT_EQ(lookupIterB->first, testVariableNameB);
    EXPECT_EQ(lookupIterB->second.memoryIndex, startingAddress + testSizeInBytes);
    EXPECT_EQ(lookupIterB->second.variableSizeInBytes, testSizeInBytesB);
    EXPECT_EQ(lookupIterB->second.initialValue, testValueB);
    EXPECT_EQ(lookupIterB->second.currentValue, testValueB);
}

TEST(Variables, updateVariableValue_pass)
{
    string testVariableName = "variableA";
    unsigned startingAddress = 0;
    unsigned testSizeInBytes = 4;
    string testValue = "4005";

    Variables testVariables;
    EXPECT_TRUE(testVariables.addVariable(testVariableName, testSizeInBytes, testValue));

    auto lookupIter = testVariables.lookupVariable(testVariableName);
    auto variablesEnd = testVariables.getVariables().end();
    EXPECT_NE(lookupIter, variablesEnd);
    EXPECT_EQ(lookupIter->first, testVariableName);
    EXPECT_EQ(lookupIter->second.memoryIndex, startingAddress);
    EXPECT_EQ(lookupIter->second.variableSizeInBytes, testSizeInBytes);
    EXPECT_EQ(lookupIter->second.initialValue, testValue);
    EXPECT_EQ(lookupIter->second.currentValue, testValue);

    string testVariableNameB = "variableB";
    unsigned testSizeInBytesB = 2;
    string testValueB = "22000";

    EXPECT_TRUE(testVariables.addVariable(testVariableNameB, testSizeInBytesB, testValueB));

    auto lookupIterB = testVariables.lookupVariable(testVariableNameB);
    EXPECT_NE(lookupIterB, variablesEnd);
    EXPECT_EQ(lookupIterB->first, testVariableNameB);
    EXPECT_EQ(lookupIterB->second.memoryIndex, startingAddress + testSizeInBytes);
    EXPECT_EQ(lookupIterB->second.variableSizeInBytes, testSizeInBytesB);
    EXPECT_EQ(lookupIterB->second.initialValue, testValueB);
    EXPECT_EQ(lookupIterB->second.currentValue, testValueB);

    string newTestValueA = "43";
    EXPECT_TRUE(testVariables.updateVariableValue(testVariableName, newTestValueA));

    lookupIter = testVariables.lookupVariable(testVariableName);
    EXPECT_NE(lookupIter, variablesEnd);
    EXPECT_EQ(lookupIter->first, testVariableName);
    EXPECT_EQ(lookupIter->second.memoryIndex, startingAddress);
    EXPECT_EQ(lookupIter->second.variableSizeInBytes, testSizeInBytes);
    EXPECT_EQ(lookupIter->second.initialValue, testValue);
    EXPECT_EQ(lookupIter->second.currentValue, newTestValueA);

    lookupIterB = testVariables.lookupVariable(testVariableNameB);
    EXPECT_NE(lookupIterB, variablesEnd);
    EXPECT_EQ(lookupIterB->first, testVariableNameB);
    EXPECT_EQ(lookupIterB->second.memoryIndex, startingAddress + testSizeInBytes);
    EXPECT_EQ(lookupIterB->second.variableSizeInBytes, testSizeInBytesB);
    EXPECT_EQ(lookupIterB->second.initialValue, testValueB);
    EXPECT_EQ(lookupIterB->second.currentValue, testValueB);
}



