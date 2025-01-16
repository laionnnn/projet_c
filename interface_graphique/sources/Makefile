CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags gtk4 json-c`
LDFLAGS = `pkg-config --libs gtk4 json-c`
CPPFLAGS = -Iheader/

SRC = add_action.c profile.c load.c add_to_json.c delete.c rename.c action_page.c interface_stat.c stat.c spin_button.c
OBJ = $(SRC:.c=.o)
EXEC = application

all: $(EXEC)

$(EXEC): application.o $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) application.o $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

.PHONY :  all clean