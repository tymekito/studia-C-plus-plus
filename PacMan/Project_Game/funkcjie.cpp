#include"funkcjie.h"
void createMyWindow(sf::RenderWindow &W, sf::String s)
{
	W.create(sf::VideoMode(SCREENX, SCREENY, CBITS), s);	//tworzymy okno o rozmiarze SCREEN X na SCREEN Y o g³êbi kolorów CBITS  o nazwie String
	W.setActive(true); //ustawiamy aktywnoœæ okna (mo¿liwoœæ jego poruszania)
	W.setFramerateLimit(FRAME_LIMIT); // czêstotliwoœæ wyœwietlania obrazków podobne do fps FRAME_LIMIT
	W.setPosition(sf::Vector2i(POSX, POSY));  // ustawienie pozycji pocz¹tkowej rysowania okna na ekranie (domyœlnie 0,0)
	W.setKeyRepeatEnabled(true);//obs³uga przycisków funkcyjnych okna
}
