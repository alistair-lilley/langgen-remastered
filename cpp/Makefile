CXX = g++
CXXFLAGS = -g
LDFLAGS = -Ilib/include
LDFLAGSTEST = -Itest
TESTSOURCE = build/IPAContainer.o build/SylGenerator.o build/IPAContainerTest.o build/testmain.o

	
app/test: $(TESTSOURCE)
	$(CXX) $(CXXFLAGS) $(TESTSOURCE) -o app/test

build/IPAContainer.o: lib/src/IPAContainer.cpp lib/include/langgen/IPAContainer.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c lib/src/IPAContainer.cpp -o build/IPAContainer.o

build/SylGenerator.o: lib/src/SylGenerator.cpp lib/include/langgen/SylGenerator.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c lib/src/SylGenerator.cpp -o build/SylGenerator.o

build/IPAContainertest.o: test/IPAContainerTest.cpp test/IPAContainertest.h
	$(CXX) $(CXXFLAGS) $(LDFLAGSTEST) $(LDFLAGS) -c test/IPAContainertest.cpp -o build/IPAContainertest.o

build/testmain.o: test/testmain.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDFLAGSTEST) -c test/testmain.cpp -o build/testmain.o
