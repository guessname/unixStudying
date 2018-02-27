#define mul(a) (a)*(a)
int main(void)
{
    int a = 5, b, c;
    b = mul(a++);
    c = mul(++a);
    printf("%d %d\n", b, c);
    if(!a && c++)
        b++;
    else
        c++;
    printf("%d %d\n", b, c);
}