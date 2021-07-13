#include "BigInt.h"
#include<iostream>
using namespace std;

BigInteger :: BigInteger() {
    s="";
    is_negative = 0;
}


istream& operator>>(istream &din,BigInteger &c)
{
    cin>>c.s;
    if(c.s[0] == '-')
    {
        c.is_negative = true;
        c.s = c.s.substr(1);
    }
    else
    {
        c.is_negative = false;
    }
    return din;
}
ostream& operator<<(ostream &dout,BigInteger &c)
{
    if(c.is_negative == true)
    {
        cout<<"-"<<c.s;
    }
    else
    {
        cout<<c.s;
    }
    return dout;
}

int compare_magnitude(BigInteger a,BigInteger b) {
    int n1 = a.s.size();
    int n2 = b.s.size();

    if(n2 < n1) {
        return 0;
    }
    else if(n1 < n2) {
        return 1;
    }
    else {

        for(int i = 0; i < n1 ; i++) {
            if(a.s[i] < b.s[i]) {
                return 1;
            }
            else if(a.s[i] > b.s[i]) {
                return 0;
            }
        }

        return 2;

    }

}

BigInteger add_magnitude(BigInteger a,BigInteger b) {

    int i = a.s.size()-1;
    int j = b.s.size()-1;

    BigInteger ans;
    ans.s = "";

    string temp;

    ans.is_negative = 0;
    int carry = 0;
    while(i>=0 || j>=0) {

        int digit1 = i>=0 ? a.s[i--]-'0' : 0;
        int digit2 = j>=0 ? b.s[j--]-'0' : 0;        

        int sum = digit1 +  digit2 + carry ;
        carry = sum/10;

        sum = sum%10;
        temp.push_back(sum+'0');

    }

    if(carry > 0) {
        temp.push_back(carry + '0');
    }

   

    reverse(temp.begin(),temp.end());

    ans.s = temp;

    return ans;
}



BigInteger subtract_magnitude(BigInteger a,BigInteger b) {
    BigInteger ans;

   
    if(compare_magnitude(a,b) == 1 ) {
        // a < b
        ans.is_negative = 1;
        
        string temp;
        int n1 = a.s.size();
        int n2 = b.s.size();
        int carry = 0;

        // perforn  b - a and assign negative
        
        int j = n2-1;
        int i = n1-1;

        while(j>=0) {
            int first = b.s[j--]-'0';
            int second = i>=0 ? a.s[i--]-'0' : 0;

            int sub = first - second - carry;
            if(sub < 0 ) {
                sub += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }

            temp.push_back(sub+'0');
        }

        reverse(temp.begin(),temp.end());
        
        int k = 0;
        while(k<temp.size() && temp[k] =='0') {
            k++;
        }

        temp = temp.substr(k);

        
        ans.s = temp;

        return ans;

    } 
    else if(compare_magnitude(a,b) == 2) {
        // a == b
        ans.is_negative = 0;
        ans.s.push_back('0');
        return ans;
    }
    else {
        // a > b
        ans.is_negative = 0;

         string temp;
        int n1 = a.s.size();
        int n2 = b.s.size();
        int carry = 0;

        // perforn  a - b
        
        int j = n2-1;
        int i = n1-1;

        while(i>=0) {
            int first = a.s[i--]-'0';
            int second = j>=0 ? b.s[j--]-'0' : 0;

            int sub = first - second - carry;
            if(sub < 0 ) {
                sub += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }

            temp.push_back(sub+'0');
        }

        reverse(temp.begin(),temp.end());

        int k = 0;
        while(k<temp.size() && temp[k] == '0') {
            k++;
        }
        temp = temp.substr(k);

       
        ans.s = temp;

        return ans;
        
    }

}

