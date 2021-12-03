#include <stdio.h>
#include <cstring>
#include <cstdlib>

const size_t MAX_BUFFER_SIZE = 128;



enum Type {
    error_ = 0,
    const_ = 1,
    var_ = 2,
    operator_ = 3
};


struct Node {
    double data;
    Type type;
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = NULL;
};

bool BeginExpr(const char *expression, int i) {
    return expression[i] == '(';
}

bool BeginConst(const char *expression, int i) {
    return expression[i] >= '0' && expression[i] <= '9';
}

bool IsDigit(const char *expression, int i) {
    return BeginConst(expression, i) || expression[i] == '.';
}

double ReadConst(const char *expression, int& i) {
    char buffer[MAX_BUFFER_SIZE] = {};
    int ind = 0;
    while (IsDigit(expression, i)) {
        buffer[ind] = expression[i];
        ++ind;
        ++i;
    }
    --i;
    buffer[ind] = '\0';
    double const_;
    sscanf(buffer, "%d", &const_);
    return const_;
}

bool EndExpr(const char *expression, int i) {
    return expression[i] == ')';
}

bool BeginVar(const char *expression, int i) {
    return false;
}

bool BeginOperator(const char *expression, int i) {
    char operators[] = "+-*/";
    int n_operators = strlen(operators);
    for (int j = 0; i < n_operators; ++j) {
        if (expression[i] == operators[j]) {
            return true;
        }
    }
    return false;
}

Node* ExpressionTreeConstructor(const char* expression) {
    Node* cur_node = NULL;
    Node* new_node = NULL;
    for (int i = 0; i < strlen(expression); ++i) {
        if (BeginExpr(expression, i)) {
            new_node = (Node*) calloc(1, sizeof(Node));
            new_node->parent = cur_node;
            if (cur_node->left) {
                cur_node->left = new_node;
            } else if (cur_node->right) {
                cur_node->right = new_node;
            }
            cur_node = new_node;
        } else if (BeginConst(expression, i)) {
            double data = ReadConst(expression, i);
            cur_node->data = data;
            cur_node->type = const_;
        } else if (EndExpr(expression, i)) {
            cur_node = cur_node->parent;
        } else if (BeginVar(expression, i)) {
            ;
        } else if (BeginOperator(expression, i)) {
            cur_node->data = (double)(int)expression[i];
            cur_node->type = operator_;
        }
    }
}


int main() {
    return 0;
}
