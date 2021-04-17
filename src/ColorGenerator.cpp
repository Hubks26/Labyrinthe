#include "ColorGenerator.h"

ColorGenerator::ColorGenerator()
:m_cursor(0)
{
	m_palette.push_back(sf::Color(0, 0, 0));
	m_palette.push_back(sf::Color(0, 0, 255));
	m_palette.push_back(sf::Color(0, 255, 0));
	m_palette.push_back(sf::Color(0, 255, 255));
	m_palette.push_back(sf::Color(255, 0, 0));
	m_palette.push_back(sf::Color(255, 0, 255));
	m_palette.push_back(sf::Color(255, 255, 0));
	m_palette.push_back(sf::Color(255, 255, 255));
}

std::size_t ColorGenerator::getPaletteSize() const{
	return m_palette.size();
}

sf::Color ColorGenerator::getColor(std::size_t i){
	while(i >= getPaletteSize()){
		generateNewColor();
	}
	return m_palette[i];
}

sf::Color ColorGenerator::generateNewColor(){
	unsigned q = m_cursor/8;
	unsigned r = m_cursor%8 + 1;
	
	sf::Color newColor = m_palette[q]*sf::Color(127, 127, 127) + m_palette[r]*sf::Color(127, 127, 127);
	m_palette.push_back(newColor);
	
	++m_cursor;
	return newColor;
}
