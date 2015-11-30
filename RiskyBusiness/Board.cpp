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
	this->startY = ConsoleHandler::getInstance()->getCusrsorPosition();
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
			this->handle->gotoXYPrint(pos, j, (char)(179));
		}
		if (pos == this->startX)
		{
			this->handle->gotoXYPrint(this->startX, this->startY, (char)(218));
			this->handle->gotoXYPrint(this->startX, this->endY, (char)(192));
		}
		else if (pos == this->endX)
		{
			this->handle->gotoXYPrint(this->endX, this->startY, (char)(191));
			this->handle->gotoXYPrint(this->endX, this->endY, (char)(217));
		}
		else
		{
			this->handle->gotoXYPrint(pos, this->startY, (char)(194));
			this->handle->gotoXYPrint(pos, this->endY, (char)(193));
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
			this->handle->gotoXYPrint(j, pos, (char)(196));

			int xpos = this->startX;
			for (int k = 0; k < this->numCols; k++)
			{
				xpos += this->colWidth;
				if (xpos == j)
				{
					this->handle->gotoXY(xpos, pos);
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
			this->handle->gotoXYPrint(this->startX, this->startY, (char)(218));
			this->handle->gotoXYPrint(this->endX, this->startY, (char)(191));
		}
		else if (pos == this->endY)
		{
			this->handle->gotoXYPrint(this->startX, this->endY, (char)(192));
			this->handle->gotoXYPrint(this->endX, this->endY, (char)(217));
		}
		else
		{
			this->handle->gotoXYPrint(this->startX, pos, (char)(195));
			this->handle->gotoXYPrint(this->endX, pos, (char)(180));
		}
	}
	
	this->handle->gotoXYPrint(0, this->endY + 2, "");

}

void Board::drawBorders() {
	//Horizontal lines
	for (int i = this->startX; i <= this->endX; i++)
	{
		this->handle->gotoXYPrint(i, this->startY, (char)(196));
		this->handle->gotoXYPrint(i, this->endY, (char)(196));
	}
	//Vertical lines
	for (int i = this->startY; i <= this->endY; i++)
	{
		this->handle->gotoXYPrint(this->startX, i, (char)(179));
		this->handle->gotoXYPrint(this->endX, i, (char)(179));
	}

	//Missing characters at the corners of the borders
	this->handle->gotoXYPrint(this->startX, this->startY, (char)(218));
	this->handle->gotoXYPrint(this->endX, startY, (char)(191));
	this->handle->gotoXYPrint(startX, endY, (char)(192));
	this->handle->gotoXYPrint(endX, endY, (char)(217));

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

Board::~Board()
{
}
