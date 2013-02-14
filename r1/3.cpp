#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
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
vector<P*> rec;

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
    rec.clear();
    //should rethink
    //x: 0 -- (w-p)
    //y: 0 -- (h-q)
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

bool isHave(int tx, int ty)
{
    for (int i = 0; i < rec.size(); ++i)
    {
        if (rec[i]->x == tx && rec[i]->y==ty)
        {
            return true;
        }
    }

    return false;
}

void work()
{
    P* temp;
        for (int k = 0; k < ps.size(); ++k)
        {
            int tempx = ps[k]->x;
            int tempy = ps[k]->y;

            //leftx, rightx;
            //upy, downy;
            //x:max(0, rightx-p+1) -- min(w-p, leftx + p-1);
            //y:max(q-1, downy-q+1) -- min(h-1, upy+q-1)
            //x: 0 -- (w-p)
            //y: 0 -- (h-q)
            for (int tx = max(0, tempx-p+1); tx <= min(w-p, tempx); ++tx)
            {
                for (int ty = max(0, tempy-q+1); ty <= min(h-q, tempy); ++ty)
                {
                    if (isHave(tx, ty) == false/*rec[tx][ty] == 0*/)
                    {
                        --ans;
                        temp = new P(tx, ty);                   
                        rec.push_back(temp);
                    }
                }
            }
        }
}

int main()
{
    freopen("3.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
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

