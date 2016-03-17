GEN_SRC =  Initializer.cpp Player.cpp gofish_constants.cpp gofish_types.cpp PlayerStore.cpp Card.cpp
GEN_OBJ = $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR = /usr/local/include/thrift
BOOST_DIR = /usr/local/include/boost

INC = -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: GoFish_Initializer GoFish_Player

%.o: %.cpp
	$(CXX) -std=c++11 -Wall $(INC) -c $< -o $@

GoFish_Initializer: GoFish_Initializer.o $(GEN_OBJ)
	$(CXX) -std=c++11 $^ -o $@ -L/usr/local/lib -lthrift

GoFish_Player: GoFish_Player.o $(GEN_OBJ)
	$(CXX) -std=c++11 $^ -o $@ -L/usr/local/lib -lthrift

clean:
	$(RM) *.o GoFish_Initializer GoFish_Player