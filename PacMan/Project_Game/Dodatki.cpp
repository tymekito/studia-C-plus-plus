#include"Dodatki.h"
Napis::Napis(const sf::Vector2f&pos)
{
	czcionka.loadFromFile("OpenSans-Light.ttf");//za�adowanie czcionki 
	sf::Texture Timer;
	Timer.loadFromFile("grafika/timer.png");   //za�adowanie grafiki
	sf::Sprite Timery;
	Timery.setTexture(Timer, true);	//ustawienie textury sprite'a jako active
	Timery.setPosition(pos);		  //ustawienie parametrow Sprite'a
	this->ss.str(" ");	  //ustawienie  domy�lnych danych w strumieniu stringow
	this->ss << this->punkty;	//wpisanie do niego domy�lnych danych
	this->str.setFont(czcionka);	//ustawienie cziocnki 
	this->str.setPosition(pos.x -80, pos.y);//ustawienie pozycji okna na Bitmapie
	this->str.setString(ss.str());//ustawienie wy�wietlanego tekstu 
	str.setFillColor(sf::Color::Green);//ustawienie koloru wy�wietlanego tekstu
	str.setCharacterSize(40);	  //ustawienie rozmiaru wy�wietlanego tekstu 
}
void Napis::draw(sf::RenderWindow &W, int T)
{
	this->ss.str(" ");	//wyczyszczenie aktualanego tesktu 
	this->ss << "Punkty: ";	//wpisanie strumieniami  s�owa punkty
	this->ss << (T);//wpisanie strumieniami warto�ci do wy�wietlenia
	this->str.setString(ss.str()); //ustawienie wy�wietlanego stringa 
	W.draw(this->str);	// wy�wietlenie stringa  w oknie W 
}
Okno::Okno(string nazwa, int X, int Y) : nazwa_grafiki(nazwa), pozycjaX(X), pozycjaY(Y)	 //argumenty wczytanie za pomoc� listy inizjalizacyjnej 
{
	this->Tlo.loadFromFile(this->nazwa_grafiki);   //za�adowanie t�a
	Spr.setPosition(this->pozycjaX, this->pozycjaY);  //ustawienie pozycji
	Spr.setTexture(Tlo);  //ustawia tekstur� sprite'a

}
