#include <vector>
#include <iostream>
#include <fstream>
#include <opencv2\opencv.hpp>

//////////////////////////////////////////////////
// Define and Typedef
//
typedef unsigned short USHORT;


//////////////////////////////////////////////////
// Clamp
//
__forceinline float clamp(float val)
{
	return (val < 0.f) ? 0.f : ((val > 1.f) ? 1.0f : val);
}


void createFrontBackRef(uint32_t iImageSizeX, uint32_t iImageSizeY)
{
	/// Make our image pointer
	std::vector<unsigned char> image;
	image.reserve(iImageSizeX * iImageSizeY);

	//char * image = new char[(iImageSizeX * iImageSizeY)];

	/// Work out the image
	for (uint32_t y = 0; y < iImageSizeY; y++)
	{
		for (uint32_t x = 0; x < iImageSizeX; x++)
		{
			if (y % (iImageSizeY / 8) == 0) image.push_back(0x0);
			else image.push_back(0xff);
		}
	}

	///Create writable
	auto cvImage = cvCreateImage(cvSize(iImageSizeX, iImageSizeY), 8, 1);
	//cvImage->imageData = &image[0];
	memcpy_s(
		cvImage->imageData,
		cvImage->width * cvImage->height,
		&image[0],
		iImageSizeX * iImageSizeY
		);

	cvSaveImage("FrontBackRef.png", cvImage);
}

void createFrontFacialRef(uint32_t iImageSizeX, uint32_t iImageSizeY)
{
	/// Make our image pointer
	std::vector<unsigned char> image;
	image.reserve(iImageSizeX * iImageSizeY);

	//char * image = new char[(iImageSizeX * iImageSizeY)];

	/// Work out the image
	for (uint32_t y = 0; y < iImageSizeY; y++)
	{
		for (uint32_t x = 0; x < iImageSizeX; x++)
		{
			if (y % (iImageSizeY / 2) == 0) { image.push_back(0xff); image.push_back(0x0); image.push_back(0x0); }
			else if (y % (iImageSizeY / 4) == 0 && y > iImageSizeY / 2) { image.push_back(0x0); image.push_back(0x0); image.push_back(0xff); }
			else if (y % (iImageSizeY / 5) == 0 && (y < (iImageSizeY / 5 + 1) || y > iImageSizeY - (iImageSizeY / 5 + 1))) { image.push_back(0x0); image.push_back(0xff); image.push_back(0x0); }
			else if (x % (iImageSizeX / 5) == 0) { image.push_back(0x0); image.push_back(0x87); image.push_back(0xff);}
			else { image.push_back(0xff); image.push_back(0xff); image.push_back(0xff); }
		}
	}

	///Create writable
	auto cvImage = cvCreateImage(cvSize(iImageSizeX, iImageSizeY), 8, 3);
	//cvImage->imageData = &image[0];
	memcpy_s(
		cvImage->imageData,
		cvImage->width * cvImage->height * 3,
		&image[0],
		iImageSizeX * iImageSizeY * 3
		);

	cvSaveImage("FrontFacialRef.png", cvImage);
}

//////////////////////////////////////////////////
// Entry Point
//
int main(int argc, char** argv)
{
	/// Create Front/Back Reference
	createFrontBackRef(800,800);

	/// Create Face Reference
	createFrontFacialRef(2000,2000);

	return 0;
}
