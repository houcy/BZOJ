/*
�����������ʣ�ÿ�Թ�����(a,b)������(m,n)һһ��Ӧ������
a=m^2-n^2
b=2*m*n
c=sqrt(a^2+b^2)=m^2+n^2
����m,n���ܲ�����������Ϊ��֤������������ 
a=k(m^2-n^2)
b=k(2*m*n)
c=k(sqrt(a^2+b^2)=m^2+n^2)
gcd(m,n)=1
������������������
���ڻ��ʹ������ԣ���k=1����Ҫ��֤gcd(m,n)=1
����gcd(a,b)=1
����b=2*m*n<=maxh
����ö��mö��n�����Ӷ���O(maxh ln maxh)
��(a,b)�����ߣ�����ͼ
����ÿ����ͨ�飬dfs��һ��������
���ڷ����ߣ�O(2^...)����ö�ٷ��������˵ĵ�ȡ�Ͳ�ȡ
��������DP
��Ȼ���Ǳ��㣬���ǻ��Ƿ������㷨�����Ա���������cha�� 
*/
#include <cstdio>
const int N=1000005,M=N,mo=(int)1e9+7;
int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return a;
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int maxh,t,m=1,root,cnt[N],fa[N],son[N],ed[M],next[M],pw2[N];
int vis[N],flag[N],num[N];
int seq[N],te[N];
int f[N][2];
void dfs(int u){
	vis[u]=1;
	for(int e=son[u];e;e=next[e]){
		int v=ed[e];
		if(v==fa[u]||!cnt[v]) continue;
		if(vis[v]){
			if(!num[u]||!num[v])
				te[++*te]=e;
			if(!num[u])
				seq[num[u]=++*seq]=u;
			if(!num[v])
				seq[num[v]=++*seq]=v;
		}
		else{
			fa[v]=u;
			dfs(v);
		}
	}
}
void dp(int u){
	vis[u]++;
	f[u][0]=flag[u]>0?0:1;
	f[u][1]=flag[u]<0?0:(pw2[cnt[u]]+mo-1)%mo;
	for(int e=son[u];e;e=next[e]){
		int v=ed[e];
		if(v==fa[u]||!cnt[v]) continue;
		if(vis[v]!=vis[u]){
			dp(v);
			f[u][0]=1LL*f[u][0]*f[v][1]%mo;
			f[u][1]=1LL*f[u][1]*f[v][0]%mo;
		}
	}
	f[u][1]=(f[u][1]+f[u][0])%mo;
}
int search(int i){
	if(i>*seq){
		for(int j=1;j<=*te;j++){
			int e=te[j];
			if(flag[ed[e]]>0&&flag[ed[e^1]]>0)
				return 0;
		}
		dp(root);
		return f[root][1];
	}
	int u=seq[i];
	flag[u]=-i;
	int ret=search(i+1);
	flag[u]=i;
	(ret+=search(i+1))%=mo;
	flag[u]=0;
	return ret;
}
int main(){
	t=getint();
	pw2[0]=1;
	for(int i=1;i<=t;i++)
		pw2[i]=pw2[i-1]*2LL%mo;
	while(t--){
		int h=getint();
		cnt[h]++;
		if(h>maxh) maxh=h;
	}
	for(int m=1;m*2<=maxh;m++){
		for(int n=m&1?2:1;n<m&&2LL*m*n<=maxh;n+=2) if(gcd(m,n)==1){
			long long a=1LL*m*m-1LL*n*n,b=2LL*m*n;
			if(a<=maxh&&b<=maxh){
				#define m ::m
				++m;
				ed[m]=b;
				next[m]=son[a];
				son[a]=m;
				++m;
				ed[m]=a;
				next[m]=son[b];
				son[b]=m;
				#undef m
			}
		}
	}
	int ans=1;
	for(int i=1;i<=maxh;i++) if(cnt[i]&&!vis[i]){
		root=i;
		*seq=0;
		*te=0;
		dfs(i);
		int tmp=search(1);
		ans=1LL*ans*tmp%mo;
	}
	printf("%d\n",(ans+mo-1)%mo);
}
