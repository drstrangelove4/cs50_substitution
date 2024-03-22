#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void decode_text(string key, string message);
bool validate_key(string key);

const int ALPHABET_LENGTH = 26;

// ----------------------------------------------------------------------------------------------------------------------

int main(int argc, string argv[])
{
    // Check for valid length
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Take the key from cli argument
    string key = argv[1];

    // Check if the key is valid
    bool valid_key = validate_key(key);
    if (!valid_key)
    {
        return 1;
    }

    // Get a message
    string message = get_string("plaintext: ");

    // Decode the message
    decode_text(key, message);
    return 0;
}

// ----------------------------------------------------------------------------------------------------------------------

bool validate_key(string key)
// Performs checks on a string to see if it is a valid key.
{
    char key_chars[ALPHABET_LENGTH];

    // Check if the length of the string is 26
    if (strlen(key) != ALPHABET_LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    // Check to see if each character in the key is alphabetical and unique
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        char current_char = key[i];

        // Check for non alphabetical characters
        if (!isalpha(tolower(current_char)))
        {
            return false;
        }
        else
        {
            // Check for repeat characters
            for (int j = 0; j < ALPHABET_LENGTH; j++)
            {
                // Convert to lower to make sure we have 26 unique characters no matter the case in
                // the cipher text
                if (tolower(key_chars[j]) == tolower(current_char))
                {
                    return false;
                }
            }
            // Add the current character to the array
            key_chars[i] = current_char;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------------------------------------------------

void decode_text(string key, string message)
// Takes a valid key and a message and encodes that message against the key.
{

    const int MESSAGE_LENGTH = strlen(message);
    const int ASCII_ADD = 65;

    // Create an A - Z array
    char alphabet_key[ALPHABET_LENGTH];
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        alphabet_key[i] = (char)(i + ASCII_ADD);
    }

    // Stores encoded characters
    char encoded_characters[MESSAGE_LENGTH];

    // Alphabetical chars into index values. Store non alphabetical chars.
    for (int i = 0; i < MESSAGE_LENGTH; i++)
    {
        char current_chracter = message[i];

        // Check if the character is alphabetic, if not store it in encoded characters.
        if (!isalpha(current_chracter))
        {
            encoded_characters[i] = current_chracter;
        }
        else
        {
            bool is_upper = false;
            // Check if the character is upper or lower case
            if (current_chracter >= 'A' && current_chracter <= 'Z')
            {
                is_upper = true;
            }

            for (int j = 0; j < ALPHABET_LENGTH; j++)
            {
                // Get the index of the character against the A -Z array.
                if (tolower(current_chracter) == tolower(alphabet_key[j]))
                {
                    // Encode the character using the character found at the same pos in the cipher.
                    char encoded_char = key[j];

                    // Check the case
                    if (!is_upper)
                    {
                        encoded_characters[i] = tolower(encoded_char);
                    }
                    else
                    {
                        encoded_characters[i] = toupper(encoded_char);
                    }
                }
            }
        }
    }

    // Print the results using a loop. There are errors using printf("%s", encoded_characters) on
    // CS50' machines.
    printf("ciphertext: ");
    for (int i = 0; i < MESSAGE_LENGTH; i++)
    {
        printf("%c", encoded_characters[i]);
    }
    printf("\n");
}

// ----------------------------------------------------------------------------------------------------------------------
