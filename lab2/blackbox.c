#include<stdio.h>
#include<string.h>

int main()
{
float x,y,d;

scanf("%f %f %f", &x, &y, &d);
printf(" %f \n %f \n %f", x,y,d);

float zd,z;

z=x*x+y*y;
zd=z+d*z;
printf("\n %f", zd);

return 0;
}
