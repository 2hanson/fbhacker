#include <iostream>
#define LL long long
using namespace std;

const long maxn = 100005;
LL n, k;
LL a, b, c, r;
LL rec[maxn];
LL m[maxn];
LL ans;

void init()
{
    //ios_base::sync_with_stdio(false);
    LL cur;
    cin>>n>>k;
    cin>>a>>b>>c>>r;
    for (cur = 0; cur<= k; ++cur)
    {
        rec[cur] = 0;
    }

    m[0] = a;
    if (a <= k)
    {
        ++rec[a];
    }

    for (cur = 1; cur < k; ++cur)
    {
        m[cur] = (b*m[cur-1] + c)%r;
        if (m[cur] <= k)
        {
            ++rec[ m[cur] ];
        }
    }
}

LL find_the_min()
{
    LL cur;
    for (cur = 0; cur <= k; ++cur)
    {
        if (rec[cur] == 0)
        {
            break;
        }
    }

    return cur;
}

void solve()
{
    LL index = 0;
    LL cur;
    LL temp = k;
    //LL cycle = (n)% k+1;
    LL cycle = (n-k)%(k+1);
    
    for (cur = 1; cur <= cycle; ++cur)
    {
        temp = find_the_min();
        if (m[index] <= k)
        {
            --rec[ m[index] ];
        }
        m[index] = temp;
        if (temp <= k)
        {
            ++rec[temp];
        }
        ++index;
        index = index % k;
    }
    
    ans = temp;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int T;
    cin>>T;
    for (int Case = 1; Case <= T; ++Case)
    {
        cout<<"Case #"<<Case<<": ";
        init();
        
        solve();

        cout<<ans<<endl;
    }
    return 0;
}

