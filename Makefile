#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -std=c++17 -lmingw32

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2main

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = build/FallingSandSimulation

INCLUDES = -IC:\SDL2-2.26.5\x86_64-w64-mingw32\include -I src -L C:\SDL2-2.26.5\x86_64-w64-mingw32\lib

FILES = src/utils/*.cpp \
		src/app/*.cpp \
		src/graphics/*.cpp \
		src/shapes/*.cpp \
		src/simulation/*.cpp \
		src/simulation/elements/*.cpp \
		src/simulation/elements/base/*.cpp \
		src/editor/*.cpp\
		src/editor/tools/*.cpp

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDES) $(FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)


