#include<stdio.h>	

struct Fraction
	{
		int up;
		int down;
	}f1,f2;

main()
{
	double x=0,y=0;
	printf("please input two number\n");
	scanf("%d/%d%d/%d",&f1.up,&f1.down,&f2.up,&f2.down);
	x=(double)f1.up/f1.down;
	y=(double)f2.up/f2.down;
	if(x>y)
	printf("%d/%d>%d/%d\n",f1.up,f1.down,f2.up,f2.down);
	if(x<y)
	printf("%d/%d<%d/%d\n",f1.up,f1.down,f2.up,f2.down);
	if(x==y)
	printf("%d/%d=%d/%d\n",f1.up,f1.down,f2.up,f2.down);
	system("pause");
}

