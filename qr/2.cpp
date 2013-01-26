#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <vector>

using namespace std;

vector<int> pars;
bool flag;

void testOut()
{
    for (int i = 0; i < pars.size(); ++i)
    {
        cout<<pars[i]<<" ";
    }
    cout<<endl;
}

void dfs_L2R(int cur)
{
    if (flag == false)
    {
        return;
    }

    int tcur = cur;
    int len = pars.size()-1;
    while (tcur<=len && flag == true)
    {
        //(
        if (pars[tcur] == 0)
        {
            int temp = tcur + 1;
            int rec = -1;
            while (temp <= len)
            {
                if (pars[temp] == 1)
                {
                    pars[tcur] = -1;
                    pars[temp] = -1;
                    break;
                }
                else if (pars[temp] == 0)
                {
                    dfs_L2R(temp);
                }
                else if (rec==-1 && pars[temp]==3)
                {
                    rec = temp;
                }

                ++temp;
            }

            if (temp > len)
            {
                if (rec < 0)
                {
                    pars[tcur] = -2;
                    flag = false;
                    return;
                }
                else
                {
                    pars[tcur] = -1;
                    pars[rec] = -1;
                }
            }
        }

        ++tcur;
    }
}

void dfs_R2L(int cur)
{
    if (flag == false)
    {
        return;
    }
    int tcur = cur;
    while (tcur >= 0 && flag == true)
    {
        //)
        if (pars[tcur] == 1)
        {
            int temp = tcur - 1;
            int rec = -1;
            while (temp >= 0)
            {
                if (pars[temp] == 0)
                {
                    pars[tcur] = -1;
                    pars[temp] = -1;
                    break;
                }
                else if (pars[temp] == 1)
                {
                    dfs_R2L(temp);
                }
                else if (rec==-1 && pars[temp] == 2)
                {
                    rec = temp;
                }

                --temp;
            }

            if (temp < 0)
            {
                if (rec<0)
                {
                    pars[tcur] = -2;
                    flag = false;
                    return;
                }
                else
                {
                    pars[tcur] = -1;
                    pars[rec] = -1;
                }
            }
        }

        --tcur;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int T;
    cin>>T;
    string bstr;
    getchar();
    for (int Case = 1; Case<=T; ++Case)
    {
        cout<<"Case #"<<Case<<": ";
        getline(cin, bstr);
        
        pars.clear();
        
        int len = bstr.length();
        for (int cur = 0; cur < bstr.length(); ++cur)
        {
            if (bstr[cur] == ':' && cur+1<len)
            {
                //:(
                if (bstr[cur+1] == '(')
                {
                    pars.push_back(2);
                    ++cur;
                }
                //:)
                else if (bstr[cur+1] == ')')
                {
                    pars.push_back(3);
                    ++cur;
                }
                
            }
            else if (bstr[cur] == '(')
            {
                //(
                pars.push_back(0);
            }
            //)
            else if (bstr[cur] == ')')
            {
                pars.push_back(1);
            }
        }

        flag = true;
        
        //testOut();
        //left -> right
        dfs_R2L( pars.size()-1 );
        dfs_L2R( 0 );
        //testOut();
        if (flag == true)
        {
            cout<<"YES";
        }
        else
        {
            cout<<"NO";
        }
        cout<<endl;
    }
    return 0;
}

