#pragma once
#include"Ksztalty.h"

//funkcjia tworzy g³óe okno programu
void createMyWindow(sf::RenderWindow &W, sf::String s);
//wczytuje z pliku .txt do tablicy 24/16 znaku które maj¹ reprezentowaæ obiekty
template<class Type,class Type2>
Type2 wczytaj(Type plansza, Type2 tablica[SCREENY / ROZMIAR][SCREENX / ROZMIAR])//tablica 24/16
{
	ifstream Plik_we;	  //zmienna plikowa
	Plik_we.open(plansza, ios::in);//otwarcie pliku do odczytu
	while (Plik_we)	  //dopóki s¹ dane w pliku
	{
		for (int i = 0; i < SCREENY / ROZMIAR; i++)
		{
			for (int j = 0; j < SCREENX / ROZMIAR; j++)
			{
				Plik_we >> tablica[i][j];	  //za pomoc¹ operatora strumienia przekazujemy dane zpliku do tablicy
			}
		}
	}
	Plik_we.close();	 //po zakonczeniu operacji na pliku zamykamy go 
	return tablica[SCREENY / ROZMIAR][SCREENX / ROZMIAR];	//zwracamy now¹ tablice
}
// w zale¿noœæi od znaku jaki znajduje siê w komórce tablicy jest tworozny obiekt i dodawany do vektora
template<class Type3>
void wypisz(Type3 tablica[SCREENY / ROZMIAR][SCREENX / ROZMIAR], vector <Ksztalt*>&ksztalty, Ludek *&ludek, vector<Postac*> &postacie)
{
	for (int i = 0; i < SCREENY / ROZMIAR; i++)
	{
		for (int j = 0; j < SCREENX / ROZMIAR; j++)
		{
			switch (tablica[i][j])	 //w tablicy znajduj¹ siê  znanki zdefiniowane jako elementy np (DUCH 'D')
			{						 //w zale¿noœæi od rozpoznanego znaku jest wykonaywana inna instrukcja case
			case DUCH:
			{
				Duch *D = new Duch(sf::Vector2f(HITBOX, HITBOX), "grafika/Duszek.png", 128, 128, j * ROZMIAR, i * ROZMIAR); //tworzymy dynamicznie obiekt o z góry narzuconych parametrach
				postacie.push_back(D);	//dodajemy go do kontenera
				break;	 //przerwyamy instrukcjê 
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
			default:  //je¿eli w tablicy znalaz³ siê znak który nie  jest zdefiniowany 
				break;
			}
		}
	}
}



