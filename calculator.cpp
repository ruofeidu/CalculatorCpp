// Programming -- Principles and Practice Using C++ by Bjarne Stroustrup
// Rewritten by ruofei
// It's such beautiful implementation
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
const char NUM = '8';

void error(string s) {
	cout << s << endl; 
	exit(EXIT_FAILURE);
}

void keep_window_open() {
	system("pause");
}

class Token
{
public:
	Token(char ch) : kind(ch), value(0) {};
	Token(char ch, double val) : kind(ch), value(val) {};
	char kind;
	double value;
};

class Token_stream
{
public:
	Token_stream(): full(false), buffer(0) {};
	Token get();
	void putback(Token c);
				  
private:
	bool full; 
	Token buffer;
};

void Token_stream::putback(Token t) {
	buffer = t; 
	full = true; 
}

Token Token_stream::get() 
{
	if (full) {
		full = false; 
		return buffer; 
	}
	char ch; 
	cin >> ch; 
	switch (ch)
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case 'q':
	case ';':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		cin.putback(ch);
		double val; 
		cin >> val; 
		return Token(NUM, val);
	default:
		error("Bad Token");
	}
}

Token_stream ts;

double expression();

double primary() {
	Token t = ts.get(); 
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			error("')' expected");
		return d;

	}
	case NUM:
		return t.value;
	default:
		error("primary expected");
	}
}

double term() {
	double left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double val = primary();
			if (val == 0)
				error("divide by zero");
			left /= val;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

int main() {
	cout << "welcome to our simple caculator." << endl;
	cout << "please enter expressions using float numbers." << endl;
	try {
		double val;
		while (cin) {
			Token t = ts.get();
			if (t.kind == 'q')
				break;
			if (t.kind == ';')
				cout << "=" << val << endl;
			else
				ts.putback(t);
			val = expression();
		}
		keep_window_open();
	} catch (exception &e) {
		cerr << e.what() << endl;
		keep_window_open();
		return 1;
	} catch (...) {
		cerr << "exception\n";
		keep_window_open();
		return 2;
	}
	return 0;
}
