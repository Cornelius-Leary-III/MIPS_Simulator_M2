#ifndef VIRTUALMACHINECONTENTS_H
#define VIRTUALMACHINECONTENTS_H

#include "Registers.h"
#include "Memory.h"
#include "Labels.h"
#include "Constants.h"

//#include <map>
//#include <vector>
#include <string>
//#include <iostream>
#include <sstream>

//using std::map;
//using std::pair;
//using std::make_pair;
//using std::vector;
using std::string;
using std::stringstream;



class VirtualMachineContents
{
public:

    VirtualMachineContents();

   //TODO: determine the functions that would be appropriate for this wrapper-style class, both during the parsing process and afterwards.


private:

    Registers vmRegisters;
    Memory vmMemory;
    Labels vmLabels;
    Constants vmConstants;

};

#endif // VIRTUALMACHINECONTENTS_H
