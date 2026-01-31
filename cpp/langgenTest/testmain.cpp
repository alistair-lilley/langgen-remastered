#ifndef LANGGENTEST_TESTMAIN_CPP
#define LANGGENTEST_TESTMAIN_CPP
#include "langgenTest/IPAContainer.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    IPA testipa = initializeIPA();
    std::vector<std::string> passfails;
    passfails.push_back(TestIPAloadOneChart(testipa) ? "Testing loadOneChart passed" : "Testing loadOneChart failed");

    for (auto test : passfails)
    {
        std::cout << test << std::endl;
    }
}

#endif