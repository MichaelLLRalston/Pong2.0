#pragma once

#include "sfwdraw.h"

const float PADDLE_HEIGHT = 150;
const float PADDLE_WIDTH = 30;

namespace Box
{

	// Help from Arthur about box drawing
	void drawPlayer(float px, float py)
	{
		float pw = px + PADDLE_WIDTH;
		float ph = py + PADDLE_HEIGHT;

		sfw::drawLine(px, py, pw, py);
		sfw::drawLine(pw, py, pw, ph);
		sfw::drawLine(px, py, px, ph);
		sfw::drawLine(px, ph, pw, ph);

	}
}