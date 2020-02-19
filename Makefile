

default: clean catimage

catimage: image.o
	gcc -O3 -lm image.o main.c -o catimage

image.o: stb_image.h
	gcc -O3 -c image.c

stb_image.h:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

clean:
	rm -f catimage


INSTALL_PATH = /usr/local

install: default
	mkdir -p $(INSTALL_PATH)/bin
	cp -f catimage $(INSTALL_PATH)/bin
	chmod 755 $(INSTALL_PATH)/bin/catimage

uninstall:
	rm -f $(INSTALL_PATH)/bin/catimage
