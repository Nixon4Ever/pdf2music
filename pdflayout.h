#pragma once
#include <vector>
struct staffLine {
	int y;
	int height;
	staffLine();
	staffLine(int Y);
};
struct staff {
	std::vector<staffLine> lines;
	staff();
};
struct pdfLayout {
	std::vector<staff> staves;
	int staffLeft;
	int staffRight;
	pdfLayout();

	void readNewStaffLine(int y);
};
