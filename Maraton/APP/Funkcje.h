#pragma once
/** @file Funkcje.h
*	@version Maraton 1.0
*	@date 18/01/2018 
*	@author Tymoteusz S³obodzian
*/
#ifndef FUNKCJE_H
#define FUNKCJE_H
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
//! Structura zawodnika
/**
* Structura przechowuje informacje o zawodnikach , ma postac listy jednokierunkowej w ktorej kazdy zawodnik posiada wskaznik na nastepnika
*/
struct lista_zawodnik  
{
	int msce_na_mecie;/*!< Miejsce na mecie uzyskane przez zawodnik  */
	string nazwisko;/*!< Nazwisko zawodnika   */
	int numer_zawodnika;/*!< Numer jaki posiada zawodnik  */
	string czas;/*!< Czas w jakim zawodnik ukonczyl maraton  */
	lista_zawodnik*pNast = nullptr;/*!< Wskaznik na nastepny element listy */
};
//! Structura maraton
/*
Jest to structura która przechowuje inormacje o maratonie , jest to struktura listy podwieszanej która posiada wskaznik na nastêpny element jak i na listê jednokierunkow¹ zawodników
*/
struct lista_maraton
{
	string nazwa_maratonu;/*!< Nazwa maratony  */
	string data;/*!< Data odbycia sie maratonu*/
	lista_zawodnik *zawodnik = nullptr;/*!< Wskaznik struture  listy jednokierunkowej zawodnikow*/
	lista_maraton  *pNast = nullptr;/*!< Wskaznik na nastepny element listy jednokierunkowej maratonow*/
};
/**
*@brief Opis funkcjia wczytaj
*@param string& Nazwa pliku z jakiego ma zostac wczytany maraton
*@param lista_maraton*& wskaznik na structure listy w ktorej ma zostac zapisany lista jest modyfikowana po wykonaiu funkcji
*@return Funkcja zwraca wartosc true w momencie wczytania pliku , wartosc false gdy plik o podanej nazwie nie istnieje 
*/
bool wczytaj(string &, lista_maraton *&);
/**
*@brief Opis funkcjia wczytaj_arg
*@brief Funckja  tworzy nowy element listy i dodaje go do podanej w argumencie listy  elementy sa dodawane w sposob uporzadowany wzgledem daty
*@param int ilosc wczytanych argumentow z lini polecen
*@param char*[] tablica wskaznikow na znaki przechowuje znaki / lancuchy znakow wczytane z argumentow z lini polecen
*@param lista_maraton*& wskaznik na structure listy w ktorej ma zostac zapisany lista jest modyfikowana po wykonaiu funkcji
*@return Funkcja zwraca wartosc true w momencie parametrow lub flase gdy wczytwanie nie powiodlo sie np. nie podano argumentow
*/
bool wczytaj_arg(int, char*[], lista_maraton*&);
/**
*@brief Opis funkcji zapisz
*@brief Funkcja skladajaca sie z pofunkcji ktore tworza plik torzsamy z nazwiskiem zawodnika lub dopisuja wynik(czas + nazwe maratonu) do istniejacego pliku
*@param lista_maraton* wskaznik na struture maraton 
*/
void zapisz(lista_maraton *);
/**
*@brief Opis funkcji zapisz_zawodnika
*@brief Funkcja tworzy plik torzsamy z nazwiskiem zawodnika i zapisuje do niego czas jaki uzyska³ w danym maratonie oraz nazwe maratonu
*@param lista_maraton* wskaznik na structure maraton
*/
void zapisz_zawodnika(lista_maraton *);
/**
*@brief Opis funkcji scal_maratony
*@brief Funckja wywoluje funkcjie wczytaj (,) dla danej nazwy maratonu i wskaznika na poczatek listy , funkcja wywoluje sie do momentu az wczytamy wszytkie pliki zawarte w wektorze
*@param vector<string> wektor przechowujacy nazwy plikow z jakich maja byc wczytane maratony 
*@param lista_maraton*& wskaznik na structure maraton(wskaznik na glowe listy)
*/
void scal_maratony(vector<string>, int, lista_maraton*&); 
/**
*@brief Opis funkcji dodaj_wynik
*@brief Funkcja tworzy plik torzsamy z nazwiskiem zawodnika i zapisuje do niego czas jaki uzyska³ w danym maratonie oraz nazwe maratonu
*@param lista_maraton*& wskaznik na structure maraton(wskaznik na glowe listy)
*/
void dodaj_wynik(lista_maraton*);
/**
*@brief Opis funkcji znajdz
*@param lista_maraton* wskaznik na structure maraton(wskaznik na glowe listy)
*@param vector<string> nazwa zawodnika ktory ma zostac znaleziony w liscie
*@brief Funkcja szuka zawodnika o podanym nazwisku istnieje w liscie
*@return Funkcja zwraca wartosc true jezeli dany wadonik istnieje w liscie w przeciwnym wypadku zwraca wartosc false
*/
bool znajdz(vector<string>, lista_maraton *);
/**
*@brief Opis funkcji usun_iteracyjnie
*@brief Funckja czysci pamiec , usuwa liste maratonow oraz podwieszone do niej listy zawodnikow
*@param lista_maraton*& wskaznik na structure maraton(wskaznik na glowe listy)
*/
void usun_iteracyjnie(lista_maraton*&);
/**
*@brief Opis funkcji maraton
*@brief Jest to glowna funckja programu ktora ma za zadanie wywolac funkcje realizujace program
*@param int liczba argumentow wprowadzonych do programu z lini polecen
*@param char*[] tablica wskaznikow na znaki przechowuje znaki / lancuchy znakow wczytane z argumentow z lini polecen 
*/
void maraton(int, char*[]);

#endif // FUNKCJE_H