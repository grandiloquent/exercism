#include <stddef.h>
#include <stdio.h>
#define NUM_OF_ELEMENTS(a) (sizeof(a) / sizeof(a[0]))

unsigned int sum_of_multiples(const unsigned int *multiples,
                              const size_t number_of_multiples,
                              const unsigned int upper_bound)
{
    unsigned int sum = 0;
    if (NULL == multiples)
        return sum;

    for (unsigned int current = 1; current < upper_bound; current++)
    {
        for (size_t i = 0; i < number_of_multiples; i++)
        {
            if (0 != multiples[i] && (current % multiples[i]) == 0)
            {
                sum += current;
                break;
            }
        }
    }
    return sum;
}

int main(int argc, char const *argv[])
{

    const unsigned int multiples[] = {3, 5};

    unsigned int v = sum_of_multiples(multiples, NUM_OF_ELEMENTS(multiples),20);
    printf("%d", v);

    return 0;
}
// gcc sum-of-multiples.c & a