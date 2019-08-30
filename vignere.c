#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(int c);
int cipherText(int plaintext, int key);

int main(int argc, string argv[])
{
    string plaintext = "";
    string ciphertext = "";
    string shiftWord = "";
    int shiftWordLength = 0;
    int key;
    // check at least one argument has been passed
    if (argc != 2) 
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    } 
    else 
    {
        // loop through each character in key to check if alpha only
        for (int i = 0, n = strlen(argv[1]); i < n; i++) 
        {
            // exit if non-alpha found
            if (!isalpha(argv[1][i])) 
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
            // success if all alpha
        }
        shiftWord = argv[1];
        shiftWordLength = strlen(shiftWord);
    }
    // get user plaintext value
    plaintext = get_string("plaintext: ");
    // loop through plain text and apply key
    for (int i = 0, n = strlen(plaintext), j = 0; i < n; i++)
    {
        if (isupper(plaintext[i]) || islower(plaintext[i]))
        {
            if (j > shiftWordLength - 1) 
            {
                key = (j % (shiftWordLength));
            }
            else 
            {
                key = j;
            }
            printf("%c", cipherText(plaintext[i], shift(shiftWord[key])));
            j++;
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}

// convert character to shift value
int shift(int c)
{
    // subtract 97 from lower character to match alphabet index
    if (islower(c)) 
    {
        return c - 'a';
    } 
    // subtract 65 from upper character to match alphabet index
    else if (isupper(c)) 
    {
        return c - 'A';
    }
    // return -1 if an invalid value is passed
    else 
    {
        return -1;
    }
}

int cipherText(int plaintext, int key) 
{
    int c = plaintext + key;
    if ((islower(plaintext) && c > 'z') || (isupper(plaintext) && c > 'Z'))
    {
        c -= 26;
    }
    return c;
}
