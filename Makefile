all:
	$(CXX) testwork.C -c -o testwork.o
	$(CXX) testforiterators.C -o testforiterators testwork.o

