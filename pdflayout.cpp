#include "pdflayout.h"

staff::staff()
{
	lines = std::vector<staffLine>();
}

pdfLayout::pdfLayout()
{
	staves = std::vector<staff>();
	int staffLeft = 0;
	int staffRight = 0;
}

void pdfLayout::readNewStaffLine(int y)
{
	if (staves.empty()) {
		printf("first stave!\n");
		staves.emplace_back();
	}
	staff& curstave = staves[staves.size()-1];
	if (curstave.lines.empty()) {
		printf("first Line!\n");
		curstave.lines.emplace_back(y);
	}
	else {
		staffLine& lastLine = curstave.lines[curstave.lines.size()-1];
		if (lastLine.y + lastLine.height == y) {
			printf("bigger line!\n");
			lastLine.height++;
		}
		else {// need a new line
			if (staves[staves.size() - 1].lines.size() == 5) {
				printf("new stave!\n");
				staves.emplace_back();
			}
			printf("new line!\n");
			staves[staves.size() - 1].lines.emplace_back(y);
		}
	}
}

staffLine::staffLine() : y(0),height(1) {}
staffLine::staffLine(int Y) : y(Y), height(1) {}
