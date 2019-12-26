#include"Gra.h"

void PacMan()  //fukcja z g�own� czesci� programu
{
	std::srand(time(NULL));
	char tablica[SCREENY / ROZMIAR][SCREENX / ROZMIAR];	//tablica z plansz�
	wczytaj<string,char>("poziomy/poziom_01.txt", tablica);
	vector<Ksztalt*> ksztalt;	 //vector wskaznikow i dziala 
	vector<Postac*> postac;   //tworzy dodaje do vectora 
	Ludek *L = nullptr;		   //wska�nik na Ludka
	wypisz<char>(tablica, ksztalt, L, postac);	//wpisuje do wektora odpowiednie obiekty 
	sf::Vector2f poczatek(L->getPosition().x, L->getPosition().y);// wektor sfmlowy ktory przechowuje poczatkowe wsp�rz�dne ludka
	//..................OKNO...................//
	sf::RenderWindow W;	  //zmienna clasy okno
	createMyWindow(W, "PacMan V 4.0");	 //stworzenie okna 
	Okno Tlo("grafika/GUI.png", 0, 0);	//stworzenie obiektu t�a
	int licznik = 0;  //licznik kt�ry pokazuje funkcj� kiedy ma do�� do losowej zmienay kierunku postaci 
	Napis *nap = new Napis(sf::Vector2f((SCREENX / 2), 0));	 //stworzenie obiektu napis
	sf::Event e;
	//...................GUI.................//
	while (W.isOpen())
	{
		while (W.pollEvent(e))
			if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				W.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			break;

		W.draw(Tlo.Spr);
		W.display();
	}
	//..................GRA....................//
	Tlo.set_nazwa_grafiki("grafika/tlo_12x8.png");
	sf::Clock clock;
	while (W.isOpen()) //G��wna p�tla programu
	{
		sf::Time delta = clock.restart();	 //delta 
		if (W.pollEvent(e)) //kiedy zaszed� event(kiedy wci�ni�to co� na klawiaturze)
		{
			if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))//jak exc czy X w oknie to zamknij okno	   
				W.close();
			if (L)	//je�eli istnieje ludzik (wska�nik na niego nie jest nullptr)
			{
				L->ruch(e, delta);	//wykonaj ruch postaci� gracza
				vector < Ksztalt*>::iterator t = ksztalt.begin();
				for (; t != ksztalt.end(); t++)	  //sprawdz czy dla kontenera z obiektami statycznymi nie dosz�o do kolizji z postaci� gracza
				{
					Ksztalt* tmp = *t;   // iterator t 
					
					if (tmp->kolizja(L, delta) && (tmp->test() == 0))	 //sprawdzenie czy dosz�o do kolizji z obiektem zniszczalnm
					{
						nap->zwieksz(0);  //dodajemy punkty gdy� w logice gry takie obiekty przyznaj� punkty
						ksztalt.erase(t); //usuwamy obiekt z kontenera
						break;	//mo�e doj�� na raz tylko z jedynm obiektem wi�c przerywamy p�tle
					}
				}
				
					vector < Postac*>::iterator ta = postac.begin(); //iterator  tp
					for (; ta != postac.end(); ta++)  //sprawdzamy czy po ruchu gracza dosz�o do kolizji z obiektem typu posta� (czyli przeciwnikiem)
					{
						Postac *tmp2 = *ta;   //zmienna pomocnicza do kt�rej przypisujemy sprawdzany obiekt 
						if (!L->zyje(postac))	 //jezeli wystapi�a kolizja przeciwnika z duchem wykonaj ponizsza instrukcje
						{
							L->set_liczba_zyc(L->get_liczba_zyc() - 1);//zmniejszamy liczbe zyc gracza o 1
							L->setPosition(poczatek); //ustawiamy go na pozycji poczatkowej
							if (L->get_liczba_zyc() <= 0)//jezeli zycia spad�y na 0 to ustawiamy wska�nik postaci gracza na nullptr(umiera)
								L = nullptr;
							break;
						}
					}
					//w powy�szej p�tli sprawdzili�my czy mog�o doj�c do kolizji postac gracza z inna postacia wiec nie ma potrzebny sprawdzanie tego poni�ej
				vector < Postac*>::iterator tb = postac.begin();	//iterator po postaciach
				for (; tb != postac.end(); tb++)				  //petla ruchu  dla postaci innyc od postaci gracza
				{
					Postac *p = *tb;
					p->ruch(e, delta); //postacie poruszaj� si� 
					vector < Ksztalt*>::iterator t = ksztalt.begin(); //iterator po obiektach podejrzanych o kolizje
					for (; t != ksztalt.end(); t++)
					{
						Ksztalt *ptr = *t;
						if (ptr->kolizja(p, delta) && (ptr->test() == 1))  //jezeli dosz�o do kolizji z obiektem niezniszczalnym
						{
							licznik++;	 //licznik s�u�y do zmianny ruchu po osi�gni�ciu okre�lonej warto�� ludzik podczas swojej drogi zmienia kierunek ruchu 
							ustawDroge(p, ksztalt);	//ustawiamy nowy wolny kierunek 
							p->ruch(e, delta);	//poruszamy postac
							break;
						}
						else if (licznik == 10)
						{
							licznik = 0;
							ustawDroge(p, ksztalt);
							p->ruch(e, delta);
							break;
						}
						else {}

					}

				}	licznik++;
			}
		}
				else {
					for (auto t = postac.begin(); t != postac.end(); t++)
					{
						Postac *p = *t;
						p->ruch(e, delta);
						for (auto t = ksztalt.begin(); t != ksztalt.end(); t++)
						{
							Ksztalt *ptr = *t;
							if (ptr->kolizja(p, delta) && (ptr->test() == 1))
							{
								licznik++;
								ustawDroge(p, ksztalt);
								p->ruch(e, delta);
								break;
							}
							else if (licznik == 40)
							{
								licznik = 0;
								ustawDroge(p, ksztalt);
								p->ruch(e, delta);
								break;
							}
							else {}
						}
					}
					licznik++;
				}
		if (nap->getPunkty()== 200)
		{
			ksztalt.clear();
			postac.clear();
			L = nullptr;
			wczytaj<string, char>("poziomy/poziom_02.txt", tablica);
			wypisz<char>(tablica, ksztalt, L, postac);
			nap->setPunkty(0);
		}
		
		//...........WY�WIETLANIE...............//
		W.draw(Tlo.Spr);			   //za pomoc� metody draw wy�wietlamy Sprite'y obiekt�w na bitmapie
		for (auto shape : ksztalt)
			W.draw(*shape);
		for (auto shape : postac)
			W.draw(*shape);
		if (L)
		W.draw(*L);
		W.draw(*nap);
		nap->draw(W, nap->getPunkty());
		W.display();//wy�wietlamy  cale okno
	}
	return;		 
}
