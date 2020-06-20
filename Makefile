CFLAGS=-Wall -Wextra -Werror -O2

all: brightness_manager

install: brightness_manager
	cp brightness_manager /usr/bin
	chmod a+s /usr/bin/brightness_manager

brightness_manager: brightness_manager.o
