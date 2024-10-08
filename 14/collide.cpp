#include <string>
#include <iostream>

using namespace std;
const int m = 3021;

string get_next(string x)
{
    if (x[2] < 'z')
        x[2]++;
    else if (x[1] < 'z')
    {
        x[1]++;
        x[2] = 'a';
    }
    else
    {
        x[0]++;
        x[1] = 'a';
        x[2] = 'a';
    }
    return x;
}

int h(string x)
{
    int hash = 0;
    for (int i = 0; i < x.length(); i++)
        hash = (hash * 31 + x[i]) % m;
    return hash;
}

int main()
{
    for (string x = "aaa"; x <= "zzz"; x = get_next(x))
        for (string y = get_next(x); y <= "zzz"; y = get_next(y))
            if (h(x) == h(y))
            {
                cout << x << " " << y << endl;
                return 0;
            }
    return 0;
}