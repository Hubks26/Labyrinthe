#ifndef LABIRYNTH_H
#define LABIRYNTH_H

#include "ColorGenerator.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

class Labirynth : public sf::Drawable
{
public :
	
	Labirynth();
	
	void update();
	
private :
	
	void init();
	void ending();
	void merge(sf::Vector2u, sf::Vector2u);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	void print() const;
	
private :
	
	static const std::size_t m_row = 65; //65
	static const std::size_t m_col = 135; //135 (tpf == 1/600)
	std::vector<std::vector<int>> m_table;
	std::vector<sf::Vector2u> m_wallToCheck;
};

#endif // LABIRYNTH_H
