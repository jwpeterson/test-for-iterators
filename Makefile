CXXFLAGS = -O3

all:
	$(CXX) $(CXXFLAGS) testwork.C -c -o testwork.o
	$(CXX) $(CXXFLAGS) testforiterators.C -o testforiterators testwork.o
