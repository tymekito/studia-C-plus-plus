#include"Funkcje.h"
//------------------------------------------------
bool wczytaj(string &nazwaPliku, lista_maraton *&lista)//wczytuje z pliku maraton
{
	fstream plik;
	if (plik.good())
	{
		plik.open(nazwaPliku, ios::in);
		lista_zawodnik*zawodnik = new lista_zawodnik();
		lista->zawodnik = zawodnik;
		string znak;
		if (!plik.eof())
		{
			getline(plik, lista->nazwa_maratonu);
			plik >> lista->data;
			while (plik >> zawodnik->msce_na_mecie >> znak >> zawodnik->nazwisko >> zawodnik->numer_zawodnika >> znak >> zawodnik->czas)
			{
				zawodnik->nazwisko = zawodnik->nazwisko.substr(0, zawodnik->nazwisko.size() - 1);
				if (!plik.eof())
				{
					zawodnik = zawodnik->pNast = new lista_zawodnik();

				}
			}
		}
		plik.close();
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------
void scal_maratony(vector<string> maratony, int ilosc, lista_maraton*&pGlowa)//³aczy listy maratonow 
{
	if (ilosc == 1)
	{
		wczytaj(maratony[0], pGlowa);
	}
	else
	{
		lista_maraton*trzymaj = pGlowa;
		wczytaj(maratony[0], pGlowa);
		for (int i = 1; i < ilosc; i++)
		{
			if (pGlowa->pNast == nullptr)
			{
				lista_maraton*tmp = new lista_maraton();
				wczytaj(maratony[i], tmp);
			
				if (trzymaj->data > tmp->data)//dodawanie na poczatek listy 
				{
					tmp->pNast = trzymaj;
					trzymaj= tmp;
				}
				else
				{
					pGlowa->pNast = tmp;
					pGlowa = pGlowa->pNast;
				}
			}
			if (i == ilosc )
			{
				pGlowa->pNast = nullptr;
				break;
			}
		}
		pGlowa = trzymaj;
	}
}
//---------------------------------------------------------------
void zapisz_zawodnika(lista_maraton *pGlowa)
{
	ofstream plikwy;
	string nazwa = pGlowa->zawodnik->nazwisko + ".txt";
	plikwy.open(nazwa, ios::trunc);
	plikwy << pGlowa->zawodnik->nazwisko << "\n" << "\n";
	plikwy << pGlowa->data << " " << pGlowa->nazwa_maratonu << " " << pGlowa->zawodnik->czas << "\n";
	plikwy.close();
}
void dodaj_wynik(lista_maraton*pGlowa)
{
	ofstream plikwy;
	string nazwa = pGlowa->zawodnik->nazwisko + ".txt";
	plikwy.open(nazwa, ios::app);
	plikwy << pGlowa->data << " " << pGlowa->nazwa_maratonu << " " << pGlowa->zawodnik->czas << "\n";
	plikwy.close();
}
bool znajdz(vector<string> nazwiska_, lista_maraton *pGlowa)
{
	int dlugosc = nazwiska_.size();
	for (int i = 0; i<dlugosc; i++)
	{
		if (pGlowa->zawodnik->nazwisko == nazwiska_[i])
			return true;
	}
	return false;
}
//-----------------------------------------------------------
void zapisz(lista_maraton *pGlowa)
{
	if (pGlowa)
	{
		vector <string> nazwiska;
		lista_maraton *tmp = pGlowa;//trzymajka glowy
		while (pGlowa)
		{
			lista_zawodnik*zad = pGlowa->zawodnik;//trzymajka zawodnika
			while (pGlowa->zawodnik)
			{
				if (znajdz(nazwiska, pGlowa))//jesli znalazlo go w vektorze to dodaj mu wynik
				{
					dodaj_wynik(pGlowa);
				}
				else//jak go nie znalaz³o to stworz mu plik 
				{
					zapisz_zawodnika(pGlowa);
					nazwiska.push_back(pGlowa->zawodnik->nazwisko);
				}
				pGlowa->zawodnik = pGlowa->zawodnik->pNast;//przesunac glowe
			}
			pGlowa->zawodnik = zad;//nie gubimy zawodnikow
			pGlowa = pGlowa->pNast;//przesunac glowe
		}
		pGlowa = tmp;
		
	}
	else
	{
		cout << "brak_list_maratonow_do_zapisania_:(" << endl;
	}
}
//---------------------------------------------------------------
void usun_iteracyjnie(lista_maraton*&pGlowa)//usuwanie ,zwalnianie pamieci  ,dzia³a :)
{
	lista_maraton *tmp = pGlowa;
	while (pGlowa)
	{
		lista_zawodnik *zad = pGlowa->zawodnik;
		while (zad)
		{
			zad = zad->pNast;
			delete pGlowa->zawodnik;
			pGlowa->zawodnik = zad;
		}
		tmp = pGlowa->pNast;
		delete pGlowa;
		pGlowa = tmp;
		delete zad;//zmiana
	}
	delete tmp;
}
//-------------------------------------------------------------
bool wczytaj_arg(int argc, char* argv[], lista_maraton*&lista)
{
	vector<string> maratony;
	int ilosc = argc - 1;
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')//i wiersz 0 element ³ancucha
			{
				switch (argv[i][1])//i wiersz 1 elment ³ancucha
				{
				case 'i':
				{
					maratony.push_back(argv[i + 1]);
					break;
				}
				default:
					cout << "Wprowadzono niepoprawne parametry\n";
					break;
				}
			}
		}
		scal_maratony(maratony, maratony.size(), lista);
		return true;
	}
	else
	{
		cout << "nie podano protokolow" << endl;
		return false;
	}
}
//--------------------------------------------------------------------
void maraton(int argc, char* argv[])
{
	lista_maraton *lista = new lista_maraton();
	wczytaj_arg(argc, argv, lista);
	zapisz(lista);
	usun_iteracyjnie(lista);
	delete lista;
}
