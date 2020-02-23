

default: semiclean catimage

catimage: image.o help.c
	gcc -O3 -lm image.o main.c -o catimage

image.o: stb_image.h
	gcc -O3 -c image.c

stb_image.h:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

help.c:
	xxd -i help > help.c

semiclean:
	rm -f help.c catimage
clean: semiclean
	rm -f stb_image.h image.o

INSTALL_PATH = /usr/local

install: default
	mkdir -p $(INSTALL_PATH)/bin
	cp -f catimage $(INSTALL_PATH)/bin
	chmod 755 $(INSTALL_PATH)/bin/catimage

uninstall:
	rm -f $(INSTALL_PATH)/bin/catimage
