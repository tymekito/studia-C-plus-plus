#include"Postacie.h"
//Tekstura+Frame(ramka)=Sprite
void Postac::_setDefaultFramePosition()	//ustawia vektor wyci�cia w zale�no�� od kierunku
{
	this->framePosition[0] = sf::Vector2i(0, 0);//pierwszy wyci�ty fragment 
	this->framePosition[1] = sf::Vector2i(0 * this->xFrameSize, 1 * this->yFrameSize);	//drugiwyci�ty fragment 
	this->framePosition[2] = sf::Vector2i(0 * this->xFrameSize, 2 * this->yFrameSize);	//trzeci wyci�ty fragment 
	this->framePosition[3] = sf::Vector2i(0 * this->xFrameSize, 3 * this->yFrameSize);	//czwarty wyci�ty fragment 
	//wycinany obrazek dzielimy na 4 cz�ci ka�da cz�� zawiera obruconego w inn� stron� ludka
}
Ludek::Ludek(const sf::Vector2f &vec, const string &filename, int xFrameSize, int yFrameSize, int PositionX, int PositionY) 
{
	//ustawienie wyskoko�ci i szeroko�ci wycinanej ramki 
	this->xFrameSize = xFrameSize;
	this->yFrameSize = yFrameSize;
	this->setSize(vec);//ustawienie rozmiaru wy�wietlanego sprite'a
	sf::Texture *tex = new sf::Texture; //tworze teksture poprzez wskaznik przypisuje pamiec 
	this->_setDefaultFramePosition();//ustaw ludzika ten numerek w tablicy 
	tex->loadFromFile(filename);//za�aduj teksture 
	this->setTexture(tex, true);//ustawiam teksture bez tego mamy shape bez pliku 
	this->setPosition(PositionX, PositionY); //ustaw pozycje sprite'a na bitmapie
	this->updateTextureRect();//sprite wywo�uje metode kt�ra ustawia jego ramk� tekstury
}
void Ludek::updateTextureRect() {
	this->setTextureRect(sf::IntRect(this->framePosition[this->kierunek].x, this->framePosition[this->kierunek].y, this->xFrameSize, this->yFrameSize));	
  //ustawia ramke sprite'a 	IntRect	(prostok�t o wymiarach int na int)	 oraz obrazek jaki ma wy�wietla� 
}
void Ludek::ruch(sf::Event &e, sf::Time T) {
	int stepx = 0, stepy = 0;//krok y krok x ludek przesuwa si� o 40 ptk po bit mapie 
	if (e.type == sf::Event::KeyPressed)   //je�eli naci�ni�to klawisz
	{
		switch (e.key.code) //w zale�no�ci jaki klawisz wci�ni�to wykonaj odpowiedni� instrukcj� 
		{
		case sf::Keyboard::W://UP
			this->kierunek = 0;
			stepy = -this->step;
			stepx = 0;
			this->setPosition((this->getPosition().x + stepx * T.asSeconds() * 2), (this->getPosition().y + stepy * T.asSeconds() * 2));   //przesuni�cie o odpowiedni� liczb� pikseli w czasie obiektu 
			break;
		case sf::Keyboard::D://Right
			this->kierunek = 1;
			stepy = 0;
			stepx = this->step;
			this->setPosition((this->getPosition().x + stepx * T.asSeconds() * 2), (this->getPosition().y + stepy * T.asSeconds() * 2));
			break;
		case sf::Keyboard::S://Dwon
			this->kierunek = 2;
			stepy = this->step;
			stepx = 0;
			this->setPosition((this->getPosition().x + stepx * T.asSeconds() * 2), (this->getPosition().y + stepy * T.asSeconds() * 2));
			break;
		case sf::Keyboard::A://Left
			this->kierunek = 3;
			stepy = 0;
			stepx = -this->step;
			this->setPosition((this->getPosition().x + stepx * T.asSeconds() * 2), (this->getPosition().y + stepy * T.asSeconds() * 2));
			break;
		}

		this->updateTextureRect();//zmiana  wy�wietlanego obrazka  w zale�no��i od kierunku 

	}
}
bool Ludek::zyje(vector<Postac*>postac)
{
	//ustawienie iteratora na pocz�tek vectora
	for (auto t = postac.begin(); t < postac.end(); t++)  //iteracja po ca�ym vektorze
	{
		Postac *tmp = *t;	//wskaznik pomocniczy 
		if ((this->getGlobalBounds().intersects(tmp->getGlobalBounds()) && typeid(*tmp) == typeid(Duch)))	//je�eli dosz�o do kolizji z obiektem oraz je�eli jego typ to Duch
			return false;	//je�eli dosz�o do kolizji														//wykorzystanie RTTI kontener�w oraz iterator�w
	}
	return true;	  //je�eli nie dosz�o do kolizji
}
int Ludek::get_liczba_zyc()
{
	return this->liczba_zyc;  //zwraca warto�� zmiennej
}
void Ludek::set_liczba_zyc(int nowa)
{
	this->liczba_zyc = nowa;  //ustawia warto�� liczba_zyc na now� warto��
}
Duch::Duch(const sf::Vector2f &vec, const string &filename, int xFrameSize, int yFrameSize, int PositionX, int PositionY) {//vector z rozmiarem jaki ma by� wy�wetlany  _ nazwa pliku do wczytania _
	 //ustawienie wyskoko�ci i szeroko�ci wycinanej ramki 
	this->xFrameSize = xFrameSize;
	this->yFrameSize = yFrameSize;
	this->setSize(vec);			//ustawienie rozmiaru wy�wietlanego sprite'a
	sf::Texture *tex = new sf::Texture; //tworze teksture poprzez wskaznik przypisuje pamiec 
	this->_setDefaultFramePosition();//ustaw ludzika ten numerek w tablicy 
	tex->loadFromFile(filename);//za�aduj teksture 
	this->setTexture(tex, true);//ustawiam teksture bez tego mamy shape bez pliku 
	this->setPosition(PositionX, PositionY);  //ustaw pozycje sprite'a na bitmapie
	this->updateTextureRect(); //sprite wywo�uje metode kt�ra ustawia jego ramk� tekstury
}
void Duch::updateTextureRect() {//to co ustawi�a SDFP zosta�o wpisane do parametru framePosition
	this->setTextureRect(sf::IntRect(this->framePosition[this->kierunek].x, this->framePosition[this->kierunek].y, this->xFrameSize, this->yFrameSize));	
	//ustawia ramke sprite'a 	IntRect	(prostok�t o wymiarach int na int)	 oraz obrazek jaki ma wy�wietla� 
}
void Duch::ruch(sf::Event &e, sf::Time T) {
	int stepy = 0, stepx = 0;
	switch (this->kierunek)		//na podstawie posiadanego kierunku   wykonaj instrukcj� 
	{
	case 0:		  //up

		stepy = -this->step;	 //ustaw  krok x 
		stepx = 0;					  //ustaw krok y 
		this->setPosition((this->getPosition().x + stepx * T.asSeconds()), (this->getPosition().y + stepy * T.asSeconds()));//przesu� pozycje sprite'a o powy�sz� warto�� *czas T
		this->updateTextureRect();	//aktualizuj ramk� 
		break;
	case 1:		 //right

		stepy = 0;
		stepx = this->step;
		this->setPosition((this->getPosition().x + stepx * T.asSeconds()), (this->getPosition().y + stepy * T.asSeconds()));
		this->updateTextureRect();
		break;
	case 2:		 //down
		stepy = this->step;;
		stepx = 0;
		this->setPosition((this->getPosition().x + stepx * T.asSeconds()), (this->getPosition().y + stepy * T.asSeconds()));
		this->updateTextureRect();
		break;
	case 3:		 //left

		stepy = 0;
		stepx = -this->step;
		this->setPosition((this->getPosition().x + stepx * T.asSeconds()), (this->getPosition().y + stepy * T.asSeconds()));
		this->updateTextureRect();
		break;

	}
	return;
}

