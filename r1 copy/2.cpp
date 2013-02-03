#include <iostream>
#include <string>
#include <vector>
using namespace std;

int m;
string k1;
string k2;
int len;
int flag;

class Section
{
    public:
        string key;
        int oindex;//opposite index

        Section(string tk, int toi)
        {
            key = tk;
            oindex = toi;
        }
};

vector<Section*> k1Sections;
vector<Section*> k2Sections;

void test_Pre_Init()
{
    cout<<"m == "<<m<<" k1s.size()=="<<k1Sections.size()<<endl;
    cout<<"k1"<<endl;
    for (int i = 0; i < k1Sections.size(); ++i)
    {
        cout<<k1Sections[i]->key<<" "<<k1Sections[i]->oindex<<endl;
    }
    cout<<"k2"<<endl;
    for (int i = 0; i < k2Sections.size(); ++i)
    {
        cout<<k2Sections[i]->key<<" "<<k2Sections[i]->oindex<<endl;
    }

}

void read()
{
    cin>>m>>k1>>k2;
}

//sort k2sections by the num of ?, the less the first
//because the size if <= 50, so just use insert_sort
void insert_sort()
{
    int index, k;
    for (index = 0; index < k2Sections.size(); ++index)
    {
        Section* temp = k2Sections[index];
        for (k = index - 1; k >= 0; --k)
        {
           if (temp->key < k2Sections[k]->key)
           {
                k2Sections[k+1] = k2Sections[k];
           }
            else
            {
                break;
            }
        }

        k2Sections[k+1] = temp;
    }
}

void pre_init()
{
    flag = 0;
    len = k1.length()/m;
    k1Sections.clear();
    k2Sections.clear();
    for (int index = 0; index < k1.length(); index += len)
    {
        //cout<<k1.substr(index, len)<<endl;
        Section *t1 = new Section(k1.substr(index, len), -1);
        k1Sections.push_back( t1 );
        Section *t2 = new Section(k2.substr(index, len), -1);
        k2Sections.push_back( t2 );
    }
    //sort k2sections by the num of ?, the less the first
    insert_sort();
}

void match(int f1, int g2)
{
    k1Sections[f1]->oindex = g2;
    k2Sections[g2]->oindex = f1;
}

void unmatch(int f1, int g2)
{
    k1Sections[f1]->oindex = -1;
    k2Sections[g2]->oindex = -1;
}

int getmatchfactor(int f1, int g2)
{
    for (int i = 0; i < len; ++i)
    {
        char t1 = k1Sections[f1]->key[i];
        char t2 = k2Sections[g2]->key[i];
        if (t1!='?' && t2!='?')
        {
            if (t1 != t2)
            {
                return -1;
            }
        }
    }
    
    return 1;
}

void dfs(int f1)
{
    if (flag == -1 || flag == 1)
    {
        return;
    }


    if (f1 == k1Sections.size())
    {
        flag = 1;
        return;
    }

    int g2;
    for (g2 = 0; g2 < k2Sections.size() && flag==0; ++g2)
    {
        if (k2Sections[ g2 ]->oindex == -1)
        {
            if (getmatchfactor(f1, g2) != -1)
            {
                match(f1, g2);
                dfs(f1+1);
                if (flag != 0)
                {
                    return;
                }
                unmatch(f1, g2);
            }
        }
    }

}

void check()
{
    int f1, g2;
    for (f1 = 0; f1 < k1Sections.size(); ++f1)
    {
        for (g2 = 0; g2 < k2Sections.size(); ++g2)
        {
            if (getmatchfactor(f1, g2) != -1)
            {
                break;
            }
        }

        if (g2 == k2Sections.size())
        {
            flag = -1;
            return;
        }
    }
}

//stable matching problem
void work()
{
    flag = 0;
    check();
    dfs(0);
}

void output(int tid)
{
    cout<<"Case #"<<tid<<": ";
    if (flag==0 || flag==-1)
    {
        cout<<"IMPOSSIBLE"<<endl;
    }
    else
    {
        for (int i = 0; i < k1Sections.size(); ++i)
        {
            int oindex = k1Sections[i]->oindex;
            for (int t = 0; t < len; ++t)
            {
                char ch1 = k1Sections[i]->key[t];
                char ch2 = k2Sections[ oindex ]->key[t];
                if (ch1=='?' && ch2=='?')
                {
                    cout<<'a';
                }
                else if (ch1 != '?')
                {
                    cout<<ch1;
                }
                else
                {
                    cout<<ch2;
                }
            }

        }
        cout<<endl;
    }
}

int main()
{
    freopen("2.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int T;
    cin>>T;
    for (int tid = 1; tid <= T; ++tid)
    {
        read();
        pre_init();
        work();
        output(tid);
    }
}

