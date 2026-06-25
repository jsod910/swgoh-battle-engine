# 1. Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# 2. Name of your final executable
TARGET = battle_engine

# 1. Define a pure-Make recursive wildcard function
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# 3. Find ALL .cpp files automatically across all subfolders
SRCS := main.cpp \
        $(call rwildcard,engine,*.cpp) \
        $(call rwildcard,entities,*.cpp) \
        $(call rwildcard,loaders,*.cpp)

# 3b. Automatically find every subfolder and convert them into -I include flags
# (This grabs all folders inside engine, entities, and loaders)
INC_DIRS := engine entities loaders $(sort $(dir $(call rwildcard,engine,*) $(call rwildcard,entities,*) $(call rwildcard,loaders,*)))
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# SRCS := main.cpp \
# 	$(shell find engine entities loaders -type f -name "*.cpp")

# INC_DIRS := $(shell find engine entities loaders -type d)
# INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# 3. Find ALL .cpp files in the root folder AND any downstream folders
# SRCS = main.cpp \
#        $(wildcard engine/*.cpp) \
# 	   $(wildcard engine/abilities/*.cpp) \
# 	   $(wildcard engine/abilities/effects/*.cpp) \
# 	   $(wildcard engine/events/*.cpp) \
# 	   $(wildcard engine/events/listeners/*.cpp) \
#        $(wildcard entities/*.cpp) \
# 	   $(wildcard loaders/*.cpp)

# 4. Convert the list of .cpp files into .o (object) files
OBJS = $(SRCS:.cpp=.o)

# 5. The "recipe" to link everything together into the final application
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

# 6. A recipe to quickly clean up your folder
clean:
	rm -f $(OBJS) $(TARGET)