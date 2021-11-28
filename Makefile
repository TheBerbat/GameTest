APP := game

CC  := gcc
CPP := g++-11
CPP_FLAGS := -std=c++20

INCLUDES := -I/opt/homebrew/include/ 
LIBS     := -L/opt/homebrew/lib/ -lIrrlicht


all: $(APP)

$(APP): main.cpp
	$(CPP) main.cpp $(LIBS) -o $(APP) $(INCLUDES) $(CPP_FLAGS)

.PHONY: all clean
clean:
	rm $(APP)
