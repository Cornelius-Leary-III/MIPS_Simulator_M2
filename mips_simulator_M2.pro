include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_mips_simulator.h \
    token.h \
    lexer.h \
    parser.h \
    DeclarationParser.h \
    InstructionParser.h \
    tst_declarationParser.h \
    tst_instructionParser.h \
    tst_lexer.h \
    tst_token.h \
    VirtualMachineContents.h \
    Registers.h \
    Labels.h \
    Constants.h \
    Memory.h

SOURCES += \
        main.cpp \
    token.cpp \
    lexer.cpp \
    parser.cpp \
    DeclarationParser.cpp \
    InstructionParser.cpp \
    VirtualMachineContents.cpp \
    Registers.cpp \
    Labels.cpp \
    Constants.cpp \
    Memory.cpp
