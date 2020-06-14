/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
class Person {
  static const char *myName = "Fred";
  public:
		const char* name() {
    	return myName;
  	}
};

class Money {
  private:
  	double myValue;
  public:
  	Money() {
      myValue = 0.0;
    }
  	Money(double aValue) {
      myValue = aValue;
    }
  	void setValue(const double aValue) {
      myValue = aValue;
    };
};

class BankAccount {
  private:
  	Money *myBalance;
  public:
  	BankAccount() {
      myBalance = new Money();
    }
  	void setBalance(const Money &anAmt) {
      myBalance = new Money(anAmt);
    }
  	Person* getOwner() { 
      return new Person(); 
    }
};

void markWorkflow(const char* aName, int aCmd) {}
const int SET_BALANCE=10;

void processTransaction(BankAccount acct, int) {
  Person *who;
  Money amt;

  amt.setValue(123.45);
  acct.setBalance(amt);
  who = acct.getOwner();
  markWorkflow(who->name(), SET_BALANCE);
}
