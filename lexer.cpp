/* current working file, in which I am creating a simple math lexer. Will be integrated into main.cpp at some point */

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

typedef struct {
    size_t type; // assigned by the enum LTYPES, stuff like PLUS_SYMBOL, PI, NUMBER
    string value; // internally everything will be held as string since it's easier to work with and debug
} key;

using key_string = vector<key>;

enum {
    UNKNOWN_CHARACTER = 0,

    /* first layer keys */
    // first layer keys are scanned direct from the string without any interpretation done to them

    NUMBER,                 // 2, 15, 6.9
    VARIABLE,               // for now will be 'x' only, later will implement as any character that is not already defined

    // predefined values

    PI,                     // "pi"
    EULER,                  //! "e" NOTE: 'e' will be interpreted as EULER always, never as VARIABLE 

    // operators
    PLUS,                   // '+'
    MINUS,                  //! ' - ' must be separated with spaces, otherwise will be interpreted as NEGATIVE
    MULTIPLY,               // '*'
    DIVIDE,                 // '/'

    POWER,                  // '^'
    FACTORIAL,              // '!'

    // common functions 

    SQUAREROOT,             // "sqrt"
    ROOT,                   // "root2," "root5," "rootx" == square root, 5th root, xth root (roots can also be achieved with fractional powers)
    ABSOLUTE,               // '|'

    // trig functions

    SIN, COS, TAN,

    CSC, SEC, COT,

    ARCSIN, ARCCOS, ARCTAN,

    ARCCSC, ARCSEC, ARCCOT,

    // control characters

    OPEN,                   // '('
    CLOSE,                  // ')'
    LOCATOR,                // '@' used to find derivate at a certain x-value of type NUMBER, should only be placed at the end of the expression
    SPACE,                  // ' '


    /* second layer keys */
    // after parsing the first layer of keys, the lexer wil go back through and re-interpret all the keys to add some context and meaning

    NEGATIVE,               // '-' if placed in front of a NUMBER or OPEN without SPACE in between them

    ABS_OPEN,               // given to the first '|' found
    ABS_CLOSED,             // given to the next '|' found
    //! NOTE: nesting of absolute value expressions is not possible!

    EXPONENT,               // given to a NUMBER that follows a POWER

} LTYPES;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class DasUberLexer {
    public:

    public:

        DasUberLexer() {

        }

    public:
        // given a string of text (mathematical expression, ie. "(4x^3)/(e^x)"), returns a list in order of lex_t items describing that expression
        // "(4x^3)/(e^x)" ==> { OPEN, "(" }, { NUMBER, "4" }, { VARIABLE, "x" }, { CARET, "^" }, etc.
        // some values do not technically need a lex_t.value, like CARET or OPEN, but in the interest of simplicity and clarity they will be included 
        key_string lex(string input_string) {
            key_string first_scan = basicScan(input_string);

            // key_string second_scan = contextScan(first_scan);

            return first_scan;
        }

        key_string basicScan(string input_string);

        key_string contextScan(key_string input_vector);
};

bool is_numerical(char c, bool include_decimal_point = false) {
    switch(c) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            return true;
        case '.':
            if(include_decimal_point) return true;
            return false;
        default:
            return false;
    }
}

key_string DasUberLexer::basicScan(string input_string) {
    /* scans first for single-letter keys while remembering where potential multi-character keys may exist (NUMBER, trig, roots, any character) */

    vector<int> multi_char_key_locations = {};

    key_string output = { };

    for (int i = 0; i < input_string.length(); i++) {
        char c = input_string.at(i);

        if(isalnum(static_cast<unsigned char>(c))) {
            multi_char_key_locations.push_back(i);
            continue; // this character will be interpreted by a second loop
        }

        key k = { UNKNOWN_CHARACTER, "~" };
        switch(c) {
            case '+':
                k = { PLUS, "+" };
                break;
            case '-':
                k = { MINUS, "-" };
                break;
            case '*':
                k = { MULTIPLY, "*" };
                break;
            case '/':
                k = { DIVIDE, "/" };
                break;
            
            case '^':
                k = { POWER, "^" };
                break;
            case '!':
                k = { FACTORIAL, "!" };
                break;

            case '|':
                k = { ABSOLUTE, "|"};
                break;

            case '(':
                k = { OPEN, "(" };
                break;
            case ')':
                k = { CLOSE, ")" };
                break;
            case '@':
                k = { LOCATOR, "@" };
                break;
            case ' ':
                k = { SPACE, " " };
                break;
            default:
                break;
        }

        output.push_back(k);

    }
    
    input_string += ' '; // buffer char for second loop

    for (int i = 0; i < input_string.length(); i++) {

        char c = input_string.at(i);

        if(!isalnum(static_cast<unsigned char>(c))) {
            continue; // these characters have already been interpreted
        }

        if(is_numerical(c)) {
            // a number is detected, and the programm will loop until it finds a non-numerical character
            // include decimal is set to false here because you shouldn't start numbers with a raw decimal point

            string number = to_string(c);

            
            while(is_numerical(input_string.at(i+1), true)) {
                number += to_string(input_string.at(i+1));
            }

            cout << number;
        }

    }
    return output;
}

key_string DasUberLexer::contextScan(key_string input_vector) {
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

string key_type_to_string(key k) {
    size_t type = k.type;

    switch(type) {
        case NUMBER: return "NUMBER";
        case VARIABLE: return "VARIABLE";
        case PI: return "PI";
        case EULER: return "EULER";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case POWER: return "POWER";
        case FACTORIAL: return "FACTORIAL";
        case SQUAREROOT: return "SQUAREROOT";
        case ROOT: return "ROOT";
        case ABSOLUTE: return "ABSOLUTE";
        case SIN: return "SIN";
        case COS: return "COS";
        case TAN: return "TAN";
        case CSC: return "CSC";
        case SEC: return "SEC";
        case COT: return "COT";
        case ARCSIN: return "ARCSIN";
        case ARCCOS: return "ARCCOS";   
        case ARCTAN: return "ARCTAN";
        case ARCCSC: return "ARCCSC";
        case ARCSEC: return "ARCSEC";
        case ARCCOT: return "ARCCOT";
        case OPEN: return "OPEN";
        case CLOSE: return "CLOSE";
        case LOCATOR: return "LOCATOR";
        case SPACE: return "SPACE";
        case NEGATIVE: return "NEGATIVE";
        case ABS_OPEN: return "ABS_OPEN";
        case ABS_CLOSED: return "ABS_CLOSED";
        case EXPONENT: return "EXPONENT";
        
        default: return "UNKNOWN CHARACTER";
        
    }

}

void print_key_string(key_string keystring) {
    for(key k : keystring) {
        cout << "[" << key_type_to_string(k) << ", " << k.value << "], ";
    }
}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int main(void) {
    DasUberLexer lexer = DasUberLexer();

    key_string lexed = lexer.lex("(|-243| + (9*4))");

    cout << "-----------------------------------------------------------------------------------\n";
    //print_key_string(lexed);
    cout << "-----------------------------------------------------------------------------------\n";

    return 0;
}