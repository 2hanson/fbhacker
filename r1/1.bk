#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>
#define LL long long
#define MOD 1000000007
using namespace std;

const int maxn = 10005;
int fact[maxn], invfact[maxn];

int powmod(int base, int expo){
	if(expo==0)
		return 1;
	else if(expo&1)
		return (long long)base*powmod(base, expo-1)%MOD;
	else{
		int root=powmod(base, expo>>1);
		return (long long)root*root%MOD;
	}
}
 
int inverse(int x){
	return powmod(x, MOD-2);
}
 
void init(){
	fact[0]=1;
	for(int i=1; i<=10000; i++)
		fact[i]=(long long)i*fact[i-1]%MOD;
	invfact[10000]=inverse(fact[10000]);
	for(int i= 10000; i>0; i--)
		invfact[i-1]=(long long)i*invfact[i]%MOD;
}

LL Lucas(LL a,LL b,LL p)
{
    LL n = a;
    LL r = b;
	if(r>n || r<0)
		return 0;
	return (long long)((long long)fact[n]*invfact[r]%MOD)*invfact[n-r]%MOD;

}

vector<LL> A;

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    int testCase;
    scanf("%d", &testCase);
    init();
//            ans = Lucas(n+m, n, Mod); 
    for (int testId = 1; testId <= testCase; ++testId)
    {
        int n, k;
        scanf("%d %d", &n, &k);
        A.clear();
        LL temp;
        for (int index = 0; index < n; ++index)
        {
            scanf("%lld", &temp);
            A.push_back(temp);
        }

        sort(A.begin(), A.end());
        
        LL ans = 0;
        for (int index = k-1; index < n; ++index)
        {
            ans +=  (Lucas(index, k-1, MOD) * A[index]);
            ans %= MOD;
        }

        printf("Case #%d: %lld\n", testId, ans);
    }

    return 0;
}

