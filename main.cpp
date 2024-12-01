#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <cmath> // For pow()
#include <iomanip> // For setprecision
int main() {
    LinkedList list;
    std::string filename = "sample_exp.txt";

    std::ifstream inputFile(filename);  
    if (!inputFile.is_open()) {
        std::cout << "File failed to open " << std::endl;
        return 1; 
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Debug: print the entire line
        std::cout << "Processing line: " << line << std::endl;

        list = LinkedList(); // Reset the list for each polynomial

        // Parsing x value
        size_t xvalStart = line.find('(');
        size_t xvalEnd = line.find(')', xvalStart);
        if (xvalStart == std::string::npos || xvalEnd == std::string::npos) {
            std::cout << "Invalid line format: " << line << std::endl;
            continue;
        }

        std::string xvalStr = line.substr(xvalStart + 1, xvalEnd - xvalStart - 1);
        double xval;
        try {
            xval = std::stod(xvalStr);
        } catch (const std::invalid_argument& e) {
            std::cout << "Error parsing x value: " << xvalStr << std::endl;
            continue;
        }

        // Find the start of the polynomial expression
        size_t expStart = line.find('=', xvalEnd);
        if (expStart == std::string::npos) {
            std::cout << "No polynomial expression found" << std::endl;
            continue;
        }
        std::string polyExpression = line.substr(expStart + 1);

        // trailing whitespace
        polyExpression.erase(0, polyExpression.find_first_not_of(" "));
        polyExpression.erase(polyExpression.find_last_not_of(" ") + 1);

        // Debug: print polynomial expression
        std::cout << "Polynomial expression: " << polyExpression << std::endl;

        int sign = 1;
        size_t pos = 0;
        while (pos < polyExpression.length()) {
            // Skip leading spaces
            while (pos < polyExpression.length() && polyExpression[pos] == ' ') pos++;
            
            // Handle sign
            if (pos < polyExpression.length() && (polyExpression[pos] == '+' || polyExpression[pos] == '-')) {
                sign = (polyExpression[pos] == '+') ? 1 : -1;
                pos++;
                // Skip spaces after sign
                while (pos < polyExpression.length() && polyExpression[pos] == ' ') pos++;
            }

            // Parse coefficient and exponent
            double coef = 1.0;
            int exp = 0;

            // Check for coefficient
            size_t xPos = polyExpression.find('x', pos);
            if (xPos != std::string::npos && xPos > pos) {
                try {
                    coef = std::stod(polyExpression.substr(pos, xPos - pos));
                } catch (const std::invalid_argument& e) {
                    coef = 1.0;
                }
                pos = xPos;
            }

            // Handle x and exponent
            if (pos < polyExpression.length() && polyExpression[pos] == 'x') {
                pos++; // Move past 'x'
                
                // Check for exponent
                if (pos < polyExpression.length() && polyExpression[pos] == '^') {
                    pos++; // Move past '^'
                    size_t expEnd = polyExpression.find_first_not_of("0123456789", pos);
                    try {
                        exp = std::stoi(polyExpression.substr(pos, expEnd - pos));
                    } catch (const std::invalid_argument& e) {
                        exp = 1;
                    }
                    pos = (expEnd == std::string::npos) ? polyExpression.length() : expEnd;
                } else {
                    exp = 1;
                }
            } else {
                // Constant term
                try {
                    coef = std::stod(polyExpression.substr(pos));
                } catch (const std::invalid_argument& e) {
                    break; // Unable to parse further
                }
                exp = 0;
            }

            // Add the term to the list
            list += new Node(sign * coef, exp);

            // Move to next term
            pos = polyExpression.find_first_of("+-", pos);
            if (pos == std::string::npos) break;
        }

        list.sortList(); // Sort before output

        // Compute and display the result
        std::cout << "f(" << xval << ") =";
        Node* current = list.getHead();
        double result = 0.0;
        bool firstTerm = true;

        while (current) {
            double termValue = current->getCoef() * std::pow(xval, current->getExp());
            result += termValue;

            if (firstTerm) {
                if (current->getCoef() < 0) {
                    std::cout << " -";
                }
                firstTerm = false;
            } else {
                std::cout << (current->getCoef() < 0 ? " - " : " + ");
            }

            double absCoef = std::abs(current->getCoef());
            if (absCoef != 1 || current->getExp() == 0) {
                std::cout << absCoef;
            }
            if (current->getExp() > 0) {
                std::cout << "x";
                if (current->getExp() > 1) {
                    std::cout << "^" << current->getExp();
                }
            }
            current = current->getNext();
        }

        // Print result
        std::cout << " = " << std::fixed << std::setprecision(3) << result << std::endl;
    }

    inputFile.close();
    return 0;
}