/*
����ģ���˻�2^nö�ٵ�3��ķ������Ȱ�ĳ��ֵ���������������λ��
ԭ��ȷ�����㷨��ͬ��2^nö�ٵ�3��ķ��������������ʣ�1.A�����İ���һ�������е�1����ǰ����2���ں�B����ͬ����2.��1������������е����λ����ͬ����2��ͬ���������Ϳ��Զ��ִ𰸣�����ÿһ�࣬ǰ��ļ�����ǰ�棬����ļ�������棬��¼��ǰ�����λ�õ�����ָ��Ĳ�dis���Ϸ�������������a<=dis�����ص�����Ȼ��̰�ĵط�ʹ��dis��С���ĺϷ������� 
*/
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=22;
int n,lim;
bool ok;
struct task{
	int t,a,b;
} tas[N];
bool cmpt(const task &a,const task &b){
	return a.t<b.t;
}
bool cmpa(const task &a,const task &b){
	return a.a<b.a;
}
bool cmpb(const task &a,const task &b){
	return a.b<b.b;
}
int sum[3][3];
#define calc1(i) (tas[i].b-tas[i].a)
#define calc2(i) (tas[i].a-tas[i].b)
struct cmp{
	bool operator () (const int i,const int j){
		return tas[i].b-tas[i].a<tas[j].b-tas[j].a;
	}
};
bool flag[N];
bool work(){
	for(int i=0;i<n;i++) flag[i]=false;
	if(sum[1][1]+sum[1][2]>lim){
		int dis=lim-sum[1][2];
		int Cnt=0;
		for(int i=0;i<n;i++) if(tas[i].t==1) Cnt++;
		while(Cnt--){
			int k=-1;
			for(int i=0;i<n;i++) if(tas[i].t==1&&!flag[i]&&tas[i].a<=dis)
				if(k==-1||calc1(i)>calc1(k))
					k=i;
			if(k==-1) return false;
			flag[k]=true;
			dis+=calc1(k);
		}
		return true;
	}
	else{
		int dis=lim-sum[2][1];
		int Cnt=0;
		for(int i=0;i<n;i++) if(tas[i].t==2) Cnt++;
		while(Cnt--){
			int k=-1;
			for(int i=0;i<n;i++) if(tas[i].t==2&&!flag[i]&&tas[i].b<=dis)
				if(k==-1||calc2(i)>calc2(k))
					k=i;
			if(k==-1) return false;
			flag[k]=true;
			dis+=calc2(k);
		}
		return true;
	}
}
void dfs(int i){
	if(i==n){
		ok=work();
		return;
	}
	if(tas[i].t!=3){
		sum[tas[i].t][1]+=tas[i].a;
		sum[tas[i].t][2]+=tas[i].b;
		dfs(i+1);
		sum[tas[i].t][1]-=tas[i].a;
		sum[tas[i].t][2]-=tas[i].b;
		return;
	}
	tas[i].t=1;
	sum[tas[i].t][1]+=tas[i].a;
	sum[tas[i].t][2]+=tas[i].b;
	dfs(i+1);
	sum[tas[i].t][1]-=tas[i].a;
	sum[tas[i].t][2]-=tas[i].b;
	if(ok){
		tas[i].t=3;
		return;
	}
	tas[i].t=2;
	sum[tas[i].t][1]+=tas[i].a;
	sum[tas[i].t][2]+=tas[i].b;
	dfs(i+1);
	sum[tas[i].t][1]-=tas[i].a;
	sum[tas[i].t][2]-=tas[i].b;
	tas[i].t=3;
}
int main(){
	scanf("%d",&n);
	int sa=0,sb=0;
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&tas[i].t,&tas[i].a,&tas[i].b);
		sa+=tas[i].a;
		sb+=tas[i].b;
	}
	sort(tas,tas+n,cmpt);
	int l=max(sa,sb)-1,r=sa+sb;
	while(r-l>1){
		lim=(l+r)/2;
		ok=false;
		dfs(0);
		if(ok)
			r=lim;
		else
			l=lim;
	}
	printf("%d\n",r);
}
