/*
���޸�CDQ���Ρ�
���ڵ�ǰ�޸����䣬���ǿ��ǵ�ǰ�����ڵ��޸Ķ�ͼ��Ӱ�졣

Contraction:
�����б��޸ĵı�Ȩ��Ϊ-oo����Kruskal��
��Щ�����޸Ķ�����С�������еı�һ���ڵ�ǰ��������ѯ�ʺ����С�������С�
���Կ��԰���Щ����������

Reduction:
�����б��޸ĵı�Ȩ��Ϊ+oo����Kruskal��
��Щ�����޸Ķ�������С�������еı�һ�����ڵ�ǰ��������ѯ�ʺ����С�������С�
���Կ��԰���Щ��ɾ����

����ͼ�Ĺ�ģ�ͼ�С�ˡ��ݹ��������ߡ�

�赱ǰ����ѯ����ΪK��ͼ�Ĺ�ģ����С��
������K+1��
	֤������Contraction����������������ΪK��
������2K��
	֤������Reduction������������+oo�ı�ȫ�������������У����ڵ���ΪK+1���ʸ�����������ΪK���ټ������б��޸ıߣ���2K�� 

���и��Ӷȣ�O(Q log Q (log Q + ��(Q)))
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=20100,M=50100,Q=50100,logQ=18,inf=(int)1e9;
int n,m,q;
long long ans;

int memw[M];

struct edge{
	int u,v,*w,flag,lab;
	void read(){
		scanf("%d%d%d",&u,&v,w);
		u--;
		v--;
	}
} memE[Q*2*2];
struct modi{
	int e,d;
	void read(){
		scanf("%d%d",&e,&d);
		e--;
	}
} memseq[Q*2];
int tmp[Q];
int belong[N];
int get(int x){
	if(belong[x]==x) return x;
	return belong[x]=get(belong[x]);
}
edge *ord[M];
bool cho[M];
int lab[N];

bool cmp(const edge* i,const edge* j){
	return *i->w<*j->w;
}
long long kruskal(int n,edge *E,int m){
	long long ret=0;
	for(int i=0;i<m;i++) ord[i]=E+i;
	sort(ord,ord+m,cmp);
	for(int i=0;i<n;i++) belong[i]=i;
	for(int i=0;i<m;i++){
		int x=get(ord[i]->u),y=get(ord[i]->v);
		if(cho[ord[i]-E]=x!=y)
			belong[x]=y,
			ret+=*ord[i]->w;
	}
	return ret;
}

void work(modi *seq,int q,int n,edge *E,int m){
	for(int i=0;i<m;i++) E[i].flag=0;
	if(q==1){
		*E[seq->e].w=seq->d;
		printf("%lld\n",ans+kruskal(n,E,m));
		return;
	}
	for(int i=0;i<q;i++){
		tmp[i]=*E[seq[i].e].w;
		*E[seq[i].e].w=-inf;
	}
	kruskal(n,E,m);
	for(int i=0;i<m;i++) if(cho[i]&&*E[i].w!=-inf)
		E[i].flag=1;
	for(int i=0;i<q;i++)
		*E[seq[i].e].w=inf;
	kruskal(n,E,m);
	for(int i=0;i<m;i++) if(!cho[i]&&*E[i].w!=inf)
		E[i].flag=2;
	for(int i=q-1;i>=0;i--)
		*E[seq[i].e].w=tmp[i];
	for(int i=0;i<n;i++) belong[i]=i;
	edge *tE=E+m;
	int mm=0;
	for(int i=0;i<m;i++){
		if(E[i].flag==0)
			tE[E[i].lab=mm++]=E[i];
		else
		if(E[i].flag==1)
			belong[get(E[i].u)]=get(E[i].v),
			ans+=*E[i].w;
	}
	int nn=0;
	for(int i=0;i<n;i++)
		if(get(i)==i)
			lab[i]=nn++;
	for(int i=0;i<mm;i++)
		tE[i].u=lab[get(tE[i].u)],
		tE[i].v=lab[get(tE[i].v)];
	int mid=q/2;
	int qq=0;
	modi *tseq=seq+q;
	for(int i=0;i<mid;i++){
		tseq[qq]=seq[i];
		tseq[qq].e=E[tseq[qq].e].lab;
		qq++;
	}
	work(tseq,qq,nn,tE,mm);
	qq=0;
	for(int i=mid;i<q;i++){
		tseq[qq]=seq[i];
		tseq[qq].e=E[tseq[qq].e].lab;
		qq++;
	}
	work(tseq,qq,nn,tE,mm);
	for(int i=0;i<m;i++)
		if(E[i].flag==1)
			ans-=*E[i].w;
}

int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=0;i<m;i++){
		memE[i].w=memw+i;
		memE[i].read();
	}
	for(int i=0;i<q;i++)
		memseq[i].read();
	work(memseq,q,n,memE,m);
}
