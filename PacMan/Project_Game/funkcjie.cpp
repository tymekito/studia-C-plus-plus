#include"funkcjie.h"
void createMyWindow(sf::RenderWindow &W, sf::String s)
{
	W.create(sf::VideoMode(SCREENX, SCREENY, CBITS), s);	//tworzymy okno o rozmiarze SCREEN X na SCREEN Y o g��bi kolor�w CBITS  o nazwie String
	W.setActive(true); //ustawiamy aktywno�� okna (mo�liwo�� jego poruszania)
	W.setFramerateLimit(FRAME_LIMIT); // cz�stotliwo�� wy�wietlania obrazk�w podobne do fps FRAME_LIMIT
	W.setPosition(sf::Vector2i(POSX, POSY));  // ustawienie pozycji pocz�tkowej rysowania okna na ekranie (domy�lnie 0,0)
	W.setKeyRepeatEnabled(true);//obs�uga przycisk�w funkcyjnych okna
}
