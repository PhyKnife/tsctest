#include <stdio.h>
#include <string>

std::string keyword[] = {"var"};
std::string operators[] = { "=", "+" };
std::string r = "var a = 100\n var b = a + 200";
//std::string r = "var a = 100";
std::string token;

int id = 4;
int digit = 5;

int syn;
int i;


bool isLetter(char c)
{
    return std::isalpha(c) || c == '_';
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
void scanner()
{
    token = "";
    syn = 0;
    if (isLetter(r[i])) 
    {
        syn = id;
        while (isLetter(r[i]) || isDigit(r[i]))
        {
            token += r[i];
            i++;
        }
        for (size_t i = 0; i < 1; i++)
        {
            /* code */
            if (keyword[i] == token)
            {
                /* code */
                syn = i + 1;
            }
            
        }
        
    } else if (isDigit(r[i]))
    {
        /* code */
        syn = digit;
        while (isDigit(r[i]))
        {
            token += r[i];
            i++;
        }
    }
    else if (i == r.length())
    {
        /* code */
        syn = 0;
    }
     
    else
    {
        switch (r[i])
        {
        case '\t':
        case '\n':
        case ' ':
            syn = -2;
            i++;
            break;

        case '=':
            syn = 2;
            token = "=";
            i++;
            break;
        case '+':
            syn = 3;
            token = "+";
            i++;
            break;

        default:
            syn = -1;
            token = r[i];
            i++;
            printf("Error %s", token);
            break;
        }

    }
    
}

void parse(){
    scanner();
    while (syn != 0 && syn != -1)
    {
        /* code */
        switch (syn)
        {
        case -2:
            scanner();
            break;
        
        default:
            printf("(%s:\t%d)", token.c_str(), syn);
            scanner();

            break;
        }
    }
    
}

int main(int argc, char const *argv[])
{
    parse();
   
    return 0;
}