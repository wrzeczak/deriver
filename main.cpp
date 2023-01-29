/* copy of the original main file in which I started to implement a lexer before realizing that I should really figure it out on its own beforehand */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct {
    size_t type; // ie. "NUMBER," "MULTIPLICATION SYMBOL," "PI," etc.
    string value; // ie. "0943," "*," "pi"
} lex_t;

enum {
    UNKNOWN_CHARACTER = 0,
    VARIABLE,   // x
    NUMBER,     // 0-9
    NEGATIVE,   // - in front of a '(' or a NUMBER
    CARET,      // ^
    PI,         // "pi"
    E,          // "e"
    SIN,        // "sin"
    COS,        // "cos"
    TAN,        // "tan"
    CSC,        // "csc"
    SEC,        // "sec"
    TAN,        // "tan"
    PLUS,       // +
    MINUS,      // -
    MULTIPLY,   // *
    DIVIDE,     // /
    SQRT,       // "sqrt"
    OPEN,       // (
    CLOSE       // )
} TOKEN;

class TheWorkersHaveNothingToLoseButTheirLexer {
    public:
        TheWorkersHaveNothingToLoseButTheirLexer() {

        }

    public:
        std::vector<lex_t> lex(string input_string) {
            for(int i = 0; i < input_string.length(); i++) {
                char c = input_string.at(i);

                if (c == 'x') {

                }
            }
        }
};

class HyperMetaUltraLydianDerivator {
    public:
        string given_equation = "";

    public:
        HyperMetaUltraLydianDerivator() {
            
        }

    private:
        // used with std::remove_if, determines if 
        bool isNumericCharacter(char input_character) {
            char c = input_character;

            switch(c) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    return true;
                    break;
                case '-':
                    return true;
                    break;
                default:
                    return false;
            }
        }

        // remove all characters that are not 0-9 or '-'
        string stripStringToNumericCharacters(string input_string) {
            string s = input_string;
            s.erase(std::remove_if(s.begin(), s.end(), isNumericCharacter), s.end());

            return s;
        }

        bool testForPowerRule(string input_string) {
            if ( input_string.find("^") != string::npos ) {
                return true;
            }
            return false;
        }

        // NOTE: assumes power rule is applicable to the function, should be checked with testForPowerRule()
        // TODO: implement x^0, x^1, negative exponents, multi-digit powers, fractional powers
        string applyPowerRule(string input_string) {
            string output = "ERROR DURING DERIVATION!";
            size_t position_of_caret = input_string.find("^");
            
            string everything_after_the_caret = input_string.substr(position_of_caret, input_string.length());
            string power_string = stripStringToNumericCharacters(everything_after_the_caret);

            

            //! subtracting 48 does not work for negative powers, find better solution!
            int power = stoi(power_string); // ??? have no idea why I need to subtract 48 here, maybe capital character offset?
            int leading_coefficient = power;
            int new_power = power - 1;

            if(new_power < 1)
                output = to_string(leading_coefficient);
            else if(new_power < 2)
                output = to_string(leading_coefficient) + "x";
            else
                output = to_string(leading_coefficient) + "x^" + to_string(new_power); 

            return everything_after_the_caret; 
            // power rule :: f(x) = x^b then f'(x) = bx^b-1
            
        }

    public:
        string derive(string input_string) {
            this->given_equation = input_string;
            string output = "";

            if (testForPowerRule(this->given_equation)) {
                output = applyPowerRule(this->given_equation);
            }

            return output;
        }
};

int main(void) {
    cout << "--- KUBA CPP DERIVATOR v1 ---\n" << "\n";
    cout << "?: ";

    string input_string;

    cin >> input_string;

    cout << "EQUATION GIVEN: \"" << input_string << "\"\n";
    
    HyperMetaUltraLydianDerivator machine = HyperMetaUltraLydianDerivator();

    string derivation_output = machine.derive(input_string);

    cout << "DERIVATIVE OF GIVEN FUNCTION: \"" << derivation_output << "\"\n";

    return 0;
}