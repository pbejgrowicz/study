#include <stdio.h>
#include <iostream>

struct Samochod
{
	char *model;
	int rocznik;
	char *marka;
	struct Samochod *prev, *next;
};

struct Samochod * inicjalizuj(char model[], int rocznik, char marka[])
{
	struct Samochod * nowy = (struct Samochod *) malloc(sizeof(struct Samochod));
	
	if (!nowy)
		return NULL;

	nowy->rocznik = rocznik;
	nowy->model = model;
	nowy->marka = marka;
	nowy->next = 0;
	nowy->prev = 0;
	return nowy;
}


struct Samochod * dodajNowy(struct Samochod *root, char model[], int rocznik, char marka[])
{
	struct Samochod *nowy = (struct Samochod *) malloc(sizeof(struct Samochod));
	struct Samochod *tmp = root;

	while (tmp->rocznik > rocznik && tmp->next)
		tmp = tmp->next;


	nowy->rocznik = rocznik;
	nowy->model = model;
	nowy->marka = marka;

	if (tmp->prev == 0 || tmp->next == 0)
	{
		if (tmp->rocznik>rocznik)
		{
			nowy->next = tmp->next;
			nowy->prev = tmp;
			tmp->next = nowy;
		}
		else {
			nowy->next = tmp;
			tmp->prev = nowy;
			nowy->prev = tmp->prev;
			root = nowy;
		}
	}
	else
	{
		nowy->next = tmp;
		nowy->prev = tmp->prev;
		tmp->prev->next = nowy;
		tmp->prev = nowy;
	}
	printf("Dodano %s %s\n\n", marka, model);
	return root;
}
struct Samochod * usun(struct Samochod *root, struct Samochod *element)
{

	if (element == 0) //jezeli pusta lista
		return 0;

	if (element->prev == 0 && element->next == 0) // jezeli root tylko
	{
		free(element);
		return 0;
	}
	else //inne przypadki
		if (element->prev != 0 && element->next != 0) // w srodku listy
		{
			element->prev->next = element->next;
			element->next->prev = element->prev;

		}
		else if (element->next == 0) //jezeli usuwamy z koñca
		{
			element->prev->next = 0;
		}
		else if (element->prev == 0) // je¿eli usuwamy z przodu listy
		{
			root->next->prev = 0;
			root = root->next;
		}
		printf("usunieto %s %s \n\n", element->marka, element->model);
		free(element);
		return root;
}
struct Samochod * szukaj(struct Samochod *root, char model[])
{
	struct Samochod *tmp = root;

	while (tmp->next)
	{
		if (tmp->model == model)
		{
			printf("Znaleziono %s \n\n", model);
			return tmp;
		}

		tmp = tmp->next;
	}
	if (tmp->model == model)
	{
		printf("Znaleziono %s \n\n", model);
		return tmp;
	}
	printf("Nie znaleziono %s\n\n", model);

	return 0;
}
void drukuj(struct Samochod *root)
{
	printf("Marka\tModel\tRocznik\n");
	printf("-----------------------\n");
	if (root == 0)
		printf("-                     -\n");
	struct Samochod *tmp;
	tmp = root;
	while (tmp != NULL)
	{
		std::cout << tmp->marka << "\t" << tmp->model << "\t" << tmp->rocznik << std::endl;
		tmp = tmp->next;
	}
	printf("-----------------------\n\n");
}
int main()
{
	struct Samochod *root = inicjalizuj("m3", 2015, "BMW");

	root = dodajNowy(root, "458", 2013, "Ferrari");
	root = dodajNowy(root, "126p", 1977, "Fiat");

	drukuj(root);

	root = dodajNowy(root, "passat", 2016, "VW");
	root = dodajNowy(root, "kadet", 1970, "opel");

	drukuj(root);

	root = usun(root, root->next->next); // usuniecie trzeciego elementu
	drukuj(root);

	root = usun(root, szukaj(root, "m3")); //usuniêcie szukanego
	szukaj(root, "BMW");
	drukuj(root);


	root = usun(root, root->next); //zerowanie listy
	drukuj(root);
	root = usun(root, root->next);
	drukuj(root);
	root = usun(root, root->next);
	drukuj(root);

	return 0;
}