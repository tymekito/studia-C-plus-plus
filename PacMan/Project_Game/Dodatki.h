#pragma once
#include"Ksztalty.h"
/*
Klasa reprezentuje Napis
Cechy: Dziedziczy po clasie kszta�t SFML, oraz po clasie Font SFML,s�u�y do generowania napis�w na bitmapie
Zmienne: czcionka(rodzaj wy�wietlanej czcionki), punkty (liczba punkt�w jakie ma obiket wyswietla�),str(Textura wy�wietlanego napisu)
ss(strumien string�w s�u�y do przechowywania danych do wy�wietlenia)
Metody: draw (rysuje obiekt w oknie ),geter zwracaj�cy punkty , zwieksz(ustawia punkty o z definiowan� w programie liczbe punktow +ew.bonus
*/
class Napis : public sf::RectangleShape, sf::Font
{
private:
	sf::Font czcionka;
	unsigned int punkty = 0;
	sf::Text str;
	stringstream ss;

public:
	Napis(const sf::Vector2f&);
	void draw(sf::RenderWindow &, int);
	int getPunkty() { return this->punkty; };
	void setPunkty(int liczba) { this->punkty = liczba; };
	void zwieksz(int bonus)
	{
		this->punkty += PUNKTOR;
		this->punkty += bonus;
	}
};
/*
Klasa reprezentuje wyskakujace Okno 
Cechy: Dziedziczy po clasie kszta�t SFML, oraz po clasie Font SFML,s�u�y do generowania napis�w na bitmapie
Zmienne:  pozycja X/Y okna na bitmapie, nazwa_grafiki nazwa pliku z kt�rego ma zostac wczytana wyswietlona grafika
Tlo Textura (obraz)SFML okna, Spr (sprite,duszek) faktura wy�wietlanego obiektu 
Metody:
set_nazwa_grafiki ustawia nazwe grafiki i �aduje j� do Textury metod� loadFromFile 
set_pozycja	ustawia pozycje X i Y sprite'a, metod� setPosition
*/
class Okno :public sf::RectangleShape
{
private:
	int pozycjaX = 0, pozycjaY = 0;
	string nazwa_grafiki;
public:
	sf::Texture Tlo;
	sf::Sprite Spr;
	Okno() {};
	Okno(string nazwa, int X, int Y);
	~Okno() {};
	void set_nazwa_grafiki(string nowa) 
	{
		this->nazwa_grafiki = nowa;
		this->Tlo.loadFromFile(this->nazwa_grafiki);
	}
	void set_pozycja(int x, int y)	  
	{
		this->pozycjaX = x;
		this->pozycjaY = y;
		Spr.setPosition(this->pozycjaX, this->pozycjaY);
	}
};