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

CFLAGS	= $(TYPE) -Ofast -pedantic -Wall -W

ifeq ($(shell uname -s), Darwin)
	LFLAGS	= -framework OpenGL -framework GLUT -framework Cocoa
else
	LFLAGS = -lm -lglut -lGL -lGLU
endif

define directoryGenerator
	@mkdir -p $(BUILD_DIR) > /dev/null
	@mkdir -p $(OBJ_DIR) > /dev/null
	@mkdir -p $(BIN_DIR) > /dev/null
endef

all: $(OBJS)
	$(CC) $(OBJS) -o $(BIN_DIR)/$(OUT) $(LFLAGS)


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
