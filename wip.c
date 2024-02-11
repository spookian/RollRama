#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

const char test_case[] = 
"v 0.005000 0.005000 -0.005000\nv 0.005000 -0.005000 -0.005000\nv 0.005000 0.005000 0.005000\nv 0.005000 -0.005000 0.005000\nv -0.005000 0.005000 -0.005000\nv -0.005000 -0.005000 -0.005000\nv -0.005000 0.005000 0.005000\nv -0.005000 -0.005000 0.005000";

const char* objectloader_skip_to_eol(const char *string)
{
    char p = 'a';
    int idx = 0;
    while (p != '\n')
    {
        p = string[idx];
        if (p == '\0') break;
        idx++;
    }
    return &(string[idx]);
}

const char* objectloader_skip_to_space(const char *string)
{
    char p = 'a';
    int idx = 0;
    while (p != ' ')
    {
        p = string[idx];
        if (p == '\0') break;
        idx++;
    }
    return &(string[idx]);
}

// only use on strings you know for certain are floats
float _strtof(const char *str)
{
    float result = 0.0f;
    int idx = 0;
    float deccount = 0.0f;
    bool decimal = false;
    char t = str[idx];

    while (t != ' ' && t != '\n' && t != '\0')
    {
        if (t != '.')
        {
            result += (float)(t - '0');
            result *= 10;
        }
        else
        {
            decimal = true;
        }
        
        idx++;
        if (decimal) deccount += 1.0f;
        t = str[idx];
    }
    
    result *= powf(0.1, deccount);
    return result;
}


int main()
{
    const char *new_case = objectloader_skip_to_eol(test_case);
    int end = (unsigned long)new_case - (unsigned long)test_case;
    char* print = (char*)calloc(end, 1);
    memcpy(print, test_case, end);
    
    printf("%s", print);
    printf("test: %f\n", _strtof("3.141598"));
    printf("%s", objectloader_skip_to_space(test_case));
    return 0;
}
