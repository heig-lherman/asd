#include "evaluator.h"
#include <algorithm>
#include <cctype>

/**
 * Evaluates an operation using (v1 op v2).
 * @param op The opeartor to use.
 * @param v1 The first value.
 * @param v2 The second value.
 * @return The result of the operation.
 */
int evalArithmeticOperation(char op, int v1, int v2) {
    switch (op) {
        case '+':
            return v1 + v2;
        case '-':
            return v1 - v2;
        case '*':
            return v1 * v2;
        case '/':
            return v1 / v2;
        case '%':
            return v1 % v2;
        default:
            throw bad_expression(); // NOLINT(hicpp-exception-baseclass)
    }
}


/**
 * Evaluates the given simple arithmetic expression recursively.
 * @param expression The expression to parse and evaluate.
 * @return The result of the evaluation.
 */
int evalue(const std::string &expression) {
    static const std::string VALID_OPERATORS = "+-*/%";

    // Check if the expression is empty.
    if (expression.empty()) {
        throw bad_expression(); // NOLINT(hicpp-exception-baseclass)
    }

    // erase spaces from the expression
    std::string token = expression;
    token.erase(
            std::remove_if(token.begin(), token.end(), ::isspace),
            token.end()
    );

    // If only digits are left, return the number.
    if (std::all_of(token.begin(), token.end(), ::isdigit)) {
        return std::stoi(token);
    }

    // Start from a left parenthesis, find the right parenthesis and evaluate
    // the expression between them, finding the operator and the operands.
    size_t opIndex = 0;
    size_t nbParenthesis = 0;
    for (auto it = token.begin(); it != token.end(); ++it) {
        if (*it == '(') {
            ++nbParenthesis;
            continue;
        }

        if (*it == ')') {
            --nbParenthesis;
            continue;
        }

        // If we have a valid operator, and we skipped all inside parenthesis,
        // we found the operator for our current expression.
        if (VALID_OPERATORS.find(*it) != std::string::npos
            && nbParenthesis == 1) {
            opIndex = (std::size_t) std::distance(token.begin(), it);
            break;
        }
    }

    std::string left = token.substr(1, opIndex - 1);
    std::string right = token.substr(opIndex + 1, token.size() - opIndex - 2);

    // Evaluate the left and right expressions.
    int leftValue = evalue(left);
    int rightValue = evalue(right);

    // Evaluate the operation.
    return evalArithmeticOperation(token[opIndex], leftValue, rightValue);
}
