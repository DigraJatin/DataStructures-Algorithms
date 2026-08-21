// https://share.google/aimode/4opGNL3skdOhplal7

#include <iostream>
#include <string>
#include <vector>
#include <stack>

// Helper structure to track expressions alongside their precedence and operators
struct Expression {
    std::string str;
    char op;            // Contains ' ' if it is a single atomic operand/variable
    int precedence;     // Precedence levels: 1 for (+, -), 2 for (*, /), 3 for atomic operands
};

// Helper function to check if a token is a valid arithmetic operator
bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

// Helper function to get the precedence level of a given operator character
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 3; // Atomic operands possess the highest precedence
}

/**
 * Question 1: Standard RPN to Infix Conversion
 * Takes a pre-tokenized vector of strings representing a single RPN expression.
 */
std::string rpnToInfixNaive(const std::vector<std::string>& tokens) {
    std::stack<std::string> st;

    // Loop directly through the pre-split tokens vector instead of using stringstream
    for (const std::string& token : tokens) {
        if (!isOperator(token)) {
            // Push atomic operands directly to the stack
            st.push(token);
        } else {
            // RPN evaluation order: first pop is the right child, second is the left child
            if (st.size() < 2) return "Invalid RPN Expression";
            
            std::string right = st.top(); st.pop();
            std::string left = st.top(); st.pop();

            // Explicitly wrap every operation in parentheses
            std::string combined = "(" + left + " " + token + " " + right + ")";
            st.push(combined);
        }
    }

    if (st.size() != 1) return "Invalid RPN Expression";
    return st.top();
}

/**
 * Question 2 Follow-Up: RPN to Infix with Minimized Parentheses
 * Takes a pre-tokenized vector of strings representing a single RPN expression.
 */
std::string rpnToInfixMinimized(const std::vector<std::string>& tokens) {
    std::stack<Expression> st;

    // Loop directly through the pre-split tokens vector instead of using stringstream
    for (const std::string& token : tokens) {
        if (!isOperator(token)) {
            // Atoms have a placeholder operator ' ' and maximum precedence level 3
            st.push({token, ' ', 3});
        } else {
            if (st.size() < 2) return "Invalid RPN Expression";

            Expression right = st.top(); st.pop();
            Expression left = st.top(); st.pop();

            char currentOp = token[0];
            int currentPrec = getPrecedence(currentOp);

            // Rule for Left Child: Needs brackets only if its precedence is strictly lower 
            // than the parent operator. Due to left-associativity, equal precedence is safe.
            std::string leftStr = left.str;
            if (left.precedence < currentPrec) {
                leftStr = "(" + leftStr + ")";
            }

            // Rule for Right Child: Needs brackets if its precedence is strictly lower.
            // If its precedence is equal, it requires brackets if the parent operator 
            // is non-associative from the right side (such as subtraction '-' or division '/').
            std::string rightStr = right.str;
            if (right.precedence < currentPrec || 
               (right.precedence == currentPrec && (currentOp == '-' || currentOp == '/'))) {
                rightStr = "(" + rightStr + ")";
            }

            // Combine strings and push back tracking structural details
            std::string combinedStr = leftStr + " " + currentOp + " " + rightStr;
            st.push({combinedStr, currentOp, currentPrec});
        }
    }

    if (st.size() != 1) return "Invalid RPN Expression";
    return st.top().str;
}

int main() {
    // Input represented as a vector of vectors of strings (vector<vector<string>>)
    // Each inner vector represents a single tokenized RPN expression.
    std::vector<std::vector<std::string>> testCases = {
        {"3", "4", "5", "*", "+"},       // 3 + 4 * 5
        {"3", "4", "+", "5", "*"},       // (3 + 4) * 5
        {"3", "4", "5", "-", "-"},       // 3 - (4 - 5)
        {"3", "4", "-", "5", "-"},       // 3 - 4 - 5
        {"a", "b", "/", "c", "d", "/", "*"} // a / b * (c / d)
    };

    std::cout << "--- RPN to Infix Using vector<vector<string>> Input ---\n\n";
    for (const auto& rpnTokens : testCases) {
        // Print the tokenized input visually
        std::cout << "RPN Tokens: [ ";
        for (const auto& token : rpnTokens) {
            std::cout << token << " ";
        }
        std::cout << "]\n";

        // Pass the individual vector<string> to the functions
        std::cout << "Naive     : " << rpnToInfixNaive(rpnTokens) << "\n";
        std::cout << "Minimized : " << rpnToInfixMinimized(rpnTokens) << "\n";
        std::cout << "--------------------------------------------------\n";
    }

    return 0;
}