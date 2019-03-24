#include<stdio.h>
#define NAME_LEN 64
typedef struct student{
	char name[NAME_LEN];
	int height;
	float weight;
	long schols;
}Student;
 
void hiroko(Student *std)
{
	if (std ->height <180) std->height = 180;
	if (std ->weight > 80) std->weight =  80;
}
 
int main(void)
{
	Student sanaka = {"Sanaka", 175, 62.5, 3000};
	hiroko(&sanaka);
	
	printf("姓名 = %s\n", sanaka.name);
	printf("身高 = %d\n", sanaka.height);
	printf("体重 = %.1f\n", sanaka.weight);
	printf("奖学金 = %1d\n", sanaka.schols);
	
	return 0;
}
/*
--------------------- 
作者：real肇事者 
来源：CSDN 
原文：https://blog.csdn.net/weixin_39690617/article/details/79574817 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
