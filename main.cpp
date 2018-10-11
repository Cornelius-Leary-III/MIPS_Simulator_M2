#include "tst_token.h"
#include "tst_lexer.h"
#include "tst_declarationParser.h"
#include "tst_instructionParser.h"

#include "tst_mips_simulator.h"



#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}