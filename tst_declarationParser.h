#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "parser.h"

using namespace testing;

//TEST(declarationParserTest, constructorTest)
//{
//}

#define TEST_CONSTANTS 1
#define TEST_LABELS 0
#define TEST_LAYOUTS 1

#if TEST_CONSTANTS

TEST(declarationParserTest, constant_pass)
{
    string testString = "  .data\n  constantC = 352";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, constant_fail)
{
    string testString = ".data\nconstantA = H2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, constant_fail_splitByEOL)
{
    string testString = ".data\nconstantA = \nH2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, constant_fail_digitFirstChar)
{
    string testString = ".data\n3BonstantA = H2";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

#endif // TEST_CONSTANTS

#if TEST_LABELS

TEST(declarationParserTest, label_pass)
{
    string testString = ".data\n    testLabel:";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, label_fail_noColonChar)
{
    string testString = ".data\n    testLabel";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, label_fail_spaceBetweenTextAndColonChar)
{
    string testString = ".data\n    testLabel :";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, label_fail_digitFirstChar)
{
    string testString = ".data\n    44testLabel";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

#endif // TEST_LABELS

#if TEST_LAYOUTS

TEST(declarationParserTest, layout_var_intLayout_word_pass)
{
    string testString = ".data\n    testVar: .word 10";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_word_fail)
{
    string testString = ".data\n    testVar: .word A";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_half_pass)
{
    string testString = ".data\n    testVar: .half 4";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_half_fail)
{
    string testString = ".data\n    testVar: .half @";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_byte_pass)
{
    string testString = ".data\n    testVar: .byte 1";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_byte_fail)
{
    string testString = ".data\n    testVar: .byte byte";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_space_pass)
{
    string testString = ".data\n    testVar: .space 12";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_space_fail)
{
    string testString = ".data\n    testVar: .space (10)";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_fail_invalidLayoutKeyword_1)
{
    string testString = ".data\n    testVar: .spice 10";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_intLayout_fail_invalidLayoutKeyword_2)
{
    string testString = ".data\n    testVar: word 3";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_stringLayout_ascii_pass)
{
    string testString = ".data\n    testVar: .ascii \"test string goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_stringLayout_asciiz_pass)
{
    string testString = ".data\n    testVar: .asciiz \"test string with null terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_TRUE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_stringLayout_ascii_fail_missingClosingStringDelimChar)
{
    string testString = ".data\n    testVar: .ascii \"test string goes here";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_stringLayout_asciiz_fail_missingOpeningStringDelimChar)
{
    string testString = ".data\n    testVar: .asciiz test string with null terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_stringLayout_ascii_fail_missingBothStringDelimChars)
{
    string testString = ".data\n    testVar: .ascii test string goes here";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}

TEST(declarationParserTest, layout_var_stringLayout_asciiz_fail_oddNumberOfStringDelimChars)
{
    string testString = ".data\n    testVar: .asciiz \"test string with null \"terminator goes here\"";

    stringstream testSS;
    testSS << testString;

    parser testParser(testSS);

    EXPECT_FALSE(testParser.parseStream());
}


#endif // TEST_LAYOUTS








