#include"Postacie.h"
//Tekstura+Frame(ramka)=Sprite
void Postac::_setDefaultFramePosition()	//ustawia vektor wyciêcia w zale¿noœæ od kierunku
{
	this->framePosition[0] = sf::Vector2i(0, 0);//pierwszy wyciêty fragment 
	this->framePosition[1] = sf::Vector2i(0 * this->xFrameSize, 1 * this->yFrameSize);	//drugiwyciêty fragment 
	this->framePosition[2] = sf::Vector2i(0 * this->xFrameSize, 2 * this->yFrameSize);	//trzeci wyciêty fragment 
	this->framePosition[3] = sf::Vector2i(0 * this->xFrameSize, 3 * this->yFrameSize);	//czwarty wyciêty fragment 
	//wycinany obrazek dzielimy na 4 czêœci ka¿da czêœæ zawiera obruconego w inn¹ stronê ludka
}
Ludek::Ludek(const sf::Vector2f &vec, const string &filename, int xFrameSize, int yFrameSize, int PositionX, int PositionY) 
{
	//ustawienie wyskokoœci i szerokoœci wycinanej ramki 
	this->xFrameSize = xFrameSize;
	this->yFrameSize = yFrameSize;
	this->setSize(vec);//ustawienie rozmiaru wyœwietlanego sprite'a
	sf::Texture *tex = new sf::Texture; //tworze teksture poprzez wskaznik przypisuje pamiec 
	this->_setDefaultFramePosition();//ustaw ludzika ten numerek w tablicy 
	tex->loadFromFile(filename);//za³aduj teksture 
	this->setTexture(tex, true);//ustawiam teksture bez tego mamy shape bez pliku 
	this->setPosition(PositionX, PositionY); //ustaw pozycje sprite'a na bitmapie
	this->updateTextureRect();//sprite wywo³uje metode która ustawia jego ramkê tekstury
}
void Ludek::updateTextureRect() {
	this->setTextureRect(sf::IntRect(this->framePosition[this->kierunek].x, this->framePosition[this->kierunek].y, this->xFrameSize, this->yFrameSize));	
  //ustawia ramke sprite'a 	IntRect	(prostok¹t o wymiarach int na int)	 oraz obrazek jaki ma wyœwietlaæ 
}
void Ludek::ruch(sf::Event &e, sf::Time T) {
	int stepx = 0, stepy = 0;//krok y krok x ludek przesuwa siê o 40 ptk po bit mapie 
	if (e.type == sf::Event::KeyPressed)   //je¿eli naciœniêto klawisz
	{
		switch (e.key.code) //w zale¿noœci jaki klawisz wciœniêto wykonaj odpowiedni¹ instrukcjê 
		{
		case sf::Keyboard::W://UP
			this->kierunek = 0;
			stepy = -this->step;
			stepx = 0;
			this->setPosition((this->getPosition().x + stepx * T.asSeconds() * 2), (this->getPosition().y + stepy * T.asSeconds() * 2));   //przesuniêcie o odpowiedni¹ liczbê pikseli w czasie obiektu 
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

		this->updateTextureRect();//zmiana  wyœwietlanego obrazka  w zale¿noœæi od kierunku 

	}
}
bool Ludek::zyje(vector<Postac*>postac)
{
	//ustawienie iteratora na pocz¹tek vectora
	for (auto t = postac.begin(); t < postac.end(); t++)  //iteracja po ca³ym vektorze
	{
		Postac *tmp = *t;	//wskaznik pomocniczy 
		if ((this->getGlobalBounds().intersects(tmp->getGlobalBounds()) && typeid(*tmp) == typeid(Duch)))	//je¿eli dosz³o do kolizji z obiektem oraz je¿eli jego typ to Duch
			return false;	//je¿eli dosz³o do kolizji														//wykorzystanie RTTI kontenerów oraz iteratorów
	}
	return true;	  //je¿eli nie dosz³o do kolizji
}
int Ludek::get_liczba_zyc()
{
	return this->liczba_zyc;  //zwraca wartoœæ zmiennej
}
void Ludek::set_liczba_zyc(int nowa)
{
	this->liczba_zyc = nowa;  //ustawia wartoœæ liczba_zyc na now¹ wartoœæ
}
Duch::Duch(const sf::Vector2f &vec, const string &filename, int xFrameSize, int yFrameSize, int PositionX, int PositionY) {//vector z rozmiarem jaki ma byæ wyœwetlany  _ nazwa pliku do wczytania _
	 //ustawienie wyskokoœci i szerokoœci wycinanej ramki 
	this->xFrameSize = xFrameSize;
	this->yFrameSize = yFrameSize;
	this->setSize(vec);			//ustawienie rozmiaru wyœwietlanego sprite'a
	sf::Texture *tex = new sf::Texture; //tworze teksture poprzez wskaznik przypisuje pamiec 
	this->_setDefaultFramePosition();//ustaw ludzika ten numerek w tablicy 
	tex->loadFromFile(filename);//za³aduj teksture 
	this->setTexture(tex, true);//ustawiam teksture bez tego mamy shape bez pliku 
	this->setPosition(PositionX, PositionY);  //ustaw pozycje sprite'a na bitmapie
	this->updateTextureRect(); //sprite wywo³uje metode która ustawia jego ramkê tekstury
}
void Duch::updateTextureRect() {//to co ustawi³a SDFP zosta³o wpisane do parametru framePosition
	this->setTextureRect(sf::IntRect(this->framePosition[this->kierunek].x, this->framePosition[this->kierunek].y, this->xFrameSize, this->yFrameSize));	
	//ustawia ramke sprite'a 	IntRect	(prostok¹t o wymiarach int na int)	 oraz obrazek jaki ma wyœwietlaæ 
}
void Duch::ruch(sf::Event &e, sf::Time T) {
	int stepy = 0, stepx = 0;
	switch (this->kierunek)		//na podstawie posiadanego kierunku   wykonaj instrukcjê 
	{
	case 0:		  //up

		stepy = -this->step;	 //ustaw  krok x 
		stepx = 0;					  //ustaw krok y 
		this->setPosition((this->getPosition().x + stepx * T.asSeconds()), (this->getPosition().y + stepy * T.asSeconds()));//przesuñ pozycje sprite'a o powy¿sz¹ wartoœæ *czas T
		this->updateTextureRect();	//aktualizuj ramkê 
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
{//argumenty: postac (obiekt klasy postac który kolidowa³ i trzeba ustawiæ mu nowy dostêpny kierunek
// ksztalty vector klasy Ksztalt czyli obiektow statycznych na ktorych podstawie sprawdzana bedzie kolizja
	int max = 0, tmp = 0, licznik = 0, ostrzezenie = 0;
	int tab[4] = { 8,8,8,8 };  //tablica przechowywuj¹ca dostêpne kierunki, bazowo wype³niona wartoœciami '8'
	sf::Vector2f wektor(postac->getPosition().x, postac->getPosition().y);	 //pozycje pocz¹tkowe postaci
	for (int i = 0; i < 4; i++)
	{
		switch (i) {
		case 0:			  //W	 -50 y

			if (i == postac->get_kierunek())	//je¿eli róne aktualnemu kiernkowi 
			{
				break;
			}
			else {
				ostrzezenie = 0;  //flaga czy wykryto klocek (obiekt kolizyjny )
				postac->setPosition(postac->getPosition().x, postac->getPosition().y - ROZMIAR);//ustawienie postaci na pozycje podejrzan¹ o kolizje 

				for (auto t = ksztalty.begin(); t != ksztalty.end(); t++)
				{
					Ksztalt *ptr = *t;
					if (postac->getGlobalBounds().intersects(ptr->getGlobalBounds()) && (typeid(*ptr) == typeid(Klocek)))//sprawdzenie kolizji oraz typu obiektu 
					{
						ostrzezenie = 1;	 //je¿eli wykryto ustaw flage na 1 
						postac->setPosition(wektor);//ustaw postac na pozycje poczatkow¹
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
		if (tab[i] == 8)  //8 w tym kierunku by³a kolizja bo nie wpisano innej wartoœæ (8 wartoœæ domyœlna tablicy) "nic nie rób"
		{ }
		else		 //w komórce znajduje siê dozwolona wartoœæ	która wskazuje na kierunek 
		{
			tab[i] = rand() % 100 + 9;	//wpisz wartoœæ losow¹ z przediza³u 9-108,w komórki których indeksy nie s¹ zabronionymi kierunkami 
		}
	}
	//wybieramy maxymaln¹ wartoœæ umieszczon¹ w tablicy 
	for (int i = 0; i < 4; i++)
	{
		if (tab[i] > max)
		{
			max = tab[i];
			licznik = i;
		}
	}
	//indeks maksymalnej wartoœæi to nasz nowy kierunek	  zmienna licznik

	postac->set_kierunek(licznik);	 //ustawienie nowego kierunku postaci
	postac->setPosition(wektor);	  //ustawienie postaci na pozycje pocz¹tkow¹ 

}
