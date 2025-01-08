CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags gtk4 json-c`
LDFLAGS = `pkg-config --libs gtk4 json-c`
CPPFLAGS = -Iheader/

SRC = generate_button.c profile.c load_routine.c add_routine_json.c delete.c rename.c action_page.c interface_stat.c stat.c
OBJ = $(SRC:.c=.o)
EXEC = main_interfaceV2

all: $(EXEC)

$(EXEC): main_interfaceV2.o $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) main_interfaceV2.o $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

.PHONY :  all clean