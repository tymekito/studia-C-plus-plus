#pragma once
//do³¹czone biblioteki zewnêtrzne 
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML\Window.hpp>
#include<vector>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include"Postacie.h"
//define
#define POSX 200//pozycja X na ekranie
#define POSY 25//pozycja Y na ekranie 
#define SCREENX 1200//szerokoœc ekranu
#define SCREENY 800//wysokoœæ ekranu 
#define CBITS 32//g³êbia kolorów trybu graficznego 
#define FRAME_LIMIT 60//liczba fpsów
#define ROZMIAR 50 //rozmiar obiektu kwadrat 50x50
#define HITBOX 45 //rozmiar ludka z jakim ma dojsc do kolizji
#define STEP 200//rozmiar kroku po bitmapie
#define PUNKTOR 10//definiuje ile punktow dostaje gracz za monete
#define ZYCIA 3	 //liczba zyc ludka
#define DUCH 'G'//reprezentacja char duszka
#define KLOCEK 'O'//reprezentacja char kamienia
#define MONETA 'D'//reprezentacja char monety
#define LUDEK '#'//reprezentacja char ludka

using namespace std;
//Classy
class Postac;
class Ludek;
class Napis;
class Ksztalt :public sf::RectangleShape
{
protected:
	const unsigned int destructable = 0;  // zmienna definiuje czy obiekt jest zniszczalny zwraca 0,1
public:
	virtual bool kolizja(Postac*,sf::Time) = 0;	 //metoda wirtualna sprawdza czy doszlo do kolizi obiketu z obiketem clasy postac
	virtual int test() = 0; //sprawdza czy obiekt jest zniszczalny poprzez zwrocenie 0albo 1
};
/*
Klasa reprezentuje klocka
Cechy: obiekt clasy postac nie moze przez niego przesc
Zmienne: desctrutable =1 (nie jest zniszalny)
Metody: kolizja (Postac Ludek),	test zwraca destrutable
*/
class Klocek :public Ksztalt		
{
protected:
	const unsigned int destructable = 1;
public :
		Klocek(const sf::Vector2f , std::string , float , float );
	
		bool kolizja(Postac*, sf::Time T);
		int test()
		{
			return this->destructable;
		}
};
/*
Klasa reprezentuje Monete
Cechy: obiekt clasy postac  moze przez niego przesc oraz dostaje punkty w trakcie kolizji
Zmienne: desctrutable =0 (nie jest zniszalny)
Metody: kolizja (Postac Ludek),test zwraca destrutable
*/
class Moneta :public Ksztalt
{
protected:
	const unsigned int destructable = 0;
public:
		Moneta(const sf::Vector2f , std::string , float , float );
		
		bool kolizja(Postac*, sf::Time T);
		int test() {return this->destructable;}
};
	

