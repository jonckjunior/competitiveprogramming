#include <bits/stdc++.h>
using namespace std;

int gcd_extended(int a, int b, int& x, int& y){
    if(a == 0) {x = 0; y = 1; return b;}
    if(b == 0) {x = 1; y = 0; return a;}
    
    /*
        Lets divide in 2 parts:
        1. Proving that the d is correct
        2. Proving that x and y are correct
        
        
        
        1. d is the GCD of (a,b) and d is correct.
            let's say that d = gcd(a, b)
            so, d|a and d|b, where x|y means x divides y (2|4).
            we need to prove that d|b and d|(a%b)
            1.1.
                d|b is trivial from the fact that d = gcd(a,b)
            1.2.
                instead of writing as a%b let's write as:
                    a%b = a - (a/b)*b 
                where the division is implicitly the floor.
                as d|a, we have that a = x.d
                and, as d|b we have that b = y.d
                let's say that a/b = k
                so:
                    a%b = x.d - k.y.d
                    a%b = d.(x - k.y)
                we can see that a%b is of the form z.d, so d | (a%b).
            1.3
                the base case is gcd(x, 0) = x
                or gcd(0, x) = x
                and that is correct by definition
        2. If we calculate the answer for (b, a%b) we can use it to calculate (a,b)
            So, we want to calculate ax + by = d, where d = gcd(a,b) for any
            integer (a,b)
            
            let's say that x0 and y0 are the answers for (b, a%b), how can we use that?
            we know that:
                (b)*x0 + (a%b)*y0 = d (from the first theorem as gcd(a,b) = gcd(b, a%b))
            we need to re-write a%b as: a - (a/b)*b
                (b)*x0 + (a - (a/b)*b)*y0 = d
                (b)*x0 + y0*a - (a/b)*b*y0 = d
                (b)*(x0 - (a/b)*y0) + y0*a = d
                a*y0 + b*(x0 - (a/b)*y0) = d
            In conclusion, we have that:
                ax + by = a*y0 + b*(x0 - (a/b)*y0)
                x = y0
                y = (x0 - (a/b)*y0)
            
            Obs: The case base case when a = 0 means that gcd(a, b) = gcd(0, b) = b
            So whe have that 0.x + b.y = b and we derive that
                x = 0 and y = 1
            The same applyes if b = 0 instead.
        
    */
    
    int x0, y0;
    int d = gcd_extended(b, a%b, x0, y0);
    x = y0;
    y = x0-(a/b)*y0;
    return d;
}

int main(){
    int x, y;
    int d = gcd_extended(4, 10, x, y);
    cout << d << endl;
    cout << x << " " << y << endl;
    return 0;
}
