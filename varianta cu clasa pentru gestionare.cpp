#include <iostream>
using namespace std;

bool integritatePlacuta(string placuta)
{
	if (placuta.size() == 7)
	{
		if (placuta[0] >= 'A' && placuta[0] <= 'Z')
		{
			for (int i = 0; i < placuta.size() - 3; i++)
			{
				if (!(placuta[i] >= '0' && placuta[i] <= '9'))
				{
					return false;
				}
			}

			for (int i = placuta.size() - 3; i < placuta.size(); i++)
			{
				if (!(placuta[i] >= 'A' && placuta[i] <= 'Z'))
				{
					return false;
				}
			}
		}
		else return false;
	}
	else return false;

	return true;
}

class Sistem;

class Masina
{
	const string VIN = "_________________";
	string placuta = "_______";
	string proprietar = "Anonim";
	string model = "Neidentificat";
	int anFabricatie = 0;
	float kilometraj = 0;

public:
	Masina() {}

	Masina(const string _VIN, string _placuta, string _proprietar, string _model, int _anFabricatie, float _kilometraj) : VIN(_VIN)
	{
		this->placuta = _placuta;

		if (_proprietar.size() > 3)
		{
			this->proprietar = _proprietar;
		}

		this->model = _model;

		if (_anFabricatie > 0)
		{
			this->anFabricatie = _anFabricatie;
		}

		if (_kilometraj >= 0)
		{
			this->kilometraj = _kilometraj;
		}
	}

	friend ostream& operator << (ostream& out, Masina& m);
	friend Sistem;
};

class CheiUnice
{
	int nrSerii = 0;
	string* serii = nullptr;

	int nrPlacute = 0;
	string* placute = nullptr;

public:
	CheiUnice() {}

	CheiUnice(const CheiUnice& chei)
	{
		this->nrSerii = chei.nrSerii;
		for (int i = 0; i < this->nrSerii; i++)
		{
			this->serii = chei.serii;
		}

		this->nrPlacute = chei.nrPlacute;
		for (int i = 0; i < this->nrPlacute; i++)
		{
			this->placute[i] = chei.placute[i];
		}
	}

	CheiUnice& operator = (const CheiUnice& chei)
	{
		if (this != &chei)
		{
			delete[] this->serii;
			this->serii = nullptr;
			this->nrSerii = 0;

			delete[] this->placute;
			this->placute = nullptr;
			this->nrPlacute = 0;

			this->nrSerii = chei.nrSerii;
			for (int i = 0; i < this->nrSerii; i++)
			{
				this->serii = chei.serii;
			}

			this->nrPlacute = chei.nrPlacute;
			for (int i = 0; i < this->nrPlacute; i++)
			{
				this->placute[i] = chei.placute[i];
			}
		}

		return *this;
	}

	void operator +=(string& _sir)
	{
		if (_sir.size() == 17)
		{
			if (this->nrSerii > 0)
			{
				string* aux = new string[this->nrSerii + 1];
				for (int i = 0; i < this->nrSerii; i++)
				{
					aux[i] = this->serii[i];
				}
				aux[this->nrSerii] = _sir;

				delete[] this->serii;

				this->nrSerii += 1;
				this->serii = aux;
			}
			else
			{
				this->nrSerii += 1;
				this->serii = new string[this->nrSerii];
				this->serii[0] = _sir;
			}
		}

		if (_sir.size() == 7)
		{
			if (this->nrPlacute > 0)
			{
				string* aux = new string[this->nrPlacute + 1];
				for (int i = 0; i < this->nrPlacute; i++)
				{
					aux[i] = this->placute[i];
				}
				aux[this->nrPlacute] = _sir;

				delete[] this->placute;

				this->nrPlacute += 1;
				this->placute = aux;
			}
			else
			{
				this->nrPlacute += 1;
				this->placute = new string[this->nrPlacute];
				this->placute[0] = _sir;
			}
		}
	}

	bool unicitateVIN(string _VIN)
	{
		if (this->nrSerii > 0)
		{
			for (int i = 0; i < this->nrSerii; i++)
			{
				if (this->serii[i] == _VIN)
				{
					return false;
				}
			}
		}

		return true;
	}

	bool unicitatePlacuta(string _placuta)
	{
		if (this->nrPlacute > 0)
		{
			for (int i = 0; i < this->nrPlacute; i++)
			{
				if (this->placute[i] == _placuta)
				{
					return false;
				}
			}
		}

		return true;
	}

	void modificarePlacuta(string placutaNoua, int index)
	{
		this->placute[index] = placutaNoua;
	}

	~CheiUnice()
	{
		if (this->nrSerii > 0 && this->nrPlacute > 0)
		{
			delete[] this->serii;
			this->serii = nullptr;
			this->nrSerii = 0;

			delete[] this->placute;
			this->placute = nullptr;
			this->nrPlacute = 0;
		}
	}

	friend ostream& operator << (ostream& out, CheiUnice& chei);
};

class Sistem
{
	int nrInregistrari = 0;
	Masina** inregistrari = nullptr;

public:
	Sistem () {}

	Sistem(const Sistem& _sis)
	{
		this->nrInregistrari = _sis.nrInregistrari;
		this->inregistrari = new Masina* [this->nrInregistrari];

		for (int i = 0; i < this->nrInregistrari; i++)
		{
			this->inregistrari[i] = _sis.inregistrari[i];
		}
	}

	Sistem& operator = (const Sistem& _sis)
	{
		if (this != &_sis && _sis.nrInregistrari > 0)
		{
			delete[] this->inregistrari;
			this->inregistrari = nullptr;
			this->nrInregistrari = 0;

			this->nrInregistrari = _sis.nrInregistrari;
			this->inregistrari = new Masina * [this->nrInregistrari];

			for (int i = 0; i < this->nrInregistrari; i++)
			{
				this->inregistrari[i] = _sis.inregistrari[i];
			}
		}
	}

	void operator += (Masina* m)
	{
		if (this->nrInregistrari > 0)
		{
			Masina** aux = new Masina * [this->nrInregistrari + 1];
			for (int i = 0; i < this->nrInregistrari; i++)
			{
				aux[i] = this->inregistrari[i];
			}
			aux[this->nrInregistrari] = m;

			delete[] this->inregistrari;
			this->nrInregistrari += 1;
			this->inregistrari = aux;
		}
		else
		{
			this->nrInregistrari += 1;
			this->inregistrari = new Masina* [this->nrInregistrari];
			this->inregistrari[0] = m;
		}
	}

	int accesareMasina(string _placuta)
	{
		if (this->nrInregistrari > 0)
		{
			for (int i = 0; i < this->nrInregistrari; i++)
			{
				if (this->inregistrari[i]->placuta == _placuta)
				{
					return i;
				}
			}
		}
		else return -1;
	}

	void modificareProprietar(string nume, int index)
	{
		this->inregistrari[index]->proprietar = nume;
		cout << "\nProprietar schimbat cu succes!";
	}

	void modificarePlacuta(string placutaNoua, int index)
	{
		this->inregistrari[index]->placuta = placutaNoua;
	}

	~Sistem()
	{
		if (this->nrInregistrari > 0)
		{
			delete[] this->inregistrari;
			this->inregistrari = nullptr;
			this->nrInregistrari = 0;
		}
	}

	friend ostream& operator << (ostream& out, Sistem& sis);
};

ostream& operator << (ostream& out, Masina& m)
{
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\nVIN: " << m.VIN;
	cout << "\nNr de inmatriculare: " << m.placuta;
	cout << "\nProprietar: " << m.proprietar;
	cout << "\nModel: " << m.model;
	cout << "\nAn fabricatie: " << m.anFabricatie;
	cout << "\nKilometraj: " << m.kilometraj<<endl;

	return out;
}

ostream& operator << (ostream& out, CheiUnice& chei)
{
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\nVin: ";
	for (int i = 0; i < chei.nrSerii; i++)
	{
		cout << chei.placute[i] << endl;
	}

	cout << "\nNumere de inmatriculare: ";
	for (int i = 0; i < chei.nrPlacute; i++)
	{
		cout << chei.placute[i] << endl;
	}

	return out;
}

ostream& operator <<(ostream& out, Sistem& sis)
{
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\nNr de inregistrari: " << sis.nrInregistrari;
	for (int i = 0; i < sis.nrInregistrari; i++)
	{
		cout << *sis.inregistrari[i];
	}

	return out;
}

int main()
{

	Sistem sis;
	CheiUnice chei;

	int optiune;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SISTEM DE GESTIUNE MASINI ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\n1. Inregistrare masina";
	cout << "\n2. Modificare proprietar";
	cout << "\n3. Modificare numar de inmatriculare";
	cout << "\n4. Consultare sistem";
	cout << "\nApasati tasta 0 pentru incheierea programului";
	cout << "\n\nOptiune: ";
	cin >> optiune;

	while (optiune != 0)
	{
		if (optiune == 1)
		{
			cout << "\n\nIntroduceti urmatoarele date: ";

			string VIN;
			cout << "\nVIN: ";
			cin >> VIN;

			while (VIN.size() != 17 || chei.unicitateVIN(VIN) == false)
			{
				cout << "\nVIN invalid!";
				cout << "\n\nVIN: ";
				cin >> VIN;
			}
			chei += VIN;

			string placuta;
			cout << "\nNr de inmatriculare: ";
			cin >> placuta;

			while (placuta.size() != 7 || integritatePlacuta(placuta) == false || chei.unicitatePlacuta(placuta) == false)
			{
				cout << "\nNr de inmatriculare invalid!";
				cout << "\nNr de inmatriculare: ";
				cin >> placuta;
			}

			chei += placuta;

			string proprietar;
			cout << "\nNume proprietar: ";
			cin >> proprietar;

			string model;
			cout << "\nModel: ";
			cin >> model;

			int an;
			cout << "\nAn fabricatie: ";
			cin >> an;

			int nrKm;
			cout << "\nKilometraj: ";
			cin >> nrKm;

			Masina* m = new Masina(VIN, placuta, proprietar, model, an, nrKm);
			sis += m;
		}

		if (optiune == 2)
		{
			string placuta;
			cout << "\n\nIntroduceti numarul de inmatriculare al masinii: ";
			cin >> placuta;

			string numeNou;
			cout << "\nIntroduceti noul proprietar: ";
			cin >> numeNou;

			int indexMasina = sis.accesareMasina(placuta);

			if (indexMasina != -1)
			{
				sis.modificareProprietar(numeNou, indexMasina);
			}
		}

		if (optiune == 3)
		{
			string placuta;
			cout << "\n\nIntroduceti numarul de inmatriculare al masinii: ";
			cin >> placuta;

			string placutaNoua;
			cout << "\nIntroduceti noul nnr de inmatriculare: ";
			cin >> placutaNoua;

			int indexMasina = sis.accesareMasina(placuta);

			if (indexMasina != -1 && integritatePlacuta(placutaNoua) == true)
			{
				sis.modificarePlacuta(placutaNoua, indexMasina);
				chei.modificarePlacuta(placutaNoua, indexMasina);
			}
		}
		
		if (optiune == 4)
		{
			cout << sis;
		}

		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SISTEM DE GESTIUNE MASINI ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout << "\n1. Inregistrare masina";
		cout << "\n2. Modificare proprietar";
		cout << "\n3. Modificare numar de inmatriculare";
		cout << "\n4. Consultare sistem";
		cout << "\nApasati tasta 0 pentru incheierea programului";
		cout << "\n\nOptiune: ";
		cin >> optiune;
	}

	cout << "\n\nPROGRAM INCHEIAT!";

	return 0;
}