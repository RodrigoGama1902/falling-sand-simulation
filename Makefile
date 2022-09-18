#OBJS specifies which files to compile as part of the project
OBJS = src/myapp.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -std=c++17 -lmingw32

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2main

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = build/01_hello_SDL

INCLUDES = -I include -I src/graphics -I src/app -I src/shapes -I src/utils -L lib

FILES = src/utils/*.cpp src/app/*.cpp src/graphics/*.cpp src/shapes/*.cpp

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDES) $(FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)
	copy bin\SDL2.dll build\SDL2.dll

