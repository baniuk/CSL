#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

/// Global Variables
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src5; Mat dst5;
char window_name5[] = "Filter Demo 1";

/// Function headers
int display_caption(char* caption);
int display_dst(int delay);

/**
* function main
*/
// wygladzanie
int main_smooth(int argc, char** argv)
{
	namedWindow(window_name5, WINDOW_AUTOSIZE);

	/// Load the source image
	src5 = imread(argv[1], 1);

	if (display_caption("Original Image") != 0) { return 0; }

	dst5 = src5.clone();
	if (display_dst(DELAY_CAPTION) != 0) { return 0; }

	/// Applying Homogeneous blur
	if (display_caption("Homogeneous Blur") != 0) { return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		blur(src5, dst5, Size(i, i), Point(-1, -1));
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}

	/// Applying Gaussian blur
	if (display_caption("Gaussian Blur") != 0) { return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		GaussianBlur(src5, dst5, Size(i, i), 0, 0);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}

	/// Applying Median blur
	if (display_caption("Median Blur") != 0) { return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		medianBlur(src5, dst5, i);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}

	/// Applying Bilateral Filter
	if (display_caption("Bilateral Blur") != 0) { return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		bilateralFilter(src5, dst5, i, i * 2, i / 2);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}

	/// Wait until user press a key
	display_caption("End: Press a key!");

	waitKey(0);
	return 0;
}

int display_caption(char* caption)
{
	dst5 = Mat::zeros(src5.size(), src5.type());
	putText(dst5, caption,
		Point(src5.cols / 4, src5.rows / 2),
		FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

	imshow(window_name5, dst5);
	int c = waitKey(DELAY_CAPTION);
	if (c >= 0) { return -1; }
	return 0;
}

int display_dst(int delay)
{
	imshow(window_name5, dst5);
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}
