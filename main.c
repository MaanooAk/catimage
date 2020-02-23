
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/ioctl.h>


// options
char nearest = 0;
char fit = 1;
char slideshow = 0;
char ignore = 0;

// globals
int window_w;
int window_h;
char command;

// functions
char display(FILE *file, char* filename, char hasnext);
char printimage(FILE *file, char* filename);

// #include "image.c"
unsigned char* read_image(FILE* file, int* width, int* height, int* channels);


#define printf_error(format, ...) \
	if (!ignore) fprintf(stderr, "catimage: " format, ##__VA_ARGS__);


int main(int argc, char *argv[]) {

	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size); // 1: the out fd

	window_w = size.ws_col;
	window_h = size.ws_row * 2 - 2;
	command = 0;

	char onlyfiles = 0;
	char filesdisplayed = 0;
	for (int i = 1; i < argc; i++) {

		if (argv[i][0] != '-' || onlyfiles) {

			char *filename = argv[i];
			FILE *file = fopen(filename, "rb");

			display(file, filename, i+1 != argc);

			if (file) fclose(file);

			filesdisplayed += 1;
			if (command == 'q') break;

		} else if (argv[i][1] == '\0') {
			display(stdin, "stdin", i+1 != argc);

		} else for (int ci = 1; argv[i][ci] != 0; ci++) {

			if (argv[i][ci] == '-' && argv[i][ci+1] == 0) onlyfiles = 1;

			else if (argv[i][ci] == 'n') nearest = 1;
			else if (argv[i][ci] == 'f') fit = 0;
			else if (argv[i][ci] == 's') slideshow = 1;
			else if (argv[i][ci] == 'i') ignore = 1;

			else if (argv[i][ci] == 'w' && i+1 < argc) window_w = atoi(argv[++i]);
			else if (argv[i][ci] == 'h' && i+1 < argc) window_h = atoi(argv[++i]);

			else {
				#include "help.c"
				printf(help, argv[i][ci]);
				return 1;
			}
		}
	}

	if (!filesdisplayed) {
		display(stdin, "stdin", 0);
	}

}

char display(FILE *file, char *filename, char hasnext) {

	if (slideshow) {
		printf("\e[1;1H\e[J");

		char shown = printimage(file, filename);

		if (shown && hasnext) scanf("%c", &command);

		return shown;
	} else {
		return printimage(file, filename);
	}

}


char printimage(FILE *file, char *filename) {

	if (!file) {
		printf_error("file not found: %s\n", filename);
		return 0;
	}

	int width, height, channels;
	unsigned char *image = read_image(file, &width, &height, &channels);
	int stride = width;

	#define PIXELS(Y,X,I) image[((Y) * stride + (X)) * 4 + I]

	if (!image) {
		printf_error("file format not supported: %s\n", filename);
		return 0;
	}

	printf("\e[1m%s  \e[0;2m%dx%d %d\e[0m\n", filename, width, height, channels);

	while (width > window_w || (fit && height > window_h)) {

		width = (width - 1) / 2;
		height = (height - 1) / 2;

		for (int y = 0; y < height; y += 1) {
			for (int x = 0; x < width; x += 1) {
				for (int i = 0; i < 4; i++) {

					if (nearest) {
						PIXELS(y, x, i) = PIXELS(2*y, 2*x, i);

					} else {
						PIXELS(y, x, i) = (
							PIXELS(2*y  , 2*x  , i)/4 +
							PIXELS(2*y+2, 2*x  , i)/4 +
							PIXELS(2*y  , 2*x+2, i)/4 +
							PIXELS(2*y+2, 2*x+2, i)/4
						);
					}

				}
			}
		}

	}

	width = width - 1;
	height = height - ( height%2 ? 1 : 2);

	for (int y = 0; y < height; y += 2) {
		for (int x = 0; x < width; x += 1) {

			printf("\e[0;38;2;%d;%d;%d;48;2;%d;%d;%dm▀\e[0m",
				PIXELS(y  , x, 0), PIXELS(y  , x, 1), PIXELS(y  , x, 2),
				PIXELS(y+1, x, 0), PIXELS(y+1, x, 1), PIXELS(y+1, x, 2)
			);
		}
		printf("\n");
	}

	return 1;
}


