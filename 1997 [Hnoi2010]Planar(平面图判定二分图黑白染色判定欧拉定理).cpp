/*
����һ���ߣ�Ҫô�ڻ��ڣ�Ҫô�ڻ��⡣����������н��棬��ô����һ��һ���ڻ���һ���ڻ��⡣
����ͼ�ڰ�Ⱦɫ���ɡ�
��ŷ����������m>3*n+6һ������ƽ��ͼ 
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=210,M=10005;
int n,m,num[N];

struct edge{
	int u,v;
} E[M];

int c[N*3],g[N*3][N*3];

bool color(int u,int col){
	if(c[u]!=-1) return c[u]==col;
	c[u]=col;
	for(int j=1;j<=*g[u];j++)
		if(!color(g[u][j],1-col))
			return false;
	return true;
}

bool work(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",&E[i].u,&E[i].v);
	}
	for(int i=0;i<n;i++){
		int u; scanf("%d",&u);
		num[u]=i;
	}
	if(m>3*n+6) return false;
	for(int i=0;i<m;i++){
		E[i].u=num[E[i].u];
		E[i].v=num[E[i].v];
		if(E[i].u>E[i].v) swap(E[i].u,E[i].v);
	}
	for(int i=0;i<m;i++) *g[i]=0,c[i]=-1;
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			if(E[i].u<E[j].u&&E[j].u<E[i].v&&E[i].v<E[j].v){
				g[i][++*g[i]]=j;
				g[j][++*g[j]]=i;
			}
	for(int i=0;i<m;i++) if(c[i]==-1&&!color(i,0))
		return false;
	return true;
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--)
		puts(work()?"YES":"NO");
}
