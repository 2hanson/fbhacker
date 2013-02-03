#include <iostream>
#include <string>
#include <vector>
using namespace std;

int m;
string k1;
string k2;
int len;
bool flag;

class Section
{
    public:
        string key;
        int oindex;//opposite index
        int cv;//num of ?
        int f;

        Section(string tk, int toi)
        {
            key = tk;
            oindex = toi;
            cv = 0;
            for (int i = 0; i < key.length(); ++i)
            {
                if (key[i] == '?')
                {
                    ++cv;
                }
            }
            f = -1;
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
           if (temp->cv < k2Sections[k]->cv)
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
    flag = true;
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

int getmatchfactor(int f1, int g2)
{
    int fac = 0;
    for (int i = 0; i < len; ++i)
    {
        char t1 = k1Sections[f1]->key[i];
        char t2 = k2Sections[g2]->key[i];
        if (t1!='?' && t2!='?')
        {
            if (t1 != t1)
            {
                return -1;
            }
            else
            {
                ++fac;
            }
        }
    }
    return fac;
}

//
void rematch(int f1)
{
    int g2;
    int temp;
    for (g2 = k1Sections[f1]->oindex+1; g2 < k2Sections.size(); ++g2)
    {
            if (k2Sections[ g2 ]->oindex == -1)
            {
                if ((k2Sections[g2]->f=getmatchfactor(f1, g2))!=-1)
                {
                    match(f1, g2);
                    break;
                }
            }
            else 
            {
                if ((temp=getmatchfactor(f1, g2)) > k2Sections[g2]->f)
                {
                    rematch(k2Sections[g2]->oindex);
                    match(f1, g2);
                    k2Sections[g2]->f = temp;
                    break;
                }
            }
    }
    if (g2 == k2Sections.size())
    {
        flag = false;
    }
}

//stable matching problem
void work()
{
    int f1, g2;
    int temp;
    for (f1 = 0; f1 < k1Sections.size() && flag == true; ++f1)
    {
        for (g2 = 0; g2 < k2Sections.size() && flag == true; ++g2)
        {
            if (k2Sections[ g2 ]->oindex == -1)
            {
                if ((k2Sections[g2]->f=getmatchfactor(f1, g2))!=-1)
                {
                    match(f1, g2);
                    break;
                }
            }
            else 
            {
                if ((temp=getmatchfactor(f1, g2)) > k2Sections[g2]->f)
                {
                    rematch(k2Sections[g2]->oindex);
                    match(f1, g2);
                    k2Sections[g2]->f = temp;
                    break;
                }
            }
        }
        if (g2 == k2Sections.size())
        {
            flag = false;
        }
    }
}

void output()
{
    if (flag == false)
    {
        cout<<"IMPOSSIBLE"<<endl;
    }
    else
    {
        
    }
}

int main()
{
    int T;
    cin>>T;
    for (int tid = 1; tid <= T; ++tid)
    {
        read();
        pre_init();
        work();
        output();
    }
}

