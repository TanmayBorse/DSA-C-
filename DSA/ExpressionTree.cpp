#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <string>

class ExpressionTree {
public:
    // Function to convert infix expression to postfix notation
    std::string infixToPostfix(const std::string &infix) {
        std::stack<char> s;
        std::string postfix;
        for (char ch : infix) {
            if (std::isdigit(ch)) {
                postfix += ch; // Append numbers to postfix directly
            } else if (ch == '(') {
                s.push(ch);
            } else if (ch == ')') {
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop(); // Remove '(' from stack
            } else if (isOperator(ch)) {
                while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(ch);
            }
        }

        // Pop all the operators left in the stack
        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }

        return postfix;
    }

    // Function to construct the BST from a postfix expression
    void constructTree(const std::string &postfix) {
        std::stack<Node*> s;
        for (char ch : postfix) {
            if (std::isdigit(ch)) {
                s.push(new Node(std::string(1, ch)));
            } else if (isOperator(ch)) {
                Node* node = new Node(std::string(1, ch));
                node->right = s.top();
                s.pop();
                node->left = s.top();
                s.pop();
                s.push(node);
            }
        }
        root = s.top();
    }

    // Function to evaluate the constructed expression tree
    int evaluate() {
        return evaluate(root);
    }

private:
    struct Node {
        std::string value;
        Node* left;
        Node* right;
        Node(const std::string &val) : value(val), left(nullptr), right(nullptr) {}
    };
    
    Node* root = nullptr;

    // Helper function to evaluate the tree recursively
    int evaluate(Node* node) {
        if (!node) return 0;

        // If leaf node, it's a number
        if (!node->left && !node->right) {
            return std::stoi(node->value);
        }

        // Evaluate left and right subtrees
        int leftValue = evaluate(node->left);
        int rightValue = evaluate(node->right);

        // Apply the operator
        if (node->value == "+") {
            return leftValue + rightValue;
        } else if (node->value == "-") {
            return leftValue - rightValue;
        } else if (node->value == "*") {
            return leftValue * rightValue;
        } else if (node->value == "/") {
            return leftValue / rightValue;
        }

        return 0;
    }

    // Helper function to determine if a character is an operator
    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

    // Helper function to define precedence of operators
    int precedence(char ch) {
        if (ch == '+' || ch == '-') {
            return 1;
        } else if (ch == '*' || ch == '/') {
            return 2;
        }
        return -1;
    }
};

int main() {
    std::string infixExpression = "3+5*(2-8)";
    ExpressionTree tree;

    // Convert infix to postfix
    std::string postfixExpression = tree.infixToPostfix(infixExpression);
    std::cout << "Postfix Expression: " << postfixExpression << std::endl;

    // Construct tree from postfix expression
    tree.constructTree(postfixExpression);

    // Evaluate the expression tree
    int result = tree.evaluate();
    std::cout << "Evaluation Result: " << result << std::endl;

    return 0;
}
