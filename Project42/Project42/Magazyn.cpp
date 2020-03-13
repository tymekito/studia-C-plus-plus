#include "Magazyn.h"

using namespace std;

Lek* Magazyn::znajdzlek(string nazwaleku, string nazwarodzaju) //parametr metody z klasy lek
{
	fstream plik;
	// sprawdzenie fragmentu instrukcj� try
	try
	{
		plik.open(nazwarodzaju + ".txt", std::ios::in);
		if (!plik.good())
		{
			throw std::exception("Nie istnieje taki rodzaj leku");
		}
		while (!plik.eof())
		{
			string napis;

			string nazwazpliku;
			bool refundacja;
			double cena;
			int ograniczenia;
			int iloscsztuk;
			string numerserii;
			getline(plik, napis, '\n');
			stringstream ss(napis);
			ss >> nazwazpliku >> refundacja >> cena >> ograniczenia >> iloscsztuk >> numerserii;
			if (nazwazpliku == nazwaleku)
			{
				return new Lek(nazwaleku, cena, refundacja, ograniczenia, numerserii, iloscsztuk);
				plik.close();
			}
		}

		return nullptr;
	}
	// z�apanie wyj�tku w przypadku niepowodzenia dost�pu do pliku
	catch (const std::exception &e )
	{
		std::cout <<std::endl << e.what() << std::endl;
		plik.close();
		return nullptr;
	}
}

void Magazyn::dodajlek()
{
	cout << "Wpisz rodzaj \n";
	string nazwaleku;
	string nazwarodzaju;

	cin >> nazwarodzaju;
	cout << "Wpisz nazwe leku\n";
	cin >> nazwaleku;

	Lek *lek = znajdzlek(nazwaleku, nazwarodzaju);

	if (lek != nullptr)
	{
		delete lek;
		cout << " Istnieje juz taki lek";

	}
	else
	{
		bool refundacja;
		double cena;
		int ograniczenia;
		int iloscsztuk;
		string numerserii;
		// sprawdznie fragmentu kodu podejrzanego o wyj�tek 
		ofstream plik;
		// je�eli otwarcie pliku by si� nie powiod�o rzucany jest wyj�tek kt�ry �apie instrukcja catch
		// je�eli do jakiego� obiektu nie mo�na by�o by si� odwo�a� to rzucany jest wyj�tek exception
		try 
		{
			plik.open(nazwarodzaju + ".txt", ios::out | ios::app);
			plik << nazwarodzaju << " " << numerserii;
			plik.close(); //obowi�zkowo nale�y zamkn�� plik
		}
		catch (const exception &e)
		{
			cout << "cos poszlo nie tak przy otwieraniu pliku!" << endl;
		}
		ofstream zamienniki;
		try {
			zamienniki.open("zamienniki.txt", ios::out | ios::app);
			string choroba;
			zamienniki << nazwaleku + " ";
			cout << "Wpisz choroby dla ktorych twoj lek jest zamiennikiem jezeli chcesz przestac wpisz 0";
			while (choroba != "0") {
				if (choroba == "0") {
					zamienniki << '\n';
				}
				cin >> choroba;
				zamienniki << choroba + " ";
			}

			zamienniki.close();
		}
		// z�panie wyj�tku
		catch (const exception &e)
		{
			cout << "cos poszlo nie tak przy otwieraniu pliku!"<<" zamienniki.txt" << endl;
			zamienniki.close();
		}
	}
}

void Magazyn::usunlek(string nazwaleku, string nazwarodzaju)
{
	fstream plik;

	try 
	{
	plik.open(nazwarodzaju + ".txt", std::ios::in);
		string linia;
		string nazwalekuzpliku;
		bool refundacja;
		double cena;
		int ograniczenia;
		int iloscsztuk;
		string numerserii;
		Listalekow* lista = NULL;

		while (getline(plik, linia)) {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");

			//while (schowek != NULL) {
			cout << schowek << endl;
			nazwalekuzpliku = schowek;
			if (nazwaleku != nazwalekuzpliku) {
				schowek = strtok(NULL, " ");
				refundacja = schowek;

				schowek = strtok(NULL, " ");
				cena = stoi(schowek);

				schowek = strtok(NULL, " ");
				ograniczenia = stoi(schowek);

				schowek = strtok(NULL, " ");
				iloscsztuk = stoi(schowek);

				schowek = strtok(NULL, " ");
				numerserii = schowek;

				Lek* lek = new Lek(nazwalekuzpliku, refundacja, cena, ograniczenia,numerserii, iloscsztuk);
				lista->dodajlekdolisty(lek, lista);

			}

			delete skonwertowany;
		}
		plik.close();
		wypiszlistedopliku(nazwarodzaju, lista);
		usunlekzzamiennikow(nazwaleku);
	}
	catch (std::exception &e)
	{
		std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
		plik.close();
	}

}

