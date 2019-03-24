#include<stdio.h>
int main() {
	int i,j,t;
	int a[3];
	for(i=0; i<3; i++) {
		scanf("%d",&a[i]);
	}
	for(i=0; i<3; i++) {
		for(j=i+1; j<3; j++) {
			if(a[j]>a[i]) {
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	for(i=0; i<3; i++) {
		printf("%d ",a[i]);
	}
}
