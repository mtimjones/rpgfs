
OBJECTS=files.o init.o levels.o main.o names.o shell.o bugs.o

rpgfs: $(OBJECTS)
	$(CC) -Werror -Wall -g -o $@ $^

%.o: %.c
	$(CC) -Wall -Werror -g -c $^

clean:
	$(RM) $(OBJECTS) *~ rpgfs
