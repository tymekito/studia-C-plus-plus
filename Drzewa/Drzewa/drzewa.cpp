#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct ElementDrzewa {
	int wartosc;
	ElementDrzewa * prawy;
	ElementDrzewa * lewy;

};
struct Drzewo {
	ElementDrzewa * glowa;

	ElementDrzewa * szukaj(int wartosc) 
	{
		return this->szukaj(this->glowa, wartosc);
	}

	ElementDrzewa * szukaj(ElementDrzewa * element, int wartosc) 
	{

		if (element == NULL || element->wartosc == wartosc) {
			return element;
		}
		else if (element->wartosc < wartosc) {
			return szukaj(element->prawy, wartosc);
		}
		else {
			return szukaj(element->lewy, wartosc);
		}

	}

	void wstaw(int wartosc) {
		this->glowa = this->wstaw(this->glowa, wartosc);
	}

	ElementDrzewa * wstaw(ElementDrzewa * element, int wartosc)
	{
		if (element == NULL) {
			ElementDrzewa * nowy = new ElementDrzewa();
			nowy->wartosc = wartosc;
			return nowy;
		}
		else if (wartosc < element->wartosc) {
			element->lewy = wstaw(element->lewy, wartosc);
		}
		else if (wartosc > element->wartosc) {
			element->prawy = wstaw(element->prawy, wartosc);
		}

		return element;
	}
};
void usun(int wartosc, ElementDrzewa *&pKorzen)
{
	if (pKorzen == nullptr){ }

	else 
	{
		ElementDrzewa*point = pKorzen;
		while (pKorzen)
		{

			if (pKorzen->lewy->wartosc < wartosc)
			{
				pKorzen = pKorzen->lewy;
			}
		    if (pKorzen->lewy->wartosc > wartosc)
			{
				pKorzen = pKorzen->prawy;
			}
			if (pKorzen->lewy->wartosc == wartosc)//|| pKorzen->prawy->wartosc == wartosc)
			{
				ElementDrzewa *tmp = pKorzen->lewy;
				pKorzen = pKorzen->lewy;
				delete pKorzen;		 //przypadek jak usun¹³em wêze³ 
				
				pKorzen = point;
			}
			if (pKorzen->prawy->wartosc == wartosc)//|| pKorzen->prawy->wartosc == wartosc)
			{
				ElementDrzewa *tmp = pKorzen->prawy;
				delete pKorzen->prawy;
				pKorzen =point;
			}
		}
		
	}
}
void usunDrzewo_cale(ElementDrzewa *&  pRoot)
{
	if (pRoot)
	{
		usunDrzewo_cale(pRoot->lewy);
		usunDrzewo_cale(pRoot->prawy);
		delete pRoot;
		pRoot = nullptr;
	}
}

int main() {
	Drzewo *drzewo = new Drzewo();
	drzewo->wstaw(10);
	drzewo->wstaw(24);
	drzewo->wstaw(4);
	drzewo->wstaw(1);
	drzewo->wstaw(5);
	drzewo->wstaw(32);
	drzewo->wstaw(0);


	return 0;
}