
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* read_image(FILE* file, int* width, int* height, int* channels) {
	return stbi_load_from_file(file, width, height, channels, STBI_rgb_alpha);
}
