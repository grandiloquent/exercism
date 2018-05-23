#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "stdio.h"

#define MAX_WORDS 20
#define MAX_WORD_LENGTH 50

#define EXCESSIVE_LENGTH_WORD -1
#define EXCESSIVE_NUMBER_OF_WORDS -2

typedef struct word_count_word
{
    char text[MAX_WORD_LENGTH];
    int count;
} word_count_word_t;

static int word_match(char *testWord, int current_word_count, word_count_word_t words[MAX_WORDS])
{
    int match_index = -1;
    for (int index = 0; index < current_word_count; index++)
    {
        if (!strcmp(testWord, words[index].text))
        {
            match_index = index;
            break;
        }
    }
    return match_index;
}
int word_count(const char *input_text, word_count_word_t *words)
{
    int index;
    int unique_words = 0;
    char *test_word;
    char *lower_case_input_text;
    const char *delimiters = " ,.-\n:!!&@$%^&\"";

    lower_case_input_text = malloc(strlen(input_text) + 1);

    for (index = 0; input_text[index] != 0; index++)
    {
        lower_case_input_text[index] = tolower(input_text[index]);
    }

    lower_case_input_text[index] = '\0';

    memset(words, 0, sizeof(word_count_word_t) * MAX_WORDS);
    test_word = strtok(lower_case_input_text, delimiters);

    while (test_word != NULL)
    {
        if (('\'' == test_word[0]) && ('\'' == test_word[strlen(test_word) - 1]))
        {
            test_word[strlen(test_word) - 1] == '\0';
            test_word++;
        }

        index = word_match(test_word, unique_words, words);

        if (-1 == index)
        {
            if (MAX_WORD_LENGTH < strlen(test_word))
            {
                unique_words = EXCESSIVE_LENGTH_WORD;
                break;
            }
            if (MAX_WORDS == unique_words)
            {
                unique_words = EXCESSIVE_NUMBER_OF_WORDS;
                break;
            }
            words[unique_words].count = 1;
            strncpy(words[unique_words].text, test_word, MAX_WORD_LENGTH);
            unique_words++;
        }
        else
        {
            //printf("%s \n", words[index].text);
            words[index].count++;
        }
        test_word = strtok(NULL, delimiters);
    }
    free(lower_case_input_text);
    return unique_words;
}
int main(int argc, char const *argv[])
{
    word_count_word_t actual_solution[MAX_WORDS];
    int actual_word_count;

    char *input_text = "one of each one of each";
    actual_word_count = word_count(input_text, actual_solution);

    word_count_word_t *a = actual_solution;

    for (size_t i = 0; i < MAX_WORDS; i++, a++)
    {

        if (a->text[0] != '\0')
            printf("%s,%d \n", a->text, a->count);
        /* code */
    }

    /* code */
    return 0;
}

// gcc word_count.c & a