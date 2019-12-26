#include"Dodatki.h"
Napis::Napis(const sf::Vector2f&pos)
{
	czcionka.loadFromFile("OpenSans-Light.ttf");//załadowanie czcionki 
	sf::Texture Timer;
	Timer.loadFromFile("grafika/timer.png");   //załadowanie grafiki
	sf::Sprite Timery;
	Timery.setTexture(Timer, true);	//ustawienie textury sprite'a jako active
	Timery.setPosition(pos);		  //ustawienie parametrow Sprite'a
	this->ss.str(" ");	  //ustawienie  domyślnych danych w strumieniu stringow
	this->ss << this->punkty;	//wpisanie do niego domyślnych danych
	this->str.setFont(czcionka);	//ustawienie cziocnki 
	this->str.setPosition(pos.x -80, pos.y);//ustawienie pozycji okna na Bitmapie
	this->str.setString(ss.str());//ustawienie wyświetlanego tekstu 
	str.setFillColor(sf::Color::Green);//ustawienie koloru wyświetlanego tekstu
	str.setCharacterSize(40);	  //ustawienie rozmiaru wyświetlanego tekstu 
}
void Napis::draw(sf::RenderWindow &W, int T)
{
	this->ss.str(" ");	//wyczyszczenie aktualanego tesktu 
	this->ss << "Punkty: ";	//wpisanie strumieniami  słowa punkty
	this->ss << (T);//wpisanie strumieniami wartości do wyświetlenia
	this->str.setString(ss.str()); //ustawienie wyświetlanego stringa 
	W.draw(this->str);	// wyświetlenie stringa  w oknie W 
}
Okno::Okno(string nazwa, int X, int Y) : nazwa_grafiki(nazwa), pozycjaX(X), pozycjaY(Y)	 //argumenty wczytanie za pomocą listy inizjalizacyjnej 
{
	this->Tlo.loadFromFile(this->nazwa_grafiki);   //załadowanie tła
	Spr.setPosition(this->pozycjaX, this->pozycjaY);  //ustawienie pozycji
	Spr.setTexture(Tlo);  //ustawia teksturę sprite'a

}
