/*
 * Image.h
 * Handles all the output related functions of the Image.
 * Author: abhinavdevireddy
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "PNGImage.h"
#include <pthread.h>

pthread_mutex_t imageDataAccess;

class Image {
public:

	Image(string outputImg, int imgWd, int imgHt) {

		pthread_mutex_init(&imageDataAccess, NULL);
		pthread_mutex_lock(&imageDataAccess);
		this->outputImg = outputImg.append(".png");
		this->imgWd = imgWd;
		this->imgHt = imgHt;

		imageData = new float[imgWd * imgHt * 3];

		for (int i = 0; i < imgWd * imgHt * 3; i++)
			imageData[i] = 0;

		zbuffer = new float[imgWd * imgHt];
		for (int i = 0; i < imgWd * imgHt; i++)
			zbuffer[i] = MAX_Z;
		pthread_mutex_unlock(&imageDataAccess);
	}

	~Image() {
		delete [] imageData;
		delete [] zbuffer;
	}

	void setPixel(float px, float py, Vector* pcolor) {
		pthread_mutex_lock(&imageDataAccess);
		double intpart;
		px = modf(px, &intpart) >= 0.5 ? ceil(px) : floor(px);
		py = modf(py, &intpart) >= 0.5 ? ceil(py) : floor(py);
		if (px >= 0 && py >= 0) {
			int idx = px2idx(px, py);
			imageData[idx] = pcolor->X() > 1.0 ? 1.0 : pcolor->X();
			imageData[idx + 1] = pcolor->Y() > 1.0 ? 1.0 : pcolor->Y();
			imageData[idx + 2] = pcolor->Z() > 1.0 ? 1.0 : pcolor->Z();
		}
		pthread_mutex_unlock(&imageDataAccess);
	}

	//Z-Buffer Implementation
	void setPixel(float px, float py, int pz, Vector* pcolor) {
		double intpart;
		px = modf(px, &intpart) >= 0.5 ? ceil(px) : floor(px);
		py = modf(py, &intpart) >= 0.5 ? ceil(py) : floor(py);
		if (px > 0 && py > 0) {
			int idx = px2idx(px, py);
			int idx_z = px * py + py;
			if (zbuffer[idx_z] > pz) {
				zbuffer[idx_z] = pz;
				imageData[idx] = pcolor->X();
				imageData[idx + 1] = pcolor->Y();
				imageData[idx + 2] = pcolor->Z();
			}
		}
	}

	void setPixel(float px, float py, float r, float g, float b) {
		pthread_mutex_lock(&imageDataAccess);
		double intpart;
		px = modf(px, &intpart) >= 0.5 ? ceil(px) : floor(px);
		py = modf(py, &intpart) >= 0.5 ? ceil(py) : floor(py);
		if (px >= 0 && py >= 0) {
			int idx = px2idx(px, py);
			imageData[idx] = r;
			imageData[idx + 1] = g;
			imageData[idx + 2] = b;
		}
		pthread_mutex_unlock(&imageDataAccess);
	}

	void setPixel(Vector* posVector, float r, float g, float b) {
		setPixel(posVector->X(), posVector->Y(), r, g, b);
	}

	void writeImage() {
		pthread_mutex_lock(&imageDataAccess);
		Write(outputImg, imgWd, imgHt, imageData);
		pthread_mutex_unlock(&imageDataAccess);
	}

	static void Write(string outputImg, int imgWd, int imgHt, float* imageData) {
		PNGImage outputPNG;
		outputPNG.writeFileData(outputImg.c_str(), imgWd, imgHt, imageData);
	}

	void getOGLData(float* output) {
		for (int i = 0; i < imgWd*imgHt*3; i++) {
			output[i] = imageData[i];
		}
	}

private:
	static const float MAX_Z = 10000;

	int px2idx(int x, int y) {
		if (x < imgWd && y < imgHt)
			return (3 * y * imgWd) + (x * 3);
		else
			return 0;
	}

	string outputImg;
	int imgWd;
	int imgHt;
	float* imageData;
	float* zbuffer;
};

#endif /* IMAGE_H_ */
