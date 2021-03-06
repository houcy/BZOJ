#include <cstdio>
#include <algorithm>
using namespace std;

const int T=105,N=105,M=100005,
	a[300][2]={{0,0},{2,1},{4,2},{10,3},{28,4},{82,5},{244,6},{730,7},{2188,8},{6562,9},{19684,10},{59050,11},{M,0}},
	b[300][2]={{1,0},{3,2},{7,3},{9,4},{25,5},{73,6},{81,8},{91,6},{97,8},{109,6},{113,8},{127,6},{129,8},{241,9},{271,8},{289,9},{325,8},{337,9},{379,8},{385,9},{721,10},{811,9},{865,10},{973,9},{1009,10},{1135,9},{1153,10},{2161,11},{2431,10},{2593,11},{2917,10},{3025,11},{3403,10},{3457,11},{6481,12},{6561,16},{6643,12},{6721,16},{6805,12},{6881,16},{6913,14},{6967,12},{7041,16},{7129,12},{7201,16},{7291,11},{7777,12},{7841,16},{7939,12},{8001,16},{8065,14},{8101,12},{8161,16},{8263,12},{8321,16},{8425,12},{8481,16},{8587,12},{8641,16},{8749,11},{9073,12},{9121,16},{9235,12},{9281,16},{9397,12},{9441,16},{9559,12},{9601,16},{9721,12},{9761,16},{9883,12},{9921,16},{10045,12},{10081,16},{10207,11},{10369,12},{10401,16},{10531,12},{10561,16},{10693,12},{10721,16},{10855,12},{10881,16},{11017,12},{11041,16},{11179,12},{11201,16},{11341,12},{11361,16},{11503,12},{11521,16},{11665,12},{11681,16},{11827,12},{11841,16},{11989,12},{12001,16},{12151,12},{12161,16},{12313,12},{12321,16},{12475,12},{12481,16},{12637,12},{12641,16},{12799,12},{12801,16},{19681,17},{19927,16},{20161,17},{20413,16},{20641,17},{20737,16},{21121,17},{21385,16},{21601,17},{21871,16},{23521,17},{23815,16},{24001,17},{24193,16},{24481,17},{24787,16},{24961,17},{25273,16},{25441,17},{25759,16},{25921,17},{26245,16},{27361,17},{27703,16},{27841,17},{28189,16},{28321,17},{28675,16},{28801,17},{29161,16},{29281,17},{29647,16},{29761,17},{30133,16},{30241,17},{30619,16},{31201,17},{31591,16},{31681,17},{32077,16},{32161,17},{32563,16},{32641,17},{33535,16},{33601,17},{34021,16},{34081,17},{34993,16},{35041,17},{35965,16},{36001,17},{36451,16},{36481,17},{36937,16},{36961,17},{37423,16},{37441,17},{37909,16},{37921,17},{38395,16},{38401,17},{59041,18},{59779,17},{60481,18},{61237,17},{61921,18},{62209,17},{63361,18},{64153,17},{64801,18},{65611,17},{70561,18},{71443,17},{72001,18},{72577,17},{73441,18},{74359,17},{74881,18},{75817,17},{76321,18},{77275,17},{77761,18},{78733,17},{82081,18},{83107,17},{83521,18},{84565,17},{84961,18},{86023,17},{86401,18},{87481,17},{87841,18},{88939,17},{89281,18},{90397,17},{90721,18},{91855,17},{93601,18},{94771,17},{95041,18},{96229,17},{96481,18},{97687,17},{97921,18},{M,0}};

int t,f,m,sg[M];
int L,R,D,flag,cov[M*4][2];

void cover(int cur,int beg,int end){
	if(end<=L||beg>=R) return;
	if(L<=beg&&R>=end){
		cov[cur][flag]|=D;
		return;
	}
	int mid=beg+end>>1;
	cover(cur<<1,beg,mid);
	cover(cur<<1|1,mid,end);
}

int query(int cur,int beg,int end){
	if(end-beg==1)
		return cov[cur][flag];
	int mid=beg+end>>1;
	if(L<mid)
		return cov[cur][flag]|query(cur<<1,beg,mid);
	else
		return cov[cur][flag]|query(cur<<1|1,mid,end);
}

void init(){
	if(f<=2){
		for(int j=0;a[j][0]<m;j++)
			for(int i=a[j][0];i<a[j+1][0];i++) if(!(i&1))
				sg[i]=a[j][1];
		for(int j=0;b[j][0]<m;j++)
			for(int i=b[j][0];i<b[j+1][0];i++) if(i&1)
				sg[i]=b[j][1];
	}
	else
	for(int x=0;x<m;x++){
		if(sg[x]);
		else
		if(x<f)
			sg[x]=0;
		else{
			L=x;
			flag=x&1;
			int tmp=query(1,0,m);
			for(sg[x]=0;tmp>>sg[x]&1;sg[x]++);
		}
		if(x<=1) continue;
		for(int d=2;d<m;d++){
			L=d*(x-1),R=d*x;
			if(L>=m) break;
			R=min(R,m);
			if(!(d&1)){
				D=1<<(sg[x-1]^sg[x]);
				flag=!(L&1);
				cover(1,0,m);
			}
			else{
				D=1<<sg[x];
				flag=!(L&1);
				cover(1,0,m);
				D=1<<sg[x-1];
				flag=L&1;
				cover(1,0,m);
			}
		}
	}
}

int seq[T][N];

int main(){
	scanf("%d%d",&t,&f);
	for(int i=0;i<t;i++){
		scanf("%d",&seq[i][0]);
		for(int j=1;j<=seq[i][0];j++){
			scanf("%d",&seq[i][j]);
			m=max(m,seq[i][j]);
		}
	}
	m++;
	init();
	for(int i=0;i<t;i++){
		int ans=0;
		for(int j=1;j<=seq[i][0];j++)
			ans^=sg[seq[i][j]];
		printf("%d%c",ans?1:0," \n"[i==t-1]);
	}
}
