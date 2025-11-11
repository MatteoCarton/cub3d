#include "vbc.h"

char *s;

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int ft_product()
{
    int a = ft_factor();
    int b;

    while (*s == '*')
    {
        s++;
        b = ft_factor();
        a = a * b;
    }
    return (a);
}

int ft_sum()
{
    int sum1 = ft_product();
    int sum2;

    while (*s == '+')
    {
        s++;
        sum2 = ft_product();
        sum1 = sum1 + sum2;
    }
    return (sum1);
}

int ft_factor()
{
    int n = 0;
    if (isdigit(*s))
        return (*s++ - '0');
    while (*s == '(')
    {
        s++;
        n = ft_sum();
        s++;
    }
    return (n);
}

int check_input(char *str)
{
    int parenthese = 0;
    int last = 0;
    int i =0;

    while (str[i])
    {
        if (str[i] == '(')
            parenthese++;
        if (str[i] == ')')
            parenthese--;
        if (isdigit(str[i]) && isdigit(str[i+1]))
            return (unexpected(str[i+1]), 1);
        last = str[i];
        i++;
    }
    if (parenthese > 0)
        return(unexpected('('), 1);
    if (parenthese < 0)
        return(unexpected(')'), 1);
    if (str[i] == '*' || str[i] == '+')
        return (unexpected(0), 1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    if (check_input(argv[1]))
        return (1);
    s = argv[1];
    printf("%d\n", ft_sum());
}