#include <stdio.h>
int main(){
    int a[10][10];
    int i,j;
    for(i=0;i<10;i++){
        a[i][0]=1;
        a[i][i]=1;
    }
    for(i=2;i<10;i++){    //直接从第三行开始，因为第二行全是1
        for(j=1;j<i;j++)
            a[i][j]=a[i-1][j]+a[i-1][j-1];
    }
    for(i=0;i<10;i++){
        for(j=0;j<(10-i-1);++j)
            printf("    ");    //每行前需要空的数的位置，每个数占4个空格
        for(j=0;j<=i;j++)
            printf("%4d    ",a[i][j]);
        printf("\n");
    }
    return 0;
}