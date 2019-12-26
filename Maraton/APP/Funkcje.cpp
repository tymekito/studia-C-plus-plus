#include"Funkcje.h"
//------------------------------------------------
bool wczytaj(string &nazwaPliku, lista_maraton *&lista)//wczytuje z pliku maraton
{
	fstream plik;//zmienna plikowa
	if (plik.good())//sprawdzamy czy plik jest prawidlowy
	{
		plik.open(nazwaPliku, ios::in);//otwieramy plik w trybie do odczytu
		lista_zawodnik*zawodnik = new lista_zawodnik();//tworzymy nowego zawodnika
		lista->zawodnik = zawodnik;//dodajemy go do listy
		string znak;//ta zmienna przechowuje przecinek ktory jest zbedny po wczytaniu pliku wejsciowego
		if (!plik.eof())//wczytujemy do mementu az plik sie skonczy
		{
			getline(plik, lista->nazwa_maratonu);//pobieramy linie z pliku i zapisujemy do listy 
			plik >> lista->data;//wczytujemy date z pliku do listy 
			while (plik >> zawodnik->msce_na_mecie >> znak >> zawodnik->nazwisko >> zawodnik->numer_zawodnika >> znak >> zawodnik->czas)
			{//wczytujemy po kolei za pomoca strumieni dane do structury
				zawodnik->nazwisko = zawodnik->nazwisko.substr(0, zawodnik->nazwisko.size() - 1);//usuwamy zedny znak
				if (!plik.eof())//jezeli w pliku sa dane
				{
					zawodnik = zawodnik->pNast = new lista_zawodnik();//stworz nastepnika dla i przestaw glowe na nowo stworzony element
				}
			}
		}
		plik.close();//zamykamy plik 
		return true;//wczytywanie powiodlo sie zwracamy true
	}
	else
	{
		return false; //wczytywanie nie powiodlo sie zwracamy false
	}
}
void scal_maratony(vector<string> maratony, int ilosc, lista_maraton*&pGlowa)//³aczy listy maratonow 
{
	if (ilosc == 1)
	{
		wczytaj(maratony[0], pGlowa);
	}
	else
	{
		lista_maraton*trzymaj = pGlowa; //wskaznik na glowe listy
		wczytaj(maratony[0], pGlowa);//wczytanie pierwszego elementu listy 
		for (int i = 1; i < ilosc; i++)//ilosc=maratony.size()
		{
			lista_maraton*tmp = new lista_maraton();
				wczytaj(maratony[i], tmp);

				if (trzymaj->data > tmp->data)//dodawanie na poczatek listy 
				{
					tmp->pNast = trzymaj;
					trzymaj = tmp;
				}
				else//jezeli go nie dodwalo na poczatek listy 
				{
					while (pGlowa->pNast)//sprawdz czy jest mniejszy od elementow w liscie 
					{

						if (pGlowa->pNast->data > tmp->data)//dodwanie w srodku listy 
						{
							tmp->pNast = pGlowa->pNast;
							pGlowa->pNast = tmp;
							break;
						}
						pGlowa = pGlowa->pNast;
					}
					if (pGlowa->pNast == nullptr)//dodwanie na koniec listy 
					{
						pGlowa->pNast = tmp;
						tmp->pNast = nullptr;
						
					}
					pGlowa = trzymaj;
				}
		}
		pGlowa = trzymaj;//przywrocenie glowy na poczatkowe miejsce
	}
}
//---------------------------------------------------------------
void zapisz_zawodnika(lista_maraton *pGlowa)
{
	ofstream plikwy;//zmienna plikowa
	string nazwa = pGlowa->zawodnik->nazwisko + ".txt";//nazwa pliku wyjsciowego
	plikwy.open(nazwa, ios::trunc);//otwieramy plik i usuwamy poprzednia zawartosc pliku
	plikwy << pGlowa->zawodnik->nazwisko << "\n" << "\n";//zapisujemy dane do pliku 
	plikwy << pGlowa->data << " " << pGlowa->nazwa_maratonu << " " << pGlowa->zawodnik->czas << "\n";
	plikwy.close();//zamykamy plik po zakonczeniu operacji na nim
}
void dodaj_wynik(lista_maraton*pGlowa)
{
	ofstream plikwy;//zmienna plikowa
	string nazwa = pGlowa->zawodnik->nazwisko + ".txt";
	plikwy.open(nazwa, ios::app);//otwarcie pliku w trybie dopisywania
	plikwy << pGlowa->data << " " << pGlowa->nazwa_maratonu << " " << pGlowa->zawodnik->czas << "\n";//zapisujemy dane do pliku
	plikwy.close();//zamykamy plik po zakonczeniu opercji na nim
}
bool znajdz(vector<string> nazwiska_, lista_maraton *pGlowa)
{
	int dlugosc = nazwiska_.size();//przypisujemy do zmiennej dlugosc vektora
	for (int i = 0; i<dlugosc; i++)
	{
		if (pGlowa->zawodnik->nazwisko == nazwiska_[i])//sprawdzamy czy dany zawodnik w liscie znajduje sie w vectorze
			return true;//jak sie znajduje to zwracamy true
	}
	return false;//jak sie nie znajduje zwracamy false
}
void zapisz(lista_maraton *pGlowa)
{
	if (pGlowa)
	{
		vector <string> nazwiska;
		lista_maraton *tmp = pGlowa;//wskaznik na pierwszy element listy 
		while (pGlowa)
		{
			lista_zawodnik*zad = pGlowa->zawodnik;//wskaznik na pierwszy element listy zawdonikow 
			while (pGlowa->zawodnik)
			{
				if (znajdz(nazwiska, pGlowa))//jesli znalazlo go w vektorze to dodaj mu wynik
				{
					dodaj_wynik(pGlowa);
				}
				else//jak go nie znalaz³o to stworz mu plik 
				{
					zapisz_zawodnika(pGlowa);
					nazwiska.push_back(pGlowa->zawodnik->nazwisko); //i dodaj nazwisko do wektora ze zawdonikowi zostal stworzony plik
				}
				pGlowa->zawodnik = pGlowa->zawodnik->pNast;//przesuwanie glowy na nastepnego zawodnik
			}
			pGlowa->zawodnik = zad;//nie gubimy zawodnikow przypisujemy wskaznikowi na pierwszy element listy jego poczatkowe miejsce
			pGlowa = pGlowa->pNast;//przesuwamy glowe listy maratonow na natsepny element
		}
		pGlowa = tmp;//ustawiamy glowe listy maratonow na pocztakowe miejsce

	}
	else//gdyby nie istaniala lista maratonow do zapisania do wyswietlamy blad
	{
		cout << "brak_list_maratonow_do_zapisania_:(" << endl;
	}
}
void usun_iteracyjnie(lista_maraton*&pGlowa)//usuwanie ,zwalnianie pamieci  
{
	lista_maraton *tmp = pGlowa;//wskanzik na pierwszy element listy 
	while (pGlowa)
	{
		lista_zawodnik *zad = pGlowa->zawodnik;
		while (zad)//usuwamy najpierw zawodnikow poruszajac sie po liscie 
		{
			zad = zad->pNast;
			delete pGlowa->zawodnik;
			pGlowa->zawodnik = zad;
		}
		tmp = pGlowa->pNast;//nastepnie usuwamy maraton i przesuwamy glowe 
		delete pGlowa;
		pGlowa = tmp;
		delete zad;
	}
	delete tmp;
}
bool wczytaj_arg(int argc, char* argv[], lista_maraton*&lista)
{
	vector<string> maratony;
	if (argc > 1)//sprawdzamy czy dany prefiks wystepuje w lini polecen
	{
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')//i wiersz 0 element ³ancucha
			{
				switch (argv[i][1])//i wiersz 1 elment ³ancucha
				{
				case 'i'://dla danego prefiku zapisz nazwe maratonu podana z lini polecen do vektora
				{
					maratony.push_back(argv[i + 1]);
					break;
				}
				default:
					cout << "Wprowadzono niepoprawne parametry\n";//w razie bledu gdy podano bledy prefiks
					break;
				}
			}
		}
		scal_maratony(maratony, maratony.size(), lista);//wywolanie funkcji scal maratony dla wczytanych nazw plikow 
		return true;
	}
	else//gdy nie podano zadnych argumentow do programu 
	{
		cout << "nie podano protokolow" << endl;
		return false;
	}
}
//--------------------------------------------------------------------
void maraton(int argc, char* argv[])
{//funkcja wykonujaca program 
	lista_maraton *lista = new lista_maraton();//tworzymy dynamicznie nowa liste 
	wczytaj_arg(argc, argv, lista);//wczytujemy dane tworzac  strukture listy powieszanej 
	zapisz(lista);//zapisujemy dane do plikow
	usun_iteracyjnie(lista);//zwalniamy pamiec
	delete lista;//usuwamy stworozna na pocztaku programu liste 
}