#include "pdflayout.h"

staff::staff()
{
	lines = std::vector<staffLine>();
	measureLines = std::vector<measureLine>();
}

void staff::addMeasureLine(int x)
{
	if (measureLines.empty()) {
		measureLines.emplace_back(x);
	}
}

pdfLayout::pdfLayout()
{
	isDoubleStaff = true;
	staves = std::vector<staff>();
	measures = std::vector<measure>();
	int staffLeft = 0;
	int staffRight = 0;
}

void pdfLayout::readNewStaffLine(int y)
{
	if (staves.empty()) {
		staves.emplace_back();
	}
	staff& curstave = staves[staves.size()-1];
	if (curstave.lines.empty()) {
		curstave.lines.emplace_back(y);
	}
	else {
		staffLine& lastLine = curstave.lines[curstave.lines.size()-1];
		if (lastLine.y + lastLine.height == y) {
			lastLine.height++;
		}
		else {// need a new line
			if (staves[staves.size() - 1].lines.size() == 5) {
				staves.emplace_back();
			}
			staves[staves.size() - 1].lines.emplace_back(y);
		}
	}
}

staffLine::staffLine() : y(0),height(1) {}
staffLine::staffLine(int Y) : y(Y), height(1) {}

vec2::vec2() : x(0),y(0) {}

vec2::vec2(int X, int Y): x(X), y(Y) {}

area2::area2() : topLeft(), bottomRight() {}

area2::area2(vec2 start) : topLeft(start), bottomRight(start) {}

area2::area2(vec2 start, vec2 end) : topLeft(start), bottomRight(end) {}

measureLine::measureLine(int X) : x(X), width(1) {}