BigInteger multiply_magnitude(BigInteger a, BigInteger b) {
    BigInteger ans;
    ans.is_negative = 0;
    if(a.s.size() == 0 || b.s.size() == 0) {
        ans.is_negative = 0;
        ans.s = "0";
        return ans;
    }
    else {
        int n1 = a.s.size();
        int n2 = b.s.size();

        int result[n1+n2];

        for(int i=0;i<n1+n2;i++) {
            result[i] =0;
        }
      

        int a_idx = 0;
        int b_idx = 0;

        for(int i=n1-1;i>=0;i--) {
            int carry = 0;
            int num1 = a.s[i] - '0';

            b_idx = 0;

            for(int j=n2-1;j>=0;j--) {
                int num2 = b.s[j] - '0';

                int sum = num1*num2 + carry + result[a_idx+b_idx];
                carry = sum/10;

                result[a_idx + b_idx] = sum%10;
                b_idx++;
            }

            if(carry > 0 ) {
                result[a_idx + b_idx] += carry;
            }
            a_idx++;
        }

        int k = n1 + n2 - 1;
        while(k>=0 && result[k] == 0) {
            k--;
        }

        if(k==-1) {
            ans.s.push_back('0');
            return ans;
        }

        string temp = "";

        while(k>=0) {
            temp += result[k--] + '0';
        }

        ans.s = temp;
        return ans;


    }


}

bool operator==(BigInteger a, BigInteger b) {
    if(a.is_negative != b.is_negative) {
        return false;
    }
    else {
        if(compare_magnitude(a,b) == 2) {
            return true;
        }
        else {
            return false;
        }
    }
}



 bool operator!=(BigInteger a,BigInteger b) {

    if(a.is_negative != b.is_negative) {
        return true;
    }
    else {
        if(compare_magnitude(a,b) == 2) {
            return false;
        }
        else {
            return true;
        }
    } 
    
 }

bool operator<(BigInteger a,BigInteger b) {
    int temp = compare_magnitude(a,b);
    if(a.is_negative == 1) {
        if(b.is_negative == 0) {
            return true;
        }
        else {
            // both negative 
            if(temp == 1 || temp == 2) {
                // magnitude of a is smaller or equal than b but both are negative so a is larger
                return false;
            }
            else {
                // temp == 0
                return true;
            }
        }
    }
    else {
        // a is positve 
        if(b.is_negative == 0) {
            if(temp == 1) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
}


bool operator<=(BigInteger a,BigInteger b) {
    if(a==b || a<b) {
        return true;
    }
    else {
        return false;
    }
}


bool operator>(BigInteger a,BigInteger b) {
    if(a<=b) {
        return false;
    }
    else {
        return true;
    }
}


bool operator>=(BigInteger a,BigInteger b) {
    if(a > b || a==b) {
        return true;
    }
    else {
        return false;
    }
}



BigInteger BigInteger::operator+(BigInteger &c) {
    BigInteger ans;

    if(this->is_negative == 0 && c.is_negative == 0) {
        ans = add_magnitude( *this , c);
    }
    else if(this->is_negative == 1 && c.is_negative == 0) {
        ans = subtract_magnitude(c,*this);
    }
    else if(this->is_negative == 0 && c.is_negative == 1) {
        ans = subtract_magnitude(*this,c);
    }
    else {
        // a and b both negative 
        ans = add_magnitude(*this,c);
        ans.is_negative = 1;
    }
    return ans;
}

BigInteger BigInteger::operator-(BigInteger &c) {
    BigInteger ans;
    if(this->is_negative == 0 && c.is_negative == 0) {
        ans = subtract_magnitude( *this , c);
    }
    else if(this->is_negative == 1 && c.is_negative == 0) {
        ans = add_magnitude(c,*this);
        ans.is_negative = 1;
    }
    else if(this->is_negative == 0 && c.is_negative == 1) {
            ans = add_magnitude(c,*this);
    }
    else {
        // a and b both negative 
        ans = subtract_magnitude(c,*this);
        
    }
    return ans;
}

BigInteger BigInteger::operator*(BigInteger &c) {
     BigInteger ans = multiply_magnitude(*this,c);

    if(this->is_negative != c.is_negative) {
        ans.is_negative = 1;
    }
    else {
        ans.is_negative = 0;
    }

    return ans;
}