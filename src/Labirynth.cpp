#include "Labirynth.h"

Labirynth::Labirynth()
:m_table(m_row, std::vector<int>(m_col, -1))
{
	init();
}

void Labirynth::update(){
	if(m_wallToCheck.size()>0){
		unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> distU(0, m_wallToCheck.size()-1);
		
		int index = distU(generator);
		sf::Vector2u wall = m_wallToCheck[index];
		
		if(wall.x%2==0 && m_table[wall.x-1][wall.y] != m_table[wall.x+1][wall.y]){
			m_table[wall.x][wall.y] = m_table[wall.x-1][wall.y];
			merge(sf::Vector2u(wall.x-1, wall.y), sf::Vector2u(wall.x+1, wall.y));
		}
		else if(m_table[wall.x][wall.y-1] != m_table[wall.x][wall.y+1]){
			m_table[wall.x][wall.y] = m_table[wall.x][wall.y-1];
			merge(sf::Vector2u(wall.x, wall.y-1), sf::Vector2u(wall.x, wall.y+1));
		}
		
		m_wallToCheck.erase(m_wallToCheck.begin() + index);
	}
	else if(m_table[1][0] == m_table[1][1]){
		ending();
		std::cout << "\nLabyrinth is created\n" << std::endl;
	}
}

void Labirynth::init(){
	unsigned color = 1;
	
	for (std::size_t i = 0; i < m_col; ++i)
	{
		for (std::size_t j = 0; j < m_row; ++j)
		{
			if(i%2 == 1 && j%2 == 1){
				m_table[j][i] = color++;
			}
			if(i != 0 && j != 0 && i != m_col-1 && j != m_row-1 && (i+j)%2 == 1){
				m_wallToCheck.push_back(sf::Vector2u(j,i));
			}
		}
	}
	
	m_table[1][0] = m_table[1][1];
	m_table[m_row-2][m_col-1] = m_table[m_row-2][m_col-2];
}

void Labirynth::ending(){	
	for (std::size_t i = 0; i < m_col; ++i)
	{
		for (std::size_t j = 0; j < m_row; ++j)
		{
			if(m_table[j][i] > 0){
				m_table[j][i] = 0;
			}
			else{
				m_table[j][i] = 7;
			}
		}
	}
	
	m_table[1][0] = 2;
	m_table[m_row-2][m_col-1] = 4;
}

void Labirynth::merge(sf::Vector2u cell1, sf::Vector2u cell2){
	int c1Value = m_table[cell1.x][cell1.y];
	int c2Value = m_table[cell2.x][cell2.y];
	
	for (std::size_t i = 0; i < m_col; ++i)
	{
		for (std::size_t j = 0; j < m_row; ++j)
		{
			if(m_table[j][i] == c2Value){
				m_table[j][i] = c1Value;
			}
		}
	}
}

void Labirynth::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ColorGenerator cg;
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f((target.getSize().x+1.f)/(m_col+2), (target.getSize().y+1.f)/(m_row+2)));
	
	for (std::size_t i = 0; i < m_col; ++i)
	{
		for (std::size_t j = 0; j < m_row; ++j)
		{
			rectangle.setPosition(((i+1)*target.getSize().x+1.f)/(m_col+2), ((j+1)*target.getSize().y+1.f)/(m_row+2));
			if(m_table[j][i] < 0){
				rectangle.setFillColor(sf::Color(30, 30, 30));
			}
			else{
				rectangle.setFillColor(cg.getColor(m_table[j][i]));
			}
			target.draw(rectangle, states);
		}
	}
	
	rectangle.setPosition((0*target.getSize().x+1.f)/(m_col+2), (1*target.getSize().y+1.f)/(m_row+2));
	rectangle.setFillColor(sf::Color(0, 255, 0));
	target.draw(rectangle, states);
	rectangle.setPosition((0*target.getSize().x+1.f)/(m_col+2), (2*target.getSize().y+1.f)/(m_row+2));
	rectangle.setFillColor(sf::Color(0, 255, 0));
	target.draw(rectangle, states);
	rectangle.setPosition((0*target.getSize().x+1.f)/(m_col+2), (3*target.getSize().y+1.f)/(m_row+2));
	rectangle.setFillColor(sf::Color(0, 255, 0));
	target.draw(rectangle, states);
	
	rectangle.setPosition(((m_col+1)*target.getSize().x+1.f)/(m_col+2), ((m_row-2)*target.getSize().y+1.f)/(m_row+2));
	rectangle.setFillColor(sf::Color(255, 0, 0));
	target.draw(rectangle, states);
	rectangle.setPosition(((m_col+1)*target.getSize().x+1.f)/(m_col+2), ((m_row-1)*target.getSize().y+1.f)/(m_row+2));
	rectangle.setFillColor(sf::Color(255, 0, 0));
	target.draw(rectangle, states);
	rectangle.setPosition(((m_col+1)*target.getSize().x+1.f)/(m_col+2), (m_row*target.getSize().y+1.f)/(m_row+2));
	rectangle.setFillColor(sf::Color(255, 0, 0));
	target.draw(rectangle, states);
}

void Labirynth::print() const{
	for (std::size_t i = 0; i < m_col; ++i)
	{
		for (std::size_t j = 0; j < m_row; ++j)
		{
			std::cout << m_table[j][i] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;
}
