/*
��NOI 2011�����ú͵��� ������
�ڰ�Ⱦɫ�γɶ���ͼ���Ϸ������ߡ�
ÿ�����ߵ���������ɫ����һ���ġ�
�������ĳһ��һ�������ƥ���У���Ӹõ㿪ʼ���ֱ�ʤ��������ֱ�ʤ��
֤����
1. ��ʼ��һ�������ƥ����
	���ֲ�������ƥ����ߡ�
	1) �����ߵ�һ���Ƿ�ƥ��ߡ�
		��������ߵ���ƥ��ߣ����ʼ�㲻һ�������ƥ���С�
	2) ����ÿ��ֻҪ��ƥ����߼��ɡ�
		�������һ���㲻����ƥ����ߣ�������·����ż�����ߡ�
		��ô�����б߷�һ�¾͵õ���һ�����ƥ�䣬�ҳ�ʼ�㲻�ٸ����ƥ���У������ì�ܡ�
	����������һ�������ߡ������ֱ�ʤ��
2. ��ʼ�㲻һ�������ƥ����
	1) �����ߵ������е�һ�������ƥ���С�
		��Ϊ��ʼ�㲻һ�������ƥ���У����԰���ʼ��ȥ�����ͼ�����ƥ������ԭͼ��ͬ�� 
		��������ߵ�һ����һ����ȥ����ʼ����ͼ�����ƥ���еĵ㣬��ôȥ������������ͼ�����ƥ������ֻȥ����ʼ�������ƥ������ͬ��
		����ȥ������������ͼ��ԭͼ�����ƥ������ͬ��
		Ȼ������ԭͼ��������ȥ��������֮���ͼ�м���������������ıߣ�ʹ�����ƥ����+1��
		�ʲ���ì�ܣ����費������ԭ�����֤��
	����������1�����ֱ�ʤ�������ֱذܡ� 
	
	ö����ʼ�㣬���԰���ʼ����������������㷨������ʼ��Ķ�Ӧ��������·��
	�ĳ���һ�ξ͹��ˡ�
	дdinic+tarjan���졣 
*/
#include <cstdio>
const int N=105;
int n,m,sx,sy,tim;
char map[N][N];
struct node;
struct edge{
	node *ed;
	edge *next;
} E[N*N*4],*newE=E;
struct node{
	node *mat;
	edge *son;
	int type;
	int vis;
	bool ban;
	bool extend(){
		if(!this) return true;
		if(ban) return false;
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v->ban||v->vis==tim) continue;
			v->vis=tim;
			if(v->mat->extend()){
				v->mat=this;
				mat=v;
				return true;
			}
		}
		return false;
	}
} V[N][N];
void addedge(node *u,node *v){
	*newE=(edge){v,u->son},u->son=newE++;
	*newE=(edge){u,v->son},v->son=newE++;
}
void hungary(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(V[i][j].type==1&&!V[i][j].mat){
			tim++;
			V[i][j].extend();
		}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",map[i]+1);
		for(int j=1;j<=m;j++)
			if(map[i][j]=='.'){
				V[i][j].type=i+j&1?-1:1;
				if(V[i-1][j].type)
					addedge(&V[i][j],&V[i-1][j]);
				if(V[i][j-1].type)
					addedge(&V[i][j],&V[i][j-1]);
			}
	}
	hungary();
	bool found=false;
	for(sx=1;sx<=n;sx++)
		for(sy=1;sy<=m;sy++) if(V[sx][sy].type){
			V[sx][sy].ban=true;
			tim++;
			if(V[sx][sy].mat->extend()){
				V[sx][sy].mat=NULL;
				if(!found) found=true,puts("WIN");
				printf("%d %d\n",sx,sy);
			}
			V[sx][sy].ban=false;
		}
	if(!found) puts("LOSE");
}
