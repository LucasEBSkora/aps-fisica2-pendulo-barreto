#OBJS specifies which files to compile as part of the project
OBJS =  main.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS =

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = 

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =

#OBJ_NAME specifies the name of our executable
OBJ_NAME = pendulo

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) -ggdb `pkg-config --cflags opencv4` `pkg-config --libs opencv4`
 