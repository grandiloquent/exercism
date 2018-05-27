#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    double a;
    double b;
    double c;
} triangle_t;

bool triangle_equality(triangle_t input)
{
    return (input.a < (input.b + input.c) && input.b < (input.a + input.c) && input.c < (input.a + input.b));
}

bool is_equilateral(triangle_t input)
{
    return (triangle_equality(input) && (input.a == input.b) && (input.b == input.c));
}

bool is_isosceles(triangle_t input)
{
    return (triangle_equality(input) && ((input.a == input.b) || (input.b == input.c) || (input.a == input.c)));
}
bool is_scalene(triangle_t input)
{
    return (!(is_equilateral(input)) && !(is_isosceles(input)) && triangle_equality(input));
}

int main(int argc, char const *argv[])
{
    triangle_t a={3,3,5};
    printf("%d-%d-%d",triangle_equality(a),is_isosceles(a),is_scalene(a));
    return 0;
}
// gcc triangle.c & a