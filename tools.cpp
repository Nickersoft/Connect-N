#include "tools.h"

using namespace std;

/*
 * Name: error(string)
 * Type: public method
 * Description: Writes a line to the error log
 * Parameters:
 * 	- s: String to write
 * Returns: None
 */
void Tools::error(string s) {
    ofstream ofs;
    ofs.open ("error.log", ios::app);
    ofs << time(NULL) << ": " << s << endl;
    ofs.close();
}

/*
 * Name: error(string, int)
 * Type: public method
 * Description: Writes a line formatted with an integer to the error log
 * Parameters:
 * 	- format: Format string
 *  - number: Integer used to format the string
 * Returns: None
 */
void Tools::error(string format, int number) {
    FILE * pFile;
    pFile = fopen ("error.log", "a+");
    fprintf(pFile, ("%d: " + format).c_str(), (int)time(NULL), number);
    fclose(pFile);
}

/*
 * Name: itos(int)
 * Type: public method
 * Description: Converts an integer to a string
 * Parameters:
 * 	- i: Integer to convert
 * Returns: The inputted integer as a string
 * Attribution: Adapted from code posted by user Bazzy found at
 * http://www.cplusplus.com/articles/D9j2Nwbp/
 */
string Tools::itos(int i) {
    ostringstream converter;
    converter << i;
    return converter.str();
}

/*
 * Name: log(string)
 * Type: public method
 * Description: Writes a line to the debug log
 * Parameters:
 * 	- s: String to write
 * Returns: None
 */
void Tools::log(string s) {
    ofstream ofs;
    ofs.open ("debug.log", ios::app);
    ofs << time(NULL) << ": " << s << endl;
    ofs.close();
}

/*
 * Name: log(string, int)
 * Type: public method
 * Description: Writes a line formatted with an integer to the debug log
 * Parameters:
 * 	- s: Format string
 *  - n: Integer used to format the string
 * Returns: None
 */
void Tools::log(string format, int number) {
    FILE * pFile;
    pFile = fopen ("debug.log", "a+");
    fprintf(pFile, ("%d: " + format).c_str(), (int)time(NULL), number);
    fclose(pFile);
}

/*
 * Name: println()
 * Type: public method
 * Description: Writes a newline to the console output
 * Parameters: None
 * Returns: None
 */
void Tools::println() {
    cout << endl;
}

/*
 * Name: println(string)
 * Type: public method
 * Description: Writes a line to console output
 * Parameters:
 * 	- s: String to output
 * Returns: None
 */
void Tools::println(string t) {
    cout << t << endl;
}

/*
 * Name: rand_from_range(int, int)
 * Type: public method
 * Description: Generates a random integer in a given range
 * Parameters:
 * 	- min: Minimum range value
 *  - max: Maximum range value
 * Returns: Integer
 */
int Tools::rand_from_range(int min, int max) {
    srand(time(NULL) ^ (getpid() << 16));
    return rand() % (max - min + 1) + min;
}

/*
 * Name: split(const string&, char)
 * Type: public method
 * Description: Splits a string using a delimeter
 * Parameters:
 * 	- s: The string to split
 *  - d: The delimeter to split by
 * Returns: An array of values resulting from the split
 * Attribution: Adapted from code posted by user pathouli found at
 * http://code.runnable.com/VHb0hWMZp-ws1gAr/splitting-a-string-into-a-vector-for-c
 */
vector<string> Tools::split(const string &str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}
