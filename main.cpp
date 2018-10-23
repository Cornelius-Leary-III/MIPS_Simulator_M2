#include "tst_token.h"
#include "tst_lexer.h"
#include "tst_declarationParser.h"
#include "tst_instructionParser.h"

#include "tst_Constants.h"
#include "tst_Labels.h"
#include "tst_Memory.h"
#include "tst_Registers.h"
#include "tst_Variables.h"
#include "tst_RawInstruction.h"

#include "tst_Instructions.h"

#include "tst_mips_simulator.h"



#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
