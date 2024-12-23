CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags gtk4 json-c`
LDFLAGS = `pkg-config --libs gtk4 json-c`
CPPFLAGS = -Iheader/

SRC = add_window.c generate_button.c generate_action.c profile.c
OBJ = $(SRC:.c=.o)
EXEC = main_interfaceV2

all: $(EXEC)

$(EXEC): main_interfaceV2.o $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) main_interfaceV2.o $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)
