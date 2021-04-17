#ifndef COLOR_GENERATOR_H
#define COLOR_GENERATOR_H_H

#include <SFML/Graphics.hpp>
#include <vector>

class ColorGenerator
{
public :
	
	ColorGenerator();
	
	std::size_t getPaletteSize() const;
	sf::Color getColor(std::size_t);
	sf::Color generateNewColor();
	
private :
	
	std::vector<sf::Color> m_palette;
	unsigned m_cursor;
};

#endif // COLOR_GENERATOR_H
