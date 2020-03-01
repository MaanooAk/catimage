

catimage: image.o help.c
	gcc -O3 -lm image.o main.c -o catimage

image.o: image.c stb_image.h
	gcc -O3 -c image.c

stb_image.h:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

help.c: help.txt
	cat help.txt > help
	echo -e '\0' >> help
	xxd -i help > help.c
	rm -f help

clean:
	rm -f catimage help help.c stb_image.h image.o

INSTALL_PATH = /usr/local

install: catimage
	mkdir -p $(INSTALL_PATH)/bin
	cp -f catimage $(INSTALL_PATH)/bin
	chmod 755 $(INSTALL_PATH)/bin/catimage

uninstall:
	rm -f $(INSTALL_PATH)/bin/catimage
