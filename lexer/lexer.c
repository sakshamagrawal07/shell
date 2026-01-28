#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **tokenize(char *input)
{
    int cap = 16;
    char **tokens = malloc(sizeof(char *) * cap);
    int t = 0;

    int i = 0;
    int n = strlen(input);

    while (i < n)
    {
        // skip whitespace outside tokens
        while (i < n && isspace(input[i]))
            i++;
        if (i >= n)
            break;

        int bufcap = 64;
        char *buf = malloc(bufcap);
        int b = 0;

        int inSingle = 0;
        int inDouble = 0;

        while (i < n && (!isspace(input[i]) || inSingle || inDouble))
        {
            // BACKSLASH ESCAPE (works outside single quotes)
            if (input[i] == '\\' && !inSingle)
            {
                i++;

                if (i < n)
                {
                    // inside double quotes, preserve \ before '
                    if (inDouble && input[i] == '\'')
                    {
                        if (b + 2 >= bufcap)
                        {
                            bufcap *= 2;
                            buf = realloc(buf, bufcap);
                        }
                        buf[b++] = '\\';
                        buf[b++] = input[i++];
                    }
                    else
                    {
                        if (b + 1 >= bufcap)
                        {
                            bufcap *= 2;
                            buf = realloc(buf, bufcap);
                        }
                        buf[b++] = input[i++];
                    }
                }
                continue;
            }

            // SINGLE QUOTES (toggle only outside double quotes)
            if (input[i] == '\'' && !inDouble)
            {
                inSingle = !inSingle;
                i++;
                continue;
            }

            // DOUBLE QUOTES (toggle only outside single quotes)
            if (input[i] == '"' && !inSingle)
            {
                inDouble = !inDouble;
                i++;
                continue;
            }

            // NORMAL CHARACTER
            if (b + 1 >= bufcap)
            {
                bufcap *= 2;
                buf = realloc(buf, bufcap);
            }
            buf[b++] = input[i++];
        }

        buf[b] = '\0';

        // store token
        if (t + 1 >= cap)
        {
            cap *= 2;
            tokens = realloc(tokens, sizeof(char *) * cap);
        }
        tokens[t++] = buf;
    }

    tokens[t] = NULL;
    return tokens;
}
