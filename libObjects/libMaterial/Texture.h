/*
 * Texture.h
 * Author: abhinavdevireddy
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

class Texture {
public:

	Texture(string textureFile, string bumpFile) {
		texData = LoadPPM((char*)textureFile.c_str(), &texWidth, &texHeight);
		bumpData = LoadPPM((char*)bumpFile.c_str(), &bumpWidth, &bumpHeight);
	}

	~Texture() {
		free(texData);
		free(bumpData);
	}

	int texWidth;
	int texHeight;
	int bumpWidth;
	int bumpHeight;
	unsigned char* texData;
	unsigned char* bumpData;

private:
	unsigned char* LoadPPM(char *filename, int *width, int *height) {
		FILE* fp;
		int i, w, h, d;
		unsigned char* image;
		char head[70];          /* max line <= 70 in PPM (per spec). */

		fp = fopen(filename, "rb");
		if (!fp) {
			perror(filename);
			return NULL;
		}

		/* grab first two chars of the file and make sure that it has the
		 correct magic cookie for a raw PPM file. */
		fgets(head, 70, fp);
		if (strncmp(head, "P6", 2)) {
			fprintf(stderr, "%s: Not a raw PPM file\n", filename);
			return NULL;
		}

		/* grab the three elements in the header (width, height, maxval). */
		i = 0;
		while(i < 3) {
			fgets(head, 70, fp);
			if (head[0] == '#')     /* skip comments. */
				continue;
			if (i == 0)
				i += sscanf(head, "%d %d %d", &w, &h, &d);
			else if (i == 1)
				i += sscanf(head, "%d %d", &h, &d);
			else if (i == 2)
				i += sscanf(head, "%d", &d);
		}

		/* grab all the image data in one fell swoop. */

		image = (unsigned char*)malloc(sizeof(unsigned char)*w*h*3);

		fread(image, sizeof(unsigned char), w*h*3, fp);
		fclose(fp);

		*width = w;
		*height = h;
//		std::cout << "Loaded texture \"" << filename << "\" (width=" << *width << ", height=" << *height << ")" << std::endl;
		return image;
	}
};


#endif /* TEXTURE_H_ */
