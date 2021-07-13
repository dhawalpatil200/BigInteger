#include<iostream>
using namespace std;

class BigInteger {

    private:
        string s;
        bool is_negative;
    
    public:

        // CONSTRUCTORS
        BigInteger();



        // FOR INPUT AND OUTPUT
        friend ostream& operator<<(ostream&,BigInteger&);
        friend istream& operator>>(istream&,BigInteger&);

        // HELPER FUNCTIONS
        friend int compare_magnitude(BigInteger,BigInteger);
        friend BigInteger add_magnitude(BigInteger,BigInteger);
        friend BigInteger subtract_magnitude(BigInteger,BigInteger);
        friend BigInteger multiply_magnitude(BigInteger,BigInteger);


        // LOGICAL OPERATORS
        friend bool operator==(BigInteger ,BigInteger);
        friend bool operator!=(BigInteger ,BigInteger);
        friend bool operator<(BigInteger ,BigInteger);
        friend bool operator<=(BigInteger ,BigInteger);
        friend bool operator>(BigInteger,BigInteger);
        friend bool operator>=(BigInteger,BigInteger);

        // ARITHMETIC OPERATORS
        BigInteger operator+(BigInteger &c);
        BigInteger operator-(BigInteger &c);
        BigInteger operator*(BigInteger &c);
         

};