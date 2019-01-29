//concern.cpp
//
//Adam Cole
//004912373
//
//Homework 3
//Problem 1

//#include <iostream>
//#include <string>
//using namespace std;

//Your declarations and implementations would go here
//--------------
//Concern class
class Concern {
public:
	Concern(string person) { m_person = person; }
	string person() const { return m_person; }
	//pure virtual
	virtual string description() const = 0;
	//non-pure virtual (doesn't have to be overwritten)
	virtual ~Concern() {/*nothing*/ }
	virtual bool possibleFelony() const { return m_felony; }
private:
	string m_person;
	bool m_felony = false;
};

//---------------
//EthicsMatter class
class EthicsMatter : public Concern {
public:
	EthicsMatter(string person) : Concern(person) {}
	virtual ~EthicsMatter() { cout << "Destroying " + person() + "'s ethics matter" << endl; }
	virtual string description() const { return "An ethics matter"; }
};

//---------------
//HushPayment class
class HushPayment : public Concern {
public:
	HushPayment(string person, int amount) : Concern(person), m_amount(amount) {}
	virtual ~HushPayment() { cout << "Destroying " + person() + "'s hush payment" << endl; }
	virtual string description() const { return "A $" + std::to_string(m_amount) + " payment"; }
private:
	int m_amount;
};

//---------------
//Investigation class
class Investigation : public Concern {
public:
	Investigation(string person) : Concern(person) {}
	virtual ~Investigation() { cout << "Destroying " + person() + "'s investigation" << endl; }
	virtual bool possibleFelony() const { return true; }
	virtual string description() const { return "An investigation"; }
};

//---------------
//
//void display(const Concern* c)
//{
//	cout << c->description() << " involving " << c->person();
//	if (c->possibleFelony())
//		cout << ", possibly felonious";
//	cout << endl;
//}
//
//int main()
//{
//	Concern* concerns[4];
//	concerns[0] = new EthicsMatter("Pruitt");
//	// Hush payments have a person's name and an amount of money (an int).
//	concerns[1] = new HushPayment("Clifford", 130000);
//	concerns[2] = new HushPayment("McDougal", 150000);
//	concerns[3] = new Investigation("Mueller");
//
//	cout << "Here are the concerns:" << endl;
//	for (int k = 0; k < 4; k++)
//		display(concerns[k]);
//
//	// Clean up the concerns before exiting
//	cout << "Cleaning up:" << endl;
//	for (int k = 0; k < 4; k++)
//		delete concerns[k];
//}