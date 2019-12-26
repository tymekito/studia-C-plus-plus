#include"Ksztalty.h"
//Tekstura+Frame=Sprite
Klocek::Klocek(const sf::Vector2f vec, std::string filename, float PositionX, float PositionY)
{
	this->setSize(vec);	//ustawienie rozmiaru wy�wietlanego sprite'a
	sf::Texture *tex = new sf::Texture; //tworze teksture poprzez wskaznik przypisuje pamiec 
	tex->loadFromFile(filename);//wczytanie grafiki z podanego pliku do tekstury
	this->setTexture(tex, true);//ustawiam teksture bez tego mamy shape bez pliku 	
	this->setPosition(PositionX, PositionY); //ustawienie pozycji Sprite'a na Bitmapue
}
bool Klocek::kolizja(Postac*L, sf::Time T)
{
	if (L->getGlobalBounds().intersects(this->getGlobalBounds())) //wykryto kolizje 
	{
			//sprawdzamy w kt�rym kierunku porusza� si� obiekt
			if (L->get_kierunek() == 0)//W g�ra 
				L->setPosition(L->getPosition().x, L->getPosition().y + STEP * T.asSeconds());
			else if (L->get_kierunek() == 1)//D prawo
				L->setPosition(L->getPosition().x - STEP*T.asSeconds(), L->getPosition().y);
			else if (L->get_kierunek() == 2)//S d� 
				L->setPosition(L->getPosition().x, L->getPosition().y - STEP * T.asSeconds());
			else //  (L->kierunek == 3)//A lewo
				L->setPosition(L->getPosition().x + STEP * T.asSeconds(), L->getPosition().y);
			//po jego przesuni�ciu zwracamy warto�� true
			return true;
	}
	//je�eli nie nast�pi�a kolizja 
	else
		return false;
}													
Moneta ::Moneta(const sf::Vector2f vec, std::string filename, float PositionX, float PositionY)
{
	this->setSize(vec);	 //ustawienie rozmiaru wy�wietlanego Sprite'a
	sf::Texture *tex = new sf::Texture; //tworze teksture poprzez wskaznik przypisuje pamiec 
	tex->loadFromFile(filename);  //za�adowanie grafiki wy�wietlanej tekstury 
	this->setTexture(tex, true);//ustawienie tekstury jako aktywnego sprite'a 
	this->setPosition(PositionX, PositionY);  //ustawienie pozycji Sprite'a na Bitmapue
}
bool Moneta::kolizja(Postac*L, sf::Time T)
{
	if (L->getGlobalBounds().intersects(this->getGlobalBounds())) //sprawdznie czy dosz�o do kolizji
	{   //sprawdzmay jakiego typu by� koliduj�cy obiekt 
		if( typeid(*L) == typeid(Ludek))  //u�ycie RTTI 
			return true;
		//je�eli by� to Ludek zwracamy true 
		if (typeid(*L) == typeid(Duch))	//u�ycie RTTI 
			return false;
		//je�eli by� to duch zwracamy false 
	}
	else
		return false;

}



