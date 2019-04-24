CFLAGS=-Wall -Wextra -Werror -g

all: brightness_manager
	chmod a+s brightness_manager

brightness_manager: brightness_manager.o
