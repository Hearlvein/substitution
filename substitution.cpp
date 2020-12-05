#include <algorithm>
#include <iostream>
#include <cctype>
using namespace std;

int main()
{
	// Cipher key. Any character of type char
	string key = "BcdeFGHIjklmnopQRsTuVWXYza";
	char useDefaultKey;
	cout << "Use default key? (Default key shifts each letter to one place) (y/n): ";
	cin >> useDefaultKey;
	if (useDefaultKey == 'n')
    {   cout << "Enter custom cipher key: ";
        cin >> key;
    }

	// Lower key for simplicity
	for (char& c : key)
		c = tolower(c);

	// Check key validity. New scope to destroy temporary sortedKey.
	{
	    if (key.size() != 26)
        {
            cout << "Key must be 26-digits-long!" << endl;
            return 1;
        }

		string sortedKey = key;
		sort(sortedKey.begin(), sortedKey.end());   // Simplicity over performance
		if (sortedKey != "abcdefghijklmnopqrstuvwxyz")
		{
			cout << "Key must be alphabetic!";
			return 1;
		}
	}

	// Message to encrypt or decrypt
	string input;
	cout << "Enter message to encrypt/decrypt: ";
	cin.ignore();
	getline(cin, input);
	if (input.empty())
	{
		cout << "Message is null!" << endl;
		return 1;
	}

    // Encrypt
	string encryption;
	encryption.reserve(input.size());
	for (char originalCharacter : input)
    {
        char encryptedCharacter = originalCharacter;
        if (isalpha(originalCharacter))	// Translate alphabetic letters
        {
            bool lower = islower(originalCharacter);
            size_t alphabeticIndex = (lower) ? originalCharacter - 97 : originalCharacter - 65;
            encryptedCharacter = key[alphabeticIndex];
            if (!lower)
                encryptedCharacter = toupper(encryptedCharacter);
        }
        encryption.push_back(encryptedCharacter);
    }
    cout << "Encryption: " << encryption << endl;

    // Decrypt
    string decryption;
    decryption.reserve(input.size());
    for (char originalCharacter : input)
    {
        char decryptedCharacter = originalCharacter;
        if (isalpha(originalCharacter))	// Translate alphabetic letters
        {
            bool lower = islower(originalCharacter);
            char loweredCharacter = tolower(originalCharacter);
            size_t keyIndex = key.find_first_of(loweredCharacter);
            decryptedCharacter = keyIndex + 97;
            if (!lower)
                decryptedCharacter = toupper(decryptedCharacter);
        }
        decryption.push_back(decryptedCharacter);
    }
    cout << "Decryption: " << decryption << endl;

    system("pause");
	return 0;
}
