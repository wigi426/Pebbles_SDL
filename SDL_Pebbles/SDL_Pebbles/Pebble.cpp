#include "Includes.h"



Pebble::Pebble()
{
	m_position.x = 500;
	m_position.y = 500;
	m_position.w = 100;
	m_position.h = 100;
}


Pebble::~Pebble()
{
}

void Pebble::render(psuedoGlobals &globals)
{
	globals.textures.at(Texture::TEXTUER_PEBBLE).render(globals, &m_position);
}

void Pebble::setPos(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

