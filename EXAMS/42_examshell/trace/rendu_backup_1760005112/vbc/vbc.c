#include <ctype.h>

char *s;

void unexpected(char c)
{
    if(c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int ft_product()
{
    int a = ft_factor();
    int b;
    while(*s == '*')
    {
        s++;
        b = ft_factor();
        a = a * b;
    }
    return (a);
}

int fd_sum()
{
    int sum1 = ft_product();
    int sum2;
    while(*s == '+')
    {
        s++;
        sum2 = ft_product();
        sum1 = sum1 * sum2;
    }
    return(sum1);
}

int ft_factor()
{
    int n = 0;
    if (isdigit(*s))
        return (*s++ - '0');
    while(*s == '(')
    {
        s++;
        n = ft_sum();
        s++;
    }
    return (n);
}

int check_sum(char *str)
{
    int parenthese = 0;
    int i = 0;

    while(str[i])
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    if (check_sum(argv[1]))
        return(1);
    s = argv[1];
    int result = ft_sum();
    printf("%d\n", result);
}