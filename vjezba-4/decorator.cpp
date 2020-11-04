#include <string>
#include <iostream>
#include <memory>

using namespace std;

// interfejs za napitke
//
class Napitak {
public:
	// virtual ~Napitak() {
	// 	cout << "brisem Napitak\n";
	// }

	virtual string opis() const { return _opis; }
	virtual double cijena() const = 0;

protected:
	string _opis;
};

class Kapucino : public Napitak {
public:
	Kapucino() {
		_opis = "kapucino";
	}
	
	// ~Kapucino() {
	// 	cout << "brisem Kapucino\n";
	// }

	virtual double cijena() const { return 12; }

};

class Espreso : public Napitak {
public:
	Espreso() {
		_opis = "espreso";
	}

	// ~Espreso() {
	// 	cout << "brisem Espreso\n";
	// }

	virtual double cijena() const { return 10; }
};

class TurskaKava : public Napitak {
public:
	TurskaKava() {
		_opis = "turska-kava";
	}

	// ~TurskaKava() {
	// 	cout << "brisem TurskaKava\n";
	// }

	virtual double cijena() const { return 8; }
};

//=============================================================================

// interfejs za dodatke - nasljedjuje od Napitak
//
class Dodatak : public Napitak {
public:
	virtual string opis() = 0;
};

class Slag : public Dodatak {
public:
	Slag(shared_ptr<Napitak> napitak) : _napitak {napitak} {
		_opis = _napitak->opis() + "; slag";
	}
	
	// ~Slag() {
	// 	cout << "brisem Slag\n";
	// }

	string opis() { return _opis; }
	double cijena() const { return 2.5 + _napitak->cijena(); }

private:
	shared_ptr<Napitak> _napitak;
};

class Mlijeko : public Dodatak {
public:
	Mlijeko(shared_ptr<Napitak> napitak) : _napitak {napitak} {
		_opis = _napitak->opis() + "; mlijeko";
	}
	
	// ~Mlijeko() {
	// 	cout << "brisem Mlijeko\n";
	// }

	string opis() { return _opis; }
	double cijena() const { return 1 + _napitak->cijena(); }

private:
	shared_ptr<Napitak> _napitak;
};

class Cokolada : public Dodatak {
public:
	Cokolada(shared_ptr<Napitak> napitak) : _napitak {napitak} {
		_opis = _napitak->opis() + "; cokolada";
	}
	
	// ~Cokolada() { 
	// 	cout << "brisem Cokolada\n";
	// }

	string opis() { return _opis; }
	double cijena() const { return 4.5 + _napitak->cijena(); }

private:
	shared_ptr<Napitak> _napitak;
};

class Rum : public Dodatak {
public:
	Rum(shared_ptr<Napitak> napitak) : _napitak {napitak} {
		_opis = _napitak->opis() + "; rum";
	}
	
	// ~Rum() { 
	// 	cout << "brisem Rum\n";
	// }

	string opis() { return _opis; }
	double cijena() const { return 6.5 + _napitak->cijena(); }

private:
	shared_ptr<Napitak> _napitak;
};

//=============================================================================
//=============================================================================
//=============================================================================

int main() {
	// espreso + slag + mlijeko
	shared_ptr<Napitak> napitak1 = make_shared<Espreso>();
	napitak1 = make_shared<Slag>(napitak1);
	napitak1 = make_shared<Mlijeko>(napitak1);

	cout << napitak1->opis() << endl << napitak1->cijena() << endl;

	// kapucino + mlijeko + slag + cokolada
	shared_ptr<Napitak> napitak2 = make_shared<Kapucino>();
	napitak2 = make_shared<Mlijeko>(napitak2);
	napitak2 = make_shared<Slag>(napitak2);
	napitak2 = make_shared<Cokolada>(napitak2);
	// napitak2 = make_shared<Cokolada>(napitak2);

	cout << napitak2->opis() << endl << napitak2->cijena() << endl;

	return 0;
}
