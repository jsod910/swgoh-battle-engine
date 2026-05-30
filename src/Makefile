# 1. Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# 2. Name of your final executable
TARGET = battle_engine

# 3. Find ALL .cpp files in the root folder AND any downstream folders
SRCS = main.cpp \
       $(wildcard engine/*.cpp) \
	   $(wildcard engine/abilities/*.cpp) \
	   $(wildcard engine/events/*.cpp) \
       $(wildcard entities/*.cpp) \
	   $(wildcard loaders/*.cpp)

# 4. Convert the list of .cpp files into .o (object) files
OBJS = $(SRCS:.cpp=.o)

# 5. The "recipe" to link everything together into the final application
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# 6. A recipe to quickly clean up your folder
clean:
	rm -f $(OBJS) $(TARGET)