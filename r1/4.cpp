#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long i64;

int main(void) {
	int m;
	cin >> m;
	for(int ts=1; ts<=m; ts++) {
		int W,H,P,Q,N,X,Y,a,b,c,d;
		cin >> W >> H >> P >> Q >> N >> X >> Y >> a >> b >> c >> d;
		vector<int> deads[50000];
		vector<int> cur(H, P);
		for(int i=0; i<N; i++) {
			//cout << X << " " << Y << endl;
			deads[X].push_back(Y);
			int X2=(X*a+Y*b+1)%W;
			Y=(X*c+Y*d+1)%H;
			X=X2;
		}

        int ret=0;
		for(int w=0; w<W; w++) {
			//for(int h=0; h<H; h++) cur[h]=max(cur[h]-1,0);
			for(int i=0; i<deads[w].size(); i++)
            {
                cur[deads[w][i]]=P+w+1;
            }
                //for(int i=0; i<deads[w].size(); i++) cout << deads[w][i] << ","; cout << endl;
			int streak=0;
			for(int h=0; h<H; h++) {
                cout<<"w: "<<w<<" :h "<<h<<" cur="<<cur[h]<<endl;
                if(cur[h]>w+1) streak=0;
				else {
					streak++;
					if(streak>=Q) 
                    {
                cout<<"fuck: "<<"w: "<<w<<" :h "<<h<<" cur="<<cur[h]<<endl;
                        ret++;
                    }
				}
				//cout << streak << " ";
			}
			//cout << endl;
		}
		cout << "Case #" << ts << ": " << ret << endl;
	}
}