void Magazyn::usunlekzzamiennikow(string nazwaleku)
{
	fstream plik;
	// sprawdzenie kodu podejrzanego o wyj�tek
	try
	{
	plik.open("zamienniki.txt", std::ios::in);

		string linia;
		string nazwalekuzpliku;
		vector<string> liniezpliku;
		while (getline(plik, linia)) {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");

			cout << schowek << endl;
			nazwalekuzpliku = schowek;
			if (nazwaleku != nazwalekuzpliku) {
				liniezpliku.push_back(linia);


			}

			delete skonwertowany;
		}
		plik.close();
		plik.open("zamienniki.txt", std::ofstream::out | std::ofstream::trunc);
		if (plik.good()) 
		{
			std::vector<string>::iterator cell = liniezpliku.begin();
			for (cell; cell!= liniezpliku.end(); cell++) {
				plik << *cell;
			}
		}
		plik.close();
	}
	// z�apanie wyj�tku 
	catch (std::exception &e)
	{
		std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
		plik.close();
	}


}

void Magazyn::zmniejszilosclekowojeden(string nazwaleku, string nazwarodzaju)
{

	fstream plik;
	try
	{
	plik.open(nazwarodzaju + ".txt", std::ios::in);
		bool znaleziono = false;
		string linia;
		string nazwalekuzpliku;
		bool refundacja;
		double cena;
		bool ograniczenia;
		string numerserii;
		int iloscsztuk;
		Listalekow* lista = NULL;

		while (getline(plik, linia)) {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");
			if (schowek != NULL) {
				nazwalekuzpliku = schowek;
				schowek = strtok(NULL, " ");
				refundacja = schowek;
				schowek = strtok(NULL, " ");
				cena = stoi(schowek);
				schowek = strtok(NULL, " ");
				ograniczenia = schowek;
				schowek = strtok(NULL, " ");
				iloscsztuk = stoi(schowek);
				schowek = strtok(NULL, " ");
				numerserii = schowek;

				if (nazwaleku == nazwalekuzpliku) {
					znaleziono = true;
					if (iloscsztuk <= 0) {
						cout << "za malo leku: " + nazwaleku + " w bazie aby sprzedac, skontaktuj sie z managerem" << endl;
					}
					else {
						iloscsztuk--;
						cout << "sprzedano lek: " + nazwaleku + " pozostalo jeszcze: " + to_string(iloscsztuk) + " w bazie" << endl;
					}

				}
				Lek* lek = new Lek(nazwalekuzpliku, refundacja, cena, ograniczenia,numerserii, iloscsztuk);
				lista->dodajlekdolisty(lek, lista);


			}

			delete skonwertowany;
		}
		if (znaleziono == false) {
			cout << "Nie znaleziono podanego leku w bazie sprobuj ponownie dla innego rodzaju " << endl;
		}
		plik.close();
		wypiszlistedopliku(nazwarodzaju, lista);
	}
	catch (std::exception &e)
	{
		cout << "Dostep do bazy zabroniony" << endl;
		plik.close();
	}
	
}

void Magazyn::uzupelnijlek(string nazwaleku, string nazwarodzaju, int nowailosc)
{
	fstream plik;
	try
	{
	plik.open(nazwarodzaju + ".txt", std::ios::in);

		string linia;
		string nazwalekuzpliku;
		bool refundacja;
		double cena;
		bool ograniczenia;
		int iloscsztuk;
		string numerserii;
		Listalekow* lista = NULL;

		while (getline(plik, linia)) {
			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			schowek = strtok(skonwertowany, " ");
			if (schowek != NULL) {
				nazwalekuzpliku = schowek;
				schowek = strtok(NULL, " ");
				refundacja = schowek;
				schowek = strtok(NULL, " ");
				cena = stoi(schowek);
				schowek = strtok(NULL, " ");
				ograniczenia = schowek;
				schowek = strtok(NULL, " ");
				iloscsztuk = stoi(schowek);
				schowek = strtok(NULL, " ");
				numerserii = schowek;

				if (nazwaleku == nazwalekuzpliku) {
					iloscsztuk = nowailosc;
				}
				Lek* lek = new Lek(nazwalekuzpliku, refundacja, cena, ograniczenia, numerserii, iloscsztuk);
				lista->dodajlekdolisty(lek, lista);
			}

			delete skonwertowany;
		}
		plik.close();
		wypiszlistedopliku(nazwarodzaju, lista);
	}
	catch (exception & e)
	{
		plik.close();
		cout << "cos poszlo nie tak przy otwieraniu pliku!" << endl;
	}

}

void Magazyn::wypiszlistedopliku(string nazwarodzaju, Listalekow* lista) //metoda ktora sobie bierze listelekow a lista lekow to obiekt co nie?
{
	fstream plik;
	// sprawd� fragment kodu podejrzany o rzucenie wyj�tku
	try
	{
		plik.open(nazwarodzaju + ".txt", std::ofstream::out | std::ofstream::trunc);
		Listalekow* przechowywatorglowy = lista;
		while (przechowywatorglowy)
		{
			plik << przechowywatorglowy->lek->getNazwaleku() << " " << przechowywatorglowy->lek->getRefundacja() <<
				" " << przechowywatorglowy->lek->getCena() << " " << przechowywatorglowy->lek->getOgraniczenia() << " " << przechowywatorglowy->lek->getIloscsztuk() << przechowywatorglowy->lek->getNumerserii() << '\n';

			przechowywatorglowy = przechowywatorglowy->pNext;
		}

		Listalekow::wyczyscliste(lista);
		plik.close();
	}
	// z�apanie wyj�tku
	catch (const exception &e)
	{
		cout << "Dostep do bazy zabroniony" << endl;
		plik.close();
	}
}