void ustawDroge(Postac * postac, vector<Ksztalt*>ksztalty)
{//argumenty: postac (obiekt klasy postac kt�ry kolidowa� i trzeba ustawi� mu nowy dost�pny kierunek
// ksztalty vector klasy Ksztalt czyli obiektow statycznych na ktorych podstawie sprawdzana bedzie kolizja
	int max = 0, tmp = 0, licznik = 0, ostrzezenie = 0;
	int tab[4] = { 8,8,8,8 };  //tablica przechowywuj�ca dost�pne kierunki, bazowo wype�niona warto�ciami '8'
	sf::Vector2f wektor(postac->getPosition().x, postac->getPosition().y);	 //pozycje pocz�tkowe postaci
	for (int i = 0; i < 4; i++)
	{
		switch (i) {
		case 0:			  //W	 -50 y

			if (i == postac->get_kierunek())	//je�eli r�ne aktualnemu kiernkowi 
			{
				break;
			}
			else {
				ostrzezenie = 0;  //flaga czy wykryto klocek (obiekt kolizyjny )
				postac->setPosition(postac->getPosition().x, postac->getPosition().y - ROZMIAR);//ustawienie postaci na pozycje podejrzan� o kolizje 

				for (auto t = ksztalty.begin(); t != ksztalty.end(); t++)
				{
					Ksztalt *ptr = *t;
					if (postac->getGlobalBounds().intersects(ptr->getGlobalBounds()) && (typeid(*ptr) == typeid(Klocek)))//sprawdzenie kolizji oraz typu obiektu 
					{
						ostrzezenie = 1;	 //je�eli wykryto ustaw flage na 1 
						postac->setPosition(wektor);//ustaw postac na pozycje poczatkow�
						break;
					}
				}
				if (ostrzezenie == 0)
				{
					tab[i] = i;		//jezeli nie bylo kolizji wpisz kierunek do tablicy 
					postac->setPosition(wektor);  //ustaw na pozycje poczatkowa 
					break;
				}
				break;
			}
		case 1:			 //D   +50x

			if (i == postac->get_kierunek())
			{
				break;
			}
			else {
				ostrzezenie = 0;
				postac->setPosition(postac->getPosition().x + ROZMIAR, postac->getPosition().y);

				for (auto t = ksztalty.begin(); t != ksztalty.end(); t++)
				{
					Ksztalt *ptr = *t;
					if (postac->getGlobalBounds().intersects(ptr->getGlobalBounds()) && (typeid(*ptr) == typeid(Klocek)))
					{
						ostrzezenie = 1;
						postac->setPosition(wektor);
						break;
					}
				}
				if (ostrzezenie == 0) {
					tab[i] = i;
					postac->setPosition(wektor);
					break;
				}
				break;
			}

		case 2:			//S	  +50 y

			if (i == postac->get_kierunek())
			{
				break;
			}
			else {
				ostrzezenie = 0;
				postac->setPosition(postac->getPosition().x, postac->getPosition().y + ROZMIAR);

				for (auto t = ksztalty.begin(); t != ksztalty.end(); t++)
				{
					Ksztalt *ptr = *t;
					if (postac->getGlobalBounds().intersects(ptr->getGlobalBounds()) && (typeid(*ptr) == typeid(Klocek)))
					{
						ostrzezenie = 1;
						postac->setPosition(wektor);
						break;
					}
				}
				if (ostrzezenie == 0) {
					tab[i] = i;
					postac->setPosition(wektor);
					break;
				}

				break;
			}
		case 3:			//A		  -50x

			if (i == postac->get_kierunek())
			{
				break;
			}
			else {
				ostrzezenie = 0;
				postac->setPosition(postac->getPosition().x - ROZMIAR, postac->getPosition().y);

				for (auto t = ksztalty.begin(); t != ksztalty.end(); t++)
				{
					Ksztalt *ptr = *t;
					if (postac->getGlobalBounds().intersects(ptr->getGlobalBounds()) && (typeid(*ptr) == typeid(Klocek)))
					{
						ostrzezenie = 1;
						postac->setPosition(wektor);
						break;
					}
				}
				if (ostrzezenie == 0) {
					tab[i] = i;
					postac->setPosition(wektor);
					break;
				}

				break;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (tab[i] == 8)  //8 w tym kierunku by�a kolizja bo nie wpisano innej warto�� (8 warto�� domy�lna tablicy) "nic nie r�b"
		{ }
		else		 //w kom�rce znajduje si� dozwolona warto��	kt�ra wskazuje na kierunek 
		{
			tab[i] = rand() % 100 + 9;	//wpisz warto�� losow� z przediza�u 9-108,w kom�rki kt�rych indeksy nie s� zabronionymi kierunkami 
		}
	}
	//wybieramy maxymaln� warto�� umieszczon� w tablicy 
	for (int i = 0; i < 4; i++)
	{
		if (tab[i] > max)
		{
			max = tab[i];
			licznik = i;
		}
	}
	//indeks maksymalnej warto��i to nasz nowy kierunek	  zmienna licznik

	postac->set_kierunek(licznik);	 //ustawienie nowego kierunku postaci
	postac->setPosition(wektor);	  //ustawienie postaci na pozycje pocz�tkow� 

}
