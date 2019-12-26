#pragma once
#include"Ksztalty.h"
#define STEP 200//liczba pix jak¹ poruszy siê ludek
#define ZYCIA 3//liczba ¿yæ jak¹ posiada ludek
using namespace std;
/*
Klasa reprezentuje Postac, dziedziczy ona po klasie reprezentujacej kszta³t przez SFML
Cechy: obiekt poruszaj¹cy siê
Zmienne: 
xFrameSize,yFrameSize wysokoœæ szerokoœæ wczytanego obrazu postaci	
framePosition   zawiera pozycje w któr¹ stronê obrócon¹ jest ludzik oraz vector jaki ma zostac wyciety z pliku graficznego
// 0 - up, 1-right, 2-down, 3-left
step (odleglosc z jaka przesuwa sie postac)
Metody
   _setDefaultFramePosition(ustawia kierunek postaci poprzez wyciecie odpowiedniego kwadratu ktorego rozmiar (vectora) reprezentuje 	  framePosition
   updateTextureRect metoda wirtualana wycina z obrazu w zale¿noœci od kiernku inny kwadrat co ma powodowaæ animacje
	ruch przesuwa ludzika po bitmapie w zaleznosci od eventu oraz kierunku w jakim jest ustawiony
	get/set ustawia/pobiera kierunek w jakim znajduje sie ludek
   */
class Ksztalt;
class Postac :public sf::RectangleShape
{
protected:
	int xFrameSize = 0;
	int yFrameSize = 0; 
	int step = STEP;
	sf::Vector2i framePosition[4]; 
	void _setDefaultFramePosition();  
public:
	int kierunek = 3;
	virtual void updateTextureRect() = 0;  
	virtual void ruch(sf::Event &, sf::Time ) = 0;
	int get_kierunek() { return this->kierunek; }; 
	void set_kierunek(int wartosc) { this->kierunek = wartosc; };
};
/*
Klasa reprezentuje ludka, dziedziczy ona po klasie abstrakcyjnej postac
Cechy: g³ówna postaæ któr¹ porusza siê gracz
Metody zyje (sprawdza czy nie dosz³o do kolizji Ludek-Postac)
*/
class Ludek :public Postac {
private:
	unsigned int liczba_zyc = ZYCIA;
public:
	Ludek(const sf::Vector2f &, const std::string &, int, int, int, int);
	void updateTextureRect();
	void ruch(sf::Event &, sf::Time );
	bool zyje(vector<Postac*>);
	int get_liczba_zyc();
	void set_liczba_zyc(int);
};

/*
Klasa reprezentuje ducha(postac kolizyjn¹ z ludkiem), dziedziczy ona po klasie abstrakcyjnej postac
Cechy: postac która po wejœciu w kolizjê z ludkiem "zabija go"
*/
class Duch :public Postac
{

public:

	Duch(const sf::Vector2f &, const std::string &, int, int, int, int);
	void updateTextureRect();
	void ruch(sf::Event &, sf::Time );
};

void ustawDroge(Postac *, vector<Ksztalt*>);