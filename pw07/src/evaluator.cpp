#include "evaluator.h"
#include <cctype>
#include <stack> // std::stack

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
 * Evaluates a simple arithmetic operation on two operands.
 * Uses Djikstra's Shunting-yard algorithm.
 * @param expression The expression to parse and evaluate.
 * @return The result of the expression
 */
int evalue(const std::string &expression) {
    static const std::string VALID_OPERATORS = "+-*/%";
    std::stack<int> operands;
    std::stack<char> operators;

    // Iterate over the expression, pushing operands and operators onto the
    // appropriate stacks. Compute the result along the way.
    for (auto posIt = expression.begin(); posIt != expression.end(); ++posIt) {
        if (*posIt == '(' || ::isblank(*posIt)) {
            continue;
        }

        if (VALID_OPERATORS.find(*posIt) != std::string::npos) {
            operators.push(*posIt);
            continue;
        }

        if (::isdigit(*posIt)) {
            int operand = 0;
            for (; posIt != expression.end() && ::isdigit(*posIt); ++posIt) {
                operand = operand * 10 + (*posIt - '0');
            }

            --posIt;
            operands.push(operand);
            continue;
        }

        if (*posIt == ')') {
            if (operands.size() < 2 || operators.empty()) {
                throw bad_expression(); // NOLINT(hicpp-exception-baseclass)
            }

            int v2 = operands.top();
            operands.pop();
            int v1 = operands.top();
            operands.pop();
            char op = operators.top();
            operators.pop();

            operands.push(evalArithmeticOperation(op, v1, v2));
            continue;
        }

        throw bad_expression(); // NOLINT(hicpp-exception-baseclass)
    }

    // Check if the expression was malformed, meaning there was an unclosed
    // parenthesis or an operator without a right operand.
    if (operands.size() != 1 || !operators.empty()) {
        throw bad_expression(); // NOLINT(hicpp-exception-baseclass)
    }

    return operands.top();
}
