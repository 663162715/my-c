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
	
	printf("���� = %s\n", sanaka.name);
	printf("��� = %d\n", sanaka.height);
	printf("���� = %.1f\n", sanaka.weight);
	printf("��ѧ�� = %1d\n", sanaka.schols);
	
	return 0;
}
/*
--------------------- 
���ߣ�real������ 
��Դ��CSDN 
ԭ�ģ�https://blog.csdn.net/weixin_39690617/article/details/79574817 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
*/
