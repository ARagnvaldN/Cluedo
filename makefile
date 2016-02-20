#
# Makefile for Cluedo
#
# (C) Andreas Nylund 2015
#

#### VARIABLES #### DEBUG
CFLAGS = -Wall -std=c++11 -D_DEBUG
#CFLAGS = -Wall -std=c++11

#### MAIN ENTRY POINT ####
MAIN = BusinessModel
MAIN_CPP_FILES := $(wildcard $(MAIN)/*.cpp)
MAIN_OBJ_FILES := $(addprefix obj/,$(notdir $(MAIN_CPP_FILES:.cpp=.o)))

#### BUSINESS LAYER ####
BL = BusinessModel/BusinessLayer
BL_CPP_FILES := $(wildcard $(BL)/*.cpp)
BL_OBJ_FILES := $(addprefix obj/,$(notdir $(BL_CPP_FILES:.cpp=.o)))

BL_ACTOR := $(BL)/Actors
BL_ACTOR_CPP_FILES := $(wildcard $(BL_ACTOR)/*.cpp)
BL_ACTOR_OBJ_FILES := $(addprefix obj/,$(notdir $(BL_ACTOR_CPP_FILES:.cpp=.o)))

BL_ENVIRON := $(BL)/Environments
BL_ENVIRON_CPP_FILES := $(wildcard $(BL_ENVIRON)/*.cpp)
BL_ENVIRON_OBJ_FILES := $(addprefix obj/,$(notdir $(BL_ENVIRON_CPP_FILES:.cpp=.o)))

BL_ITEM := $(BL)/Items
BL_ITEM_CPP_FILES := $(wildcard $(BL_ITEM)/*.cpp)
BL_ITEM_OBJ_FILES := $(addprefix obj/,$(notdir $(BL_ITEM_CPP_FILES:.cpp=.o)))

#### PRESENTATION LAYER ####
PL = BusinessModel/PresentationLayer
PL_CPP_FILES := $(wildcard $(PL)/*.cpp)
PL_OBJ_FILES := $(addprefix obj/,$(notdir $(PL_CPP_FILES:.cpp=.o)))

.PHONY : all
all : Cluedo.exe

Cluedo.exe :  $(MAIN_OBJ_FILES)
	g++ $(CFLAGS) obj/*.o -o Cluedo

obj/%.o : $(MAIN)/%.cpp $(PL_OBJ_FILES) $(BL_OBJ_FILES) $(BL_ACTOR_OBJ_FILES) $(BL_ENVIRON_OBJ_FILES) $(BL_ITEM_OBJ_FILES)
	g++ $(CFLAGS) -c $< -o $@

obj/%.o : $(PL)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

obj/%.o : $(BL)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

obj/%.o : $(BL_ACTOR)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

obj/%.o : $(BL_ENVIRON)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

obj/%.o : $(BL_ITEM)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

.PHONY : clean
clean:
	del obj\*.o
