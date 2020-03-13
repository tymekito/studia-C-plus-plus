#pragma once
#include "ListaLekow.h"


class Magazyn {

public:
	Magazyn() {};
	Lek* znajdzlek(string nazwaleku, string nazwarodzaju);
	void dodajlek();
	template <typename T> void znajdzzamiennik(T choroba)
	{
		fstream plik;
		try {
			plik.open("zamienniki.txt", std::ios::in);

			while (!plik.eof())
			{
				string napis;
				string nazwazpliku;
				int iloscsztuk;
				getline(plik, napis, '\n');
				char * schowek;
				char* skonwertowany = new char[napis.length() + 1];
				strcpy(skonwertowany, napis.c_str());
				schowek = strtok(skonwertowany, " ");
				nazwazpliku = schowek;
				while (schowek != NULL) {
					if (schowek == choroba) {
						cout << "lekiem dzialajacym na te chorobe jest: " + nazwazpliku << endl;
					}
					schowek = strtok(NULL, " ");
				}
			}
			plik.close();
		}
		catch (std::exception &e)
		{
			std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
			plik.close();
		}
	}
	void usunlek(string nazwaleku, string nazwarodzaju);
	void usunlekzzamiennikow(string nazwaleku);
	void zmniejszilosclekowojeden(string nazwaleku, string nazwarodzaju);
	void uzupelnijlek(string nazwaleku, string nazwarodzaju, int nowailosc);
	void wypiszlistedopliku(string nazwarodzaju, Listalekow* lista);
};