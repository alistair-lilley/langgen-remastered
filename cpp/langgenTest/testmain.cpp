#ifndef LANGGENTEST_TESTMAIN_CPP
#define LANGGENTEST_TESTMAIN_CPP
#include "IPAContainerTest.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    IPA testipa = initializeIPA();
    std::vector<std::string> passfails;
    passfails.push_back(TestIPAloadOneChart(testipa) ? "Testing loadOneChart passed" : "Testing loadOneChart failed");
    passfails.push_back(TestIPAloadOneKey(testipa) ? "Testing loadOneKey passed" : "Testing loadOneKey failed");
    passfails.push_back(TestIPAgetFeature(testipa) ? "Testing getFeature passed" : "Testing getFeature failed");
    passfails.push_back(TestIPAremoveNotFeature(testipa) ? "Testing removeNotFeature passed" : "Testing removeNotFeature failed");
    passfails.push_back(TestIPAgetFeatures(testipa) ? "Testing getFeatures passed" : "Testing getFeatures failed");

    for (auto test : passfails)
    {
        std::cout << test << std::endl;
    }
}

#endif