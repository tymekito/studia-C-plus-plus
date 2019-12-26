#include"Dodatki.h"
Napis::Napis(const sf::Vector2f&pos)
{
	czcionka.loadFromFile("OpenSans-Light.ttf");//za³adowanie czcionki 
	sf::Texture Timer;
	Timer.loadFromFile("grafika/timer.png");   //za³adowanie grafiki
	sf::Sprite Timery;
	Timery.setTexture(Timer, true);	//ustawienie textury sprite'a jako active
	Timery.setPosition(pos);		  //ustawienie parametrow Sprite'a
	this->ss.str(" ");	  //ustawienie  domyœlnych danych w strumieniu stringow
	this->ss << this->punkty;	//wpisanie do niego domyœlnych danych
	this->str.setFont(czcionka);	//ustawienie cziocnki 
	this->str.setPosition(pos.x -80, pos.y);//ustawienie pozycji okna na Bitmapie
	this->str.setString(ss.str());//ustawienie wyœwietlanego tekstu 
	str.setFillColor(sf::Color::Green);//ustawienie koloru wyœwietlanego tekstu
	str.setCharacterSize(40);	  //ustawienie rozmiaru wyœwietlanego tekstu 
}
void Napis::draw(sf::RenderWindow &W, int T)
{
	this->ss.str(" ");	//wyczyszczenie aktualanego tesktu 
	this->ss << "Punkty: ";	//wpisanie strumieniami  s³owa punkty
	this->ss << (T);//wpisanie strumieniami wartoœci do wyœwietlenia
	this->str.setString(ss.str()); //ustawienie wyœwietlanego stringa 
	W.draw(this->str);	// wyœwietlenie stringa  w oknie W 
}
Okno::Okno(string nazwa, int X, int Y) : nazwa_grafiki(nazwa), pozycjaX(X), pozycjaY(Y)	 //argumenty wczytanie za pomoc¹ listy inizjalizacyjnej 
{
	this->Tlo.loadFromFile(this->nazwa_grafiki);   //za³adowanie t³a
	Spr.setPosition(this->pozycjaX, this->pozycjaY);  //ustawienie pozycji
	Spr.setTexture(Tlo);  //ustawia teksturê sprite'a

}
