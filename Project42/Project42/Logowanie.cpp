#include "Logowanie.h"

string Logowanie::menulogowania()
{
	string login;
	string haslo;
	cout << "Zaloguj sie" << endl;
	cout << "Login: ";
	cin >> login;
	cout << "Haslo: ";
	cin >> haslo;
	return zalogujSie(login, haslo);
}

string Logowanie::zalogujSie(string login, string haslo)
{
	fstream plik;
	try
	{
		plik.open("hasla.txt", std::ios::in);
		while (!plik.eof())
		{
			string linia;
			string rola;
			getline(plik, linia, '\n');

			char * schowek;
			char* skonwertowany = new char[linia.length() + 1];
			strcpy(skonwertowany, linia.c_str());
			if (strlen(skonwertowany) == 0) {
				break;
			}
			string loginzPliku = strtok(skonwertowany, " ");
			string haslozPliku = strtok(NULL, " ");
			if (login == loginzPliku && haslo == haslozPliku) {
				plik.close();
				return strtok(NULL, " ");

			}
			else if (login == loginzPliku && haslo != haslozPliku) {
				cout << "Podano bledne haslo aplikacja zostanie wylaczona!";
				Sleep(1000);
				plik.close();
				exit(0);
				return nullptr;

			}
		}
	}
	// z³ap wyj¹tek je¿eli nie uda³o siê dostaæ do pliku
		catch (exception e)
		{
			cout << "Brak dostêpu do bazy";
		}
		cout << "Nie znaleziono uzytkownika o podanym hasle, aplikacja zostanie wylaczona!";
		Sleep(1000);
		plik.close();
		exit(0);
		//menulogowania();
		return nullptr;
}
