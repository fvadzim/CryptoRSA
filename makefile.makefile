APP := app
SRCS := main.cpp BtS.cpp decrypt.cpp encrypt.cpp gen.cpp
all: $(SRCS)
	g++ -Wall -ansi -g -o $(APP) $^ -lgmp
