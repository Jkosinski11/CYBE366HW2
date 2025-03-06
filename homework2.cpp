#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

//Password hash stored as a global contant ULL appended to end for an Unisigned long int
const uint64_t PASSWORD  = 17938035065087455119ULL;
//Output file name stored as a global constant
const std::string OUTPUT_FILE = "output.txt";


/// @brief Caeser cypher encryption that takes in a string and an integer key size
/// @param text Text to be encrypted
/// @param key_size size of shift in the caeser cypher
/// @return the encrypted text
std::string cypher(const std::string& text, int key_size) {
    std::string result;
    // Loop through each character in the text
    for (char c : text) {
        // Check if the character is within the printable ASCII range
        if(c + key_size >= 32 && c + key_size <= 126) {
            // Add the key size to the character
            result += (c + key_size);
        } else {
            // If the character is not within the printable ASCII range, add the character as is
            result += c; 
        }
    }
    return result;
}

/// @brief Caeser cypher decryption that takes in a string and an integer key size
/// @param text Text to be decrypted
/// @param key_size size of shift in the caeser cypher
/// @return the decrypted text
std::string decypher(const std::string& text, int key_size) {
    std::string result;
    // Loop through each character in the text
    for (char c : text) {
        // Check if the character is within the printable ASCII range
        if(c - key_size >= 32 && c - key_size <= 126) {
            // Subtract the key size from the character
           result += (c - key_size); 
        } else {
            // If the character is not within the printable ASCII range, add the character as is
           result += c; 
        }
    }
    return result;
}


/// @brief Gets password from userhashes it and checks if matches the stored hash of password
/// @return true if password is correct, false otherwise
bool password(){
// Get password from user
std::string input;
std::cout << "Enter password: ";
std::getline(std::cin, input);
// Hash the password
std::hash<std::string> hasher;
size_t hash_value = hasher(input);

// Check if the hash value matches the stored hash value
if (hash_value != PASSWORD)
{
    // Return false if the hash value does not match the stored hash value
    return false;
}
// Return true if the hash value matches the stored hash value
return true;
}

int main() {
    //Start by getting a password from user and checking it
    bool pswd = password();
    //If password is invalid exit the program
    if(!pswd)
    {
        std::cerr << "Invalid password" << std::endl;
        return 1;
    }
    int key_size ;
    // Get input in string in case user inputs characters
    std::string key_input;
    // Loop until a valid key size is entered
    bool flag = true;
    while(flag){
        flag = false;
        //initialize key input and key size
        key_input = "";
        key_size = 0;
        std::cout << "Enter Key size: ";
        std::cin >> key_input;
        //Check if key is a number
        for ( char c : key_input)
        {
            if(!isdigit(c))
            {
                std::cerr << "Invalid key size" << std::endl;
                flag = true;
                break;
            }
        }
        // if the key is not a number continue loop
        if (flag)
        {
            continue;
        }
        // if key is a number convert it to an integer
        key_size = std::stoi(key_input);
        //Key must be between sizes 0 and 94
        if (key_size > -1 && key_size < 95)
        {
            //exit loop if valid key size is entered
            break;
        }
        else
        {
            //Continue loop if key is invalid
            std::cerr << "Invalid key size" << std::endl;
            flag = true;
        }
    }
    
    //Loop until valid input and valid output type are entered by user
    while(true)
    {
        //Get output type from user plain or cipher text
        std::string output_type;
        std:: cout << "Enter 'decrypt' for plaintext output or 'encrypt' for ciphertext output: ";
        std::cin >> output_type;
        //Get input type from user text or file
        std::string input_type;
        std::cout << "Enter 'text' to enter text or 'file' to enter filepath: ";
        std::cin >> input_type;

        std::string file_text;
        //If input type is text get the text from the user
        if(input_type == "text") {
            std::cout << "Enter text: ";
            //To ignore the newline character left in the buffer
            std::cin.ignore(); 
            //Get the text from the user
            std::getline(std::cin, file_text);
        } 
        // If input type is file get the filepath from the user
        else if(input_type == "file") {
            std::string file_name;
            std::cout << "Enter file name: ";
            std::cin >> file_name;
            //Open the file and read the text
            std::ifstream file(file_name);
            // Check if the file is open
            if(file.is_open()) {
                std::string line;
                // Read the file line by line
                while(std::getline(file, line)) {
                    // Append the line to the file text with a newline character to keep file organized
                    file_text += line + "\n";
                }
                file.close();
            } 
            // if file path is invalid or file is unable to be opened exit program
            else {
                std::cerr << "Unable to open file: " << file_name << std::endl;
                return 1;
            }
        } 
        // Repeat getting input if invalid input is entered
        else {
            std::cerr << "Invalid input type" << std::endl;
            continue;
        }
        //If output type is decrypt decrypt the text and write to output file
        if (output_type == "decrypt") {
            std::string decypher_text = decypher(file_text, key_size);
           // Open or create output.txt file
            std::ofstream output_file("output.txt");
            // write decyphered text to output file
            output_file << decypher_text;
            // close output file
            output_file.close();
            break;
        // If output type is encrypt encrypt the text and write to output file
        } else if (output_type == "encrypt")
        {
            std::string cypher_text = cypher(file_text, key_size);
            // Open or create output.txt file
            std::ofstream output_file("output.txt");
            // write cyphered text to output file
            output_file << cypher_text;
            // close output file
            output_file.close();
            break;
        }
        // Repeat getting input if invalid output type is entered
        else
        {
            std::cerr << "Invalid output type" << std::endl;
        }
    }
    return 0;
}