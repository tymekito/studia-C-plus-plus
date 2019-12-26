#pragma once
#include"Ksztalty.h"
#define STEP 200//liczba pix jak� poruszy si� ludek
#define ZYCIA 3//liczba �y� jak� posiada ludek
using namespace std;
/*
Klasa reprezentuje Postac, dziedziczy ona po klasie reprezentujacej kszta�t przez SFML
Cechy: obiekt poruszaj�cy si�
Zmienne: 
xFrameSize,yFrameSize wysoko�� szeroko�� wczytanego obrazu postaci	
framePosition   zawiera pozycje w kt�r� stron� obr�con� jest ludzik oraz vector jaki ma zostac wyciety z pliku graficznego
// 0 - up, 1-right, 2-down, 3-left
step (odleglosc z jaka przesuwa sie postac)
Metody
   _setDefaultFramePosition(ustawia kierunek postaci poprzez wyciecie odpowiedniego kwadratu ktorego rozmiar (vectora) reprezentuje 	  framePosition
   updateTextureRect metoda wirtualana wycina z obrazu w zale�no�ci od kiernku inny kwadrat co ma powodowa� animacje
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
Cechy: g��wna posta� kt�r� porusza si� gracz
Metody zyje (sprawdza czy nie dosz�o do kolizji Ludek-Postac)
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
Klasa reprezentuje ducha(postac kolizyjn� z ludkiem), dziedziczy ona po klasie abstrakcyjnej postac
Cechy: postac kt�ra po wej�ciu w kolizj� z ludkiem "zabija go"
*/
class Duch :public Postac
{

public:

	Duch(const sf::Vector2f &, const std::string &, int, int, int, int);
	void updateTextureRect();
	void ruch(sf::Event &, sf::Time );
};

void ustawDroge(Postac *, vector<Ksztalt*>);