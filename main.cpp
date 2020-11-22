#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include <Magick++.h>
#include "pdflayout.h"
using namespace std;
int view_x = 0;
int view_y = 0;
bool isMouseDown = false;
cv::Mat opencvImage;
cv::Mat debugImage;
cv::Mat displayImage;
int mouse_last_x = 0;
int mouse_last_y = 0;
int w;
int h;

bool isBlack(const cv::Vec3b& rgb) {
	return rgb[0] < 70 && rgb[1] < 70 && rgb[2] < 70;
}
//using namespace cv;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		isMouseDown = true;
	}
	else if (event == cv::EVENT_LBUTTONUP)
	{
		isMouseDown = false;
	}
	else if (event == cv::EVENT_MOUSEMOVE)
	{
		if (isMouseDown) {
			int diffX = x - mouse_last_x;
			int diffY = y - mouse_last_y;
			view_x -= diffX;
			view_y -= diffY;
			view_x = max(0, view_x);
			view_y = max(0, view_y);
			view_x = min(w-1200, view_x);
			view_y = min(h-800, view_y);
			cv::Rect roi(view_x, view_y, 1200, 800);
			//printf("(%d,%d)\n", view_x, view_y);
			displayImage = debugImage(roi);
			cv::imshow("pdf", displayImage);
		}
		mouse_last_x = x;
		mouse_last_y = y;
	}
}
int main(int argc, char** argv)
{
	Magick::InitializeMagick(*argv);
	try
	{
		Magick::Image image;
		image.density("500");
		image.read("test.pdf");
		w = image.columns();
		h = image.rows();

		// Make OpenCV Mat of same size with 8-bit and 3 channels
		opencvImage = cv::Mat(h, w, CV_8UC3);
		debugImage = cv::Mat(h, w, CV_8UC3);
		displayImage = cv::Mat(1200, 800, CV_8UC3);
		// Unpack Magick++ pixels into OpenCV Mat structure
		image.write(0, 0, w, h, "BGR", Magick::CharPixel, opencvImage.data);
		image.write(0, 0, w, h, "BGR", Magick::CharPixel, debugImage.data);
		cv::Rect roi(0, 0, 1200, 800);
		displayImage = debugImage(roi);
		cv::imshow("pdf", displayImage);
		cv::resizeWindow("pdf", 1200, 800);
		cv::setMouseCallback("pdf", CallBackFunc, NULL);
		pdfLayout layout = pdfLayout();
		// FIND STAFF LINES
		for (int y = 0; y < h; y++) {
			bool isStaff = true;
			for (int x = (int)((float)w*.15f); x < (int)((float)w * .85f); x++) {
				if (!isBlack(opencvImage.at<cv::Vec3b>(y, x))) {
					isStaff=false;
					break;
				}
			}
			if (isStaff) {
				//printf("New staff!");
				layout.readNewStaffLine(y);
			}
		}
		// debug staff lines
		for (int staveNum = 0; staveNum < layout.staves.size(); staveNum++) {
			staff& staffRef = layout.staves[staveNum];
			//printf("Staff: %d\n", staveNum);
			for (int lineNum = 0; lineNum < staffRef.lines.size(); lineNum++) {
				staffLine& lineRef = staffRef.lines[lineNum];
				//printf("StaffLine: %d: %d (%d,%d,%d)\n", lineNum, lineRef.y, staveNum * 30 + 10, lineNum * 30,200);
					for (int x = (int)((float)w * .15f); x < (int)((float)w * .85f); x++) {
						for (int y = lineRef.y; y < lineRef.y + lineRef.height; y++) {
							//debugImage.at<cv::Vec3b>(y, x) = cv::Vec3b(staveNum * 30 + 10, lineNum * 30, 200);//COLOR DEBUG
						}
					}
				}
			}
		}

		// exit
		cv::waitKey();
	}
	catch (exception & e)
	{
		cout << "Warning " << e.what() << endl;
	}
	return 0;
}