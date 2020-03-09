#ETIENNE (づ｡◕‿‿◕｡)づ PENAULT#

SRC_DIR		= ./src
BUILD_DIR	= ./build
OBJ_DIR		= ./build/obj
BIN_DIR		= ./build/bin

SRC		= $(wildcard $(SRC_DIR)/*.c)
HEADER	= $(wildcard $(SRC_DIR)/*.h)

OBJS	= $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:%.c=%.o))

OUT		= bsp.out
CC	 	= gcc

CFLAGS	= -Ofast -pedantic -Wall -W

linuxLFLAGS	= -lm -lglut -lGL -lGLU
macosLFLAGS = -framework OpenGL -framework GLUT -framework Cocoa

define directoryGenerator
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
endef

all: $(OBJS)
ifeq ($(OS), Darwin)
	$(CC) $(OBJS) -o $(BIN_DIR)/$(OUT) $(macosLFLAGS)
else
	$(CC) $(OBJS) -o $(BIN_DIR)/$(OUT) $(linuxLFLAGS)
endif

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(call directoryGenerator)
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(call directoryGenerator)
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -Rf $(OBJ_DIR)

cleanall:
	rm -Rf $(BUILD_DIR)
