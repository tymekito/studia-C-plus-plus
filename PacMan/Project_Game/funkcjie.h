#pragma once
#include"Ksztalty.h"

//funkcjia tworzy g��e okno programu
void createMyWindow(sf::RenderWindow &W, sf::String s);
//wczytuje z pliku .txt do tablicy 24/16 znaku kt�re maj� reprezentowa� obiekty
template<class Type,class Type2>
Type2 wczytaj(Type plansza, Type2 tablica[SCREENY / ROZMIAR][SCREENX / ROZMIAR])//tablica 24/16
{
	ifstream Plik_we;	  //zmienna plikowa
	Plik_we.open(plansza, ios::in);//otwarcie pliku do odczytu
	while (Plik_we)	  //dop�ki s� dane w pliku
	{
		for (int i = 0; i < SCREENY / ROZMIAR; i++)
		{
			for (int j = 0; j < SCREENX / ROZMIAR; j++)
			{
				Plik_we >> tablica[i][j];	  //za pomoc� operatora strumienia przekazujemy dane zpliku do tablicy
			}
		}
	}
	Plik_we.close();	 //po zakonczeniu operacji na pliku zamykamy go 
	return tablica[SCREENY / ROZMIAR][SCREENX / ROZMIAR];	//zwracamy now� tablice
}
// w zale�no��i od znaku jaki znajduje si� w kom�rce tablicy jest tworozny obiekt i dodawany do vektora
template<class Type3>
void wypisz(Type3 tablica[SCREENY / ROZMIAR][SCREENX / ROZMIAR], vector <Ksztalt*>&ksztalty, Ludek *&ludek, vector<Postac*> &postacie)
{
	for (int i = 0; i < SCREENY / ROZMIAR; i++)
	{
		for (int j = 0; j < SCREENX / ROZMIAR; j++)
		{
			switch (tablica[i][j])	 //w tablicy znajduj� si�  znanki zdefiniowane jako elementy np (DUCH 'D')
			{						 //w zale�no��i od rozpoznanego znaku jest wykonaywana inna instrukcja case
			case DUCH:
			{
				Duch *D = new Duch(sf::Vector2f(HITBOX, HITBOX), "grafika/Duszek.png", 128, 128, j * ROZMIAR, i * ROZMIAR); //tworzymy dynamicznie obiekt o z g�ry narzuconych parametrach
				postacie.push_back(D);	//dodajemy go do kontenera
				break;	 //przerwyamy instrukcj� 
			}
			case MONETA:
			{
				Moneta *M = new Moneta(sf::Vector2f(ROZMIAR, ROZMIAR), "grafika/diament.png", j * ROZMIAR, i * ROZMIAR);
				ksztalty.push_back(M);
				break;
			}
			case KLOCEK:
			{
				Klocek *K = new Klocek(sf::Vector2f(ROZMIAR, ROZMIAR), "grafika/Murek.png", j * ROZMIAR, i * ROZMIAR);
				ksztalty.push_back(K);
				break;
			}
			case LUDEK:
			{
				Ludek *L = new Ludek(sf::Vector2f(HITBOX, HITBOX), "grafika/Ludek.png", 128, 128, j * ROZMIAR, i * ROZMIAR);
				ludek = L;

				break;
			}
			default:  //je�eli w tablicy znalaz� si� znak kt�ry nie  jest zdefiniowany 
				break;
			}
		}
	}
}



