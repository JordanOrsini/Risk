#include "Board.h"

Board::Board(int startX, int startY, int endX, int endY)
{
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	this->width = endX - startX;
	this->height = endY - startY;
}

void Board::setNumRows(int rows) {
	this->numRows = rows;
	this->rowHeight = this->height / this->numRows;
}

void Board::setNumCols(int columns) {
	this->numCols = columns;
	this->colWidth = this->width / this->numCols;
}

int Board::getColumnWidth() {
	return this->colWidth;
}

int Board::getRowHeight() {
	return this->rowHeight;
}

int Board::getHeight() {
	return this->height;
}

int Board::getWidth() {
	return this->width;
}

void Board::drawBoard() {
	cout.flush();
	GetConsoleScreenBufferInfo(this->hStd, &SBInfo);
	this->startY = SBInfo.dwCursorPosition.Y;
	this->endY = this->height + this->startY;

	this->drawBorders();

	// draw vertical lines
	int pos = this->startX;
	for (int i = 0; i < this->numCols; i++)
	{
		pos += this->colWidth;
		if (pos >= this->endX)
			pos = this->endX;

		for (int j = this->startY; j <= this->endY; j++)
		{
			gotoXYPrint(pos, j, (char)(179));
		}
		if (pos == this->startX)
		{
			this->gotoXYPrint(this->startX, this->startY, (char)(218));
			this->gotoXYPrint(this->startX, this->endY, (char)(192));
		}
		else if (pos == this->endX)
		{
			this->gotoXYPrint(this->endX, this->startY, (char)(191));
			this->gotoXYPrint(this->endX, this->endY, (char)(217));
		}
		else
		{
			this->gotoXYPrint(pos, this->startY, (char)(194));
			this->gotoXYPrint(pos, this->endY, (char)(193));
		}
	}

	// draw horizental lines
	pos = this->startY;
	for (int i = 0; i < this->numRows; i++)
	{
		pos += this->rowHeight;
		if (pos > this->endY)
			pos = this->endY;

		for (int j = this->startX; j <= this->endX; j++)
		{
			this->gotoXYPrint(j, pos, (char)(196));

			int xpos = this->startX;
			for (int k = 0; k < this->numCols; k++)
			{
				xpos += this->colWidth;
				if (xpos == j)
				{
					this->gotoXY(xpos, pos);
					if (pos == this->endY)
					{
						cout << (char)(193);
					}
					else if (pos == this->startY)
					{
						cout << (char)(194);
					}
					else
					{
						cout << (char)(197);
					}
				}

			}
		}
		if (pos == this->startY)
		{
			this->gotoXYPrint(this->startX, this->startY, (char)(218));
			this->gotoXYPrint(this->endX, this->startY, (char)(191));
		}
		else if (pos == this->endY)
		{
			this->gotoXYPrint(this->startX, this->endY, (char)(192));
			this->gotoXYPrint(this->endX, this->endY, (char)(217));
		}
		else
		{
			this->gotoXYPrint(this->startX, pos, (char)(195));
			this->gotoXYPrint(this->endX, pos, (char)(180));
		}
	}
	
	this->gotoXYPrint(0, this->endY + 2, "");

}

void Board::drawBorders() {
	//Horizontal lines
	for (int i = this->startX; i <= this->endX; i++)
	{
		gotoXYPrint(i, this->startY, (char)(196));
		gotoXYPrint(i, this->endY, (char)(196));
	}
	//Vertical lines
	for (int i = this->startY; i <= this->endY; i++)
	{
		gotoXYPrint(this->startX, i, (char)(179));
		gotoXYPrint(this->endX, i, (char)(179));
	}

	//Missing characters at the corners of the borders
	gotoXYPrint(this->startX, this->startY, (char)(218));
	gotoXYPrint(this->endX, startY, (char)(191));
	gotoXYPrint(startX, endY, (char)(192));
	gotoXYPrint(endX, endY, (char)(217));

}

void Board::clearBoard() {
	system("cls");
}

int Board::getStartX() {
	return startX;
}

int Board::getStartY() {
	return startY;
}

void Board::gotoXY(int x, int y)
{
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void Board::gotoXYPrint(int x, int y, string str)
{
	this->gotoXYPrint(x, y, str, 10);
}

void Board::gotoXYPrint(int x, int y, string str, int color)
{
	this->gotoXY(x, y);
	SetConsoleTextAttribute(this->hStd, color);
	cout << str;
}

void Board::gotoXYPrint(int x, int y, char chr)
{
	this->gotoXY(x, y);
	cout << chr;
}

Board::~Board()
{
}
