#include "Includes.h"



GridSquares::GridSquares()
{
}


GridSquares::~GridSquares()
{
}


SDL_Rect GridSquares::getPebbleRenderPos()
{
	SDL_Rect temp{ m_pebbleRenderPosX, m_pebbleRenderPosY, 100, 100 };
	return temp;
}



void GridSquares::setState(squareState newState)
{
	m_state = newState;
}

void GridSquares::setPos(int x, int y)
{
	m_topLeftPosX = x;
	m_topLeftPosY = y;
	m_pebbleRenderPosX = x + 50;
	m_pebbleRenderPosY = y + 50;
}

bool GridSquares::posMatch(int x, int y)
{
	if (x >= m_topLeftPosX &&
		x < m_topLeftPosX + 200 &&
		y >= m_topLeftPosY &&
		y < m_topLeftPosY + 200)
	{
		return true;
	}

	return false;
}

void GridSquares::setPotentialFor(int i)
{
	m_potentialFor = i;
}

int GridSquares::getPotentialFor()
{
	return m_potentialFor;
}

GridSquares::squareState GridSquares::getState()
{
	return m_state;
}

void GridSquares::render(psuedoGlobals &globals)
{
	switch (m_state)
	{
	case EMPTY:
		break;
	case OCCUPIED:
		globals.textures.at(Texture::TEXTURE_PEBBLE).render(globals, &getPebbleRenderPos());
		break;
	case MASTER_SELECTED:
		globals.textures.at(Texture::TEXTURE_PEBBLE_MASTER).render(globals, &getPebbleRenderPos());
		break;
	case SELECTED:
		globals.textures.at(Texture::TEXTURE_PEBBLE_SELECT).render(globals, &getPebbleRenderPos());
		break;
	case POTENTIAL:
		globals.textures.at(Texture::TEXTURE_PEBBLE_POTENTIAL).render(globals, &getPebbleRenderPos());
		break;
	}
}