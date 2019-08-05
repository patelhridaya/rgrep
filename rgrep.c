#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {

    if(strlen(pattern) && strlen(partial_line)==0)//Just a check to make sure partial line and line are not zero still
    {
        return 1;
    }
    if(strlen(pattern)==0)//check if pattern is not zero characters
    {
        return 1;
    }
    if (strlen(partial_line)==0)//if partial line is still not equal to a number>0, then return 0
    {
        return 0;
    }

//Case: \\. This needs to go first because if it shows up then that will disregard the meaning of the special character
    if(pattern[0]=='\\')
    {
//      if(pattern[2] == '+')

        if(pattern[2] == '?')
        {
            if(pattern[1]==partial_line[0])// check for similarity with pattern first, line second
            {
                return matches_leading(partial_line + 1, pattern + 2);//searching
            }
            else
            {
                return matches_leading(partial_line, pattern + 3);//if not jump pattern three to check again
            }
        }
        else if(pattern[1]==partial_line[0])//if char matches, call recursion to check again
        {
            return matches_leading(partial_line + 1, pattern + 2);
        }
        else
        {
            return 0;
        }
    }

//Wildcard Case: +
    if(pattern[1]=='+')
    {
        if(pattern[0] != partial_line[0] && pattern[0] != '.')//check if first characters match and if it is character at all
        {
            return 0;
        }
        else
        {
            int i = 0;      //incrementer used to keep track of how many characters are after the +
            int amount = 0;
            while(strlen(partial_line) >= i && (partial_line[i] == pattern[0] || pattern[0] == '.'))
            {
                i++;//increment till the entire length of line is scanned
                amount = matches_leading(partial_line + i, pattern + 2); //if pattern is 1 character long w/ '+' then check if it's found in the end of line
                if(amount)
                {
                    return 1;
                }
            }
            return (matches_leading(partial_line + i, pattern + 2));
        }
    }

//Case: ?
    if(pattern[1]== '?')
    {
        if(partial_line[0] == pattern[0])//check first char
        {
            return matches_leading(partial_line + 1, pattern + 2);  //it should skip the ? and compare with the next character
        }
        else
        {
            return matches_leading(partial_line, pattern + 2);  //otherwise skip 2 spots from pattern and compare with next
        }
    }

//Wildcard Case: .
    if(pattern[0] == '.')
    {
        return matches_leading(partial_line + 1, pattern + 1);//increment by one as we '.' matches with any char
    }

//The characters match so it will move on to the next part of the pattern and compare
    if (pattern[0]==partial_line[0])
    {
        return matches_leading(partial_line + 1, pattern + 1);//if the characters match then increment both by 1 to move to the next character
    }
    else
    {
        return 0;
    }
  // Implement if desire
}




/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
    if(strlen(pattern) == 0)//If pattern is not any characters, return 0
        {
            return 0;
        }

        //Checks for '/n' in line[int] here
        int c = 0;
        for(c = 0; c < strlen(line); c++)//if c iterator is less than length of line pattern, go to matches_leading
        {
            if(matches_leading(line + c, pattern))
            {
                return 1;
            }
        }
        // Implement me//
        return 0;
    }





int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}

