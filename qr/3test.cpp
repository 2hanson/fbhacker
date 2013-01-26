#include <iostream>
using namespace std;

int main()
{
    int n, k;
    cin>>n>>k;
    int a, b, c, r;
    cin>>a>>b>>c>>r;
    int pre = a;
    for (int i = 0; i < k; ++i)
    {
        int cur = (b*pre + c) % r;
        cout<<cur<<" ";
        pre = cur;
    }
    cout<<endl;
    return 0;
}
