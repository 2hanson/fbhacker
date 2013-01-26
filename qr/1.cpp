#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

const int maxn = 26;
const int LINE_LENGTH = 505;
int chs[30];

void testOut()
{
    char ch;
    for (int i = 0; i < maxn; ++i)
    {
        ch = 'a'+i;
        cout<<ch<<" ";
    }
    cout<<endl;
    for (int i = 0; i < maxn; ++i)
    {
        cout<<chs[i]<<" ";
    }
    cout<<endl;
}

void isort(int tchs[])
{
    for (int i = 0; i < maxn; ++i)
    {
        int k = i-1;
        int temp = tchs[i];
        while (k>=0 && temp>tchs[k])
        {
            tchs[k+1] = tchs[k];
            --k;
        }
        tchs[k+1] = temp;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    string bstr;
    long bvalue;
    int m;
    cin>>m;
    getchar();
    for (int Case = 1; Case <= m; ++Case)
    {
        cout<<"Case #"<<Case<<": ";
       
        getline(cin, bstr);

        for (int i = 0; i < maxn; ++i)
        {
            chs[i] = 0;
        }

        for (int len = 0; len < bstr.length(); ++len)
        {
            if (bstr[len]>='A'&&bstr[len]<='Z')
            {
                ++chs[bstr[len] - 'A'];                        
            }
            else if (bstr[len]>='a'&&bstr[len]<='z')
            {
                ++chs[bstr[len] - 'a'];
            }
        }
        isort(chs);

        bvalue = 0;
        for (int i = 0; i < maxn; ++i)
        {
            if (chs[i] == 0)
                break;

            bvalue += (26-i)*chs[i];
        }

        cout<<bvalue<<endl;
    }
    return 0;
}

