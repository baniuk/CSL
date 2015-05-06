#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat src1, dst1;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

char* window_name1 = "Morphology Transformations Demo";

/** Function Headers */
void Morphology_Operations(int, void*);

/** @function main */
// funkcje morfologiczne
int main_morphology(int argc, char** argv)
{
	/// Load an image
	src1 = imread(argv[1]);

	if (!src1.data)
	{
		return -1;
	}

	/// Create window
	namedWindow(window_name1, WINDOW_AUTOSIZE);

	/// Create Trackbar to select Morphology operation
	createTrackbar("Operator:\n 0: Opening - 1: Closing \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name1, &morph_operator, max_operator, Morphology_Operations);

	/// Create Trackbar to select kernel type
	createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name1,
		&morph_elem, max_elem,
		Morphology_Operations);

	/// Create Trackbar to choose kernel size
	createTrackbar("Kernel size:\n 2n +1", window_name1,
		&morph_size, max_kernel_size,
		Morphology_Operations);

	/// Default start
	Morphology_Operations(0, 0);

	waitKey(0);
	return 0;
}

/**
* @function Morphology_Operations
*/
void Morphology_Operations(int, void*)
{
	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator + 2;

	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

	/// Apply the specified morphology operation
	morphologyEx(src1, dst1, operation, element);
	imshow(window_name1, dst1);
}
