# Compiler
CXX = g++

# Compiler and linker flags
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -larmadillo -llapack

# Executables
TARGETS = filter_nut_graphs filter_core_graphs filter_dextronut_digraphs filter_binut_digraphs filter_ambinut_digraphs

# Source files
SRCS1 = filter_nut_graphs.cpp nut_tools.cpp
SRCS2 = filter_core_graphs.cpp nut_tools.cpp
SRCS3 = filter_dextronut_digraphs.cpp nut_tools.cpp
SRCS4 = filter_binut_digraphs.cpp nut_tools.cpp
SRCS5 = filter_ambinut_digraphs.cpp nut_tools.cpp

# Object files
OBJS1 = $(SRCS1:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)
OBJS3 = $(SRCS3:.cpp=.o)	
OBJS4 = $(SRCS4:.cpp=.o)
OBJS5 = $(SRCS5:.cpp=.o)

# Rules
all: $(TARGETS)

filter_nut_graphs: $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS1) $(LDFLAGS)

filter_core_graphs: $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS2) $(LDFLAGS)

filter_dextronut_digraphs: $(OBJS3)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS3) $(LDFLAGS)

filter_binut_digraphs: $(OBJS4)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS4) $(LDFLAGS)

filter_ambinut_digraphs: $(OBJS5)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS5) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(TARGETS)
