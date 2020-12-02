#pragma once
#include <vector>
struct vec2 {
	int x;
	int y;
	vec2();
	vec2(int X, int Y);
};
struct area2 {
	vec2 topLeft;
	vec2 bottomRight;
	area2();
	area2(vec2 start);
	area2(vec2 start, vec2 end);
};
struct staffLine {
	int y;
	int height;
	staffLine();
	staffLine(int Y);
};
struct measureLine {
	int x;
	int width;
	measureLine(int X);
};
struct measure {
	int lineBegin;
	int lineEnd;
};
struct staff {
	std::vector<staffLine> lines;
	std::vector<measureLine> measureLines;
	staff();
	void addMeasureLine(int x);
};
struct pdfLayout {
	std::vector<staff> staves;
	std::vector<measure> measures;
	int staffLeft;
	int staffRight;
	bool isDoubleStaff;
	pdfLayout();
	void readNewStaffLine(int y);
};
