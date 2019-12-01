#pragma once
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
//--------------------------------------------------------------------
struct lista_zawodnik  //structura listy jednokierunkowej zawodnikow
{
	int msce_na_mecie;//miejsce  uzyskane przez zawodnika
	string nazwisko;//nazwisko zawodnika
	int numer_zawodnika;//numer zawodnika
	string czas;//czas zawodnika
	lista_zawodnik*pNast = nullptr;//wskaznik na nastepny element listy
};
struct lista_maraton //struktura listy jednokierunkowej maratonow z podwieszana lista zawodnikow
{
	string nazwa_maratonu;//nazwa maratonu
	string data;//data maratonu
	lista_zawodnik *zawodnik = nullptr;//wskaznik na liste zawodnikow
	lista_maraton  *pNast = nullptr;//wskaznik na nastepny element listy
};
//-----------------------------------------------------------------
bool wczytaj(string &, lista_maraton *&);//wczytuje z pliku maraton

bool wczytaj_arg(int , char* [], lista_maraton*&);//funckja obslugujaca przelaczniki

void zapisz(lista_maraton *);//funkcja posrednia ktora sprawdza czy dany zawodnik jest w liscie i albo tworzy nowy plik 

void zapisz_zawodnika(lista_maraton *);//funkcja zapisuje zawodnika do pliku

void scal_maratony(vector<string> , int , lista_maraton*&);//³aczy listy maratonow 

void dodaj_wynik(lista_maraton*);//funkcja dopisuje wynik do utworzonego pliku 

bool znajdz(vector<string> , lista_maraton *);//funkcja szuka nazwiska w liscie

void usun_iteracyjnie(lista_maraton*&);//usuwanie ,zwalnianie pamieci 

void maraton(int , char* []);//wywolanie programu maraton