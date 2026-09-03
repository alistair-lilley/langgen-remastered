/* Tests for IPAContainer header file
*/
#ifndef LANGGENTEST_IPACONTAINERTEST_H
#define LANGGENTEST_IPACONTAINERTEST_H
#include "langgen/IPAContainer.h"
#include <string>
#include <vector>
#include <map>

IPA initializeIPA();

bool TestIPAloadOneChart(IPA&);

bool TestIPAloadOneKey(IPA&);

bool TestIPAgetFeature(IPA&);

bool TestIPAremoveNotFeature(IPA&);


#endif
