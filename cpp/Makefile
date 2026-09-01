CXX = g++
CXXFLAGS = -g
LDFLAGS = -IlanggenLib/include
LDFLAGSTEST = -IlanggenTest
TESTSOURCE = build/IPAContainer.o build/SylGenerator.o build/IPAContainerTest.o build/testmain.o

	
langgenApp/test: $(TESTSOURCE)
	$(CXX) $(CXXFLAGS) $(TESTSOURCE) -o langgenApp/test

build/IPAContainer.o: langgenLib/src/IPAContainer.cpp langgenLib/include/langgen/IPAContainer.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c langgenLib/src/IPAContainer.cpp -o build/IPAContainer.o

build/SylGenerator.o: langgenLib/src/SylGenerator.cpp langgenLib/include/langgen/SylGenerator.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c langgenLib/src/SylGenerator.cpp -o build/SylGenerator.o

build/IPAContainerTest.o: langgenTest/IPAContainerTest.cpp langgenTest/IPAContainerTest.h
	$(CXX) $(CXXFLAGS) $(LDFLAGSTEST) $(LDFLAGS) -c langgenTest/IPAContainerTest.cpp -o build/IPAContainerTest.o

build/testmain.o: langgenTest/testmain.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDFLAGSTEST) -c langgenTest/testmain.cpp -o build/testmain.o