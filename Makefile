# Define the output executable name
OUT = out

# Define the source files
SRC = main.c comic.c

# The rule to build the executable
$(OUT): $(SRC)
	gcc -Wall -Wextra -Werror -g -o out $(SRC)

# A clean rule (optional) to remove the executable
clean:
	rm -f $(OUT)