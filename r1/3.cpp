#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int w, h, p, q;
long n, X, Y, a, b, c, d;
long long ans;

class P
{
    public:
        long x;
        long y;

        P(long tx, long ty)
        {
            x = tx;
            y = ty;
        }
};

vector<P*> deadps;
vector<P*> ps;

void test_deadps()
{
    cout<<"test begin"<<endl;
    for (int i = 0; i < deadps.size(); ++i)
    {
        cout<<deadps[i]->x<<" "<<deadps[i]->y<<endl;
    }
}

void read()
{
    scanf("%d %d %d %d %ld %ld %ld %ld %ld %ld %ld", &w, &h, &p, &q, &n, &X, &Y, &a, &b, &c, &d);
}

void init()
{
    //should rethink
    //x: 0 -- (w-p)
    //y: (q-1) -- (h-1)

    ans = (w-p+1)*(h-q+1);
}

//
bool compare(P* tp, P* other)
{
    if (tp->x < other->x)
    {
        return true;
    }
    else if (tp->x == other->x)
    {
        return tp->y < other->y;
    }
    else
    {
        return false;
    }
}

void test_ps()
{
    cout<<"ps"<<endl;
    for (int i = 0; i < ps.size(); ++i)
    {
        cout<<ps[i]->x<<" "<<ps[i]->y<<endl;
    }
}

void rmDup()
{
    ps.clear();
    ps.push_back(deadps[0]);

    //test_deadps();
    for (int i = 1; i < deadps.size(); ++i)
    {
        if (deadps[i]->x!=ps[ps.size()-1]->x && deadps[i]->y!=ps[ps.size()-1]->y)
        {
            ps.push_back(deadps[i]);
        }
    }
    //test_ps();
}

void make_dead_p()
{
    P* tp;
    deadps.clear();
    tp = new P(X, Y);
    deadps.push_back( tp );
    long prex = X;
    long prey = Y;
    long cx;
    long cy;
    for (int i = 1; i < n; ++i)
    {
        cx = (prex*a + prey*b + 1)%w;
        cy = (prex*c + prey*d + 1)%h;
        tp = new P(cx, cy);
        deadps.push_back(tp);
        prex = cx;
        prey = cy;
    }
 
    sort(deadps.begin(), deadps.end(), compare);
    rmDup();
}

void output(int tid)
{
    cout<<"Case #"<<tid<<": "<<ans<<endl;
}

void work()
{
    test_ps();
    int flag = 1;
    for (int num = 1; num <= ps.size(); ++num)
    {
        flag *= -1;
        for (int k = 0; k < ps.size(); k += num)
        {
            int leftx = ps[k]->x;
            int rightx = ps[k]->x;
            int upy = ps[k]->y;
            int downy = ps[k]->y;

            for (int tk = k + 1; tk < (k+num) && tk<ps.size(); ++tk)
            {
                if (ps[tk]->x < leftx)
                {
                    leftx = ps[tk]->x;
                }
                if (ps[tk]->x > rightx)
                {
                    rightx = ps[tk]->x;
                }
                if (ps[tk]->y < upy)
                {
                    upy = ps[tk]->y;
                }
                if (ps[tk]->y > downy)
                {
                    downy = ps[tk]->y;
                }
            }
            //leftx, rightx;
            //upy, downy;
            //x:max(0, rightx-p+1) -- min(w-1, leftx + p-1);
            //y:max(0, downy-q+1) -- min(h-1, upy+q-1)
        
            ans += flag*( (1+min(w-1, leftx+p-1)-max(0, rightx-p+1)) * (1+min(h-1, upy+q-1)-max(0, downy-q+1)) );
            cout<<"ans = "<<ans<<endl;
        }
    }
}

int main()
{
    //freopen("3.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int test;
    scanf("%d", &test);
    for (int tid = 1; tid<=test; ++tid)
    {
        read();
        //sory by x, y and no dup
        make_dead_p();
        init();
        
        work();
        output(tid);
    }

    return 0;
}

