/*
���Ա���Ϊ����ջ�����ɸ�˫�˶��� 
̰�ģ�
1. ����ջ�׵�2��Ԫ�أ����ջ�������Ԫ�ش���ջ��Ԫ�أ���ô˭ȡ������Ǹ�Ԫ��˭�Կ������Դ�Ҷ���Ը��ȡ������һ���ǵ���󲻵ò�ȡ��ȡ�ġ��������ܹ�Ԫ�ظ�������ż���ۼƽ��𰸡�
2. ����ջ������е�����3��Ԫ��a[i-1],a[i],a[i+1],���a[i-1]<=a[i]>=a[i+1]����ô���԰�3��Ԫ��ɾȥ����֮��һ��a[i-1]+a[i+1]-a[i]����Ϊ���ܴ�ʲô����ȡ������������
3. ����ʣ���Ԫ�أ�ջһ�������ջ����ջ�׵ݼ�������һ����������ߵ��м�ݼ�������������Ԫ��һ������ȡ�������̰��ȡ���ļ��ɡ� 
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1000005;
int n,cnt,last[N],next[N];
bool bo[N];
long long sum,ans,a[N];
int ord[N];
void remove(int u){
	bo[u]=false;
	next[last[u]]=next[u];
	last[next[u]]=last[u];
}
void check(int i){
	while(bo[last[i]]&&bo[i]&&bo[next[i]]&&a[last[i]]<=a[i]&&a[i]>=a[next[i]]){
		a[i]=a[last[i]]+a[next[i]]-a[i];
		remove(last[i]);
		remove(next[i]);
		check(last[i]);
	}
}
bool cmp(const int i,const int j){
	return a[i]>a[j];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),cnt+=bo[i]=a[i],sum+=a[i];
	for(int i=1;i<=n;i++) last[i]=i-1,next[i]=i+1;
	next[0]=1;
	last[1]=0;
	next[n]=0;
	last[0]=n;
	for(int i=next[0];i;i=next[i])
		check(i);
	while(bo[next[0]]&&bo[next[next[0]]]&&a[next[0]]>=a[next[next[0]]]){
		ans+=cnt&1?a[next[0]]-a[next[next[0]]]:a[next[next[0]]]-a[next[0]];
		remove(next[0]);
		remove(next[0]);
	}
	while(bo[last[0]]&&bo[last[last[0]]]&&a[last[0]]>=a[last[last[0]]]){
		ans+=cnt&1?a[last[0]]-a[last[last[0]]]:a[last[last[0]]]-a[last[0]];
		remove(last[0]);
		remove(last[0]);
	}
	n=0;
	for(int i=next[0];i;i=next[i]) if(bo[i]) ord[n++]=i;
	sort(ord,ord+n,cmp);
	for(int i=0;i<n;i++) if(i&1) ans-=a[ord[i]]; else ans+=a[ord[i]];
	printf("%lld %lld\n",(sum+ans)/2,(sum-ans)/2);
}
