#include <stdio.h>
#include <math.h>
#include <assert.h>

double eps = 0.0001;

enum nRoots {
    zero,
    one,
    two,
    infinity
};


bool equal(double x, double y);
nRoots SolveLinear(double b, double c, double* x1);
nRoots SolveSquare (double a, double b, double c,
                 double* x1, double* x2);
void Test0Roots();
void Test1Roots();
void Test2Roots();
void TestInfRoots();




int main() {
    printf("# Square equation solver\n"
           "# (c) Andrew Borovets, 2021\n\n");
    printf("enter 0 - to solve the square equation\n"
           "      other - run test\n");
    char answer = '0';
    scanf("%c", &answer);
    if (answer == '0') {
        printf("# Enter a, b, c: ");
        double a = 0, b = 0, c = 0;
        scanf("%lg %lg %lg", &a, &b, &c);
        double x1 = 0, x2 = 0;
        int nRoots = SolveSquare(a, b, c, &x1, &x2);
        switch (nRoots) {
            case 0:
                printf("No roots\n");
                break;
            case 1:
                printf("x = %lg\n", x1);
                break;
            case 2:
                printf("x1 = %lg, x2 = %lg\n", x1, x2);
                break;
            case infinity:
                printf("Any number");
                break;
            default:
                printf("main(): ERROR: nRoots = %d\n",
                       nRoots);
                return 1;
        }
    } else /* run tests*/ {
        Test0Roots();
        Test1Roots();
        Test2Roots();
        TestInfRoots();
        printf("All tests are passed successfully!\n");
    }
}



bool equal(double x, double y) {
    return abs(x - y) < eps;
}



nRoots SolveLinear(double b, double c, double* x1) {
    if (equal(b, 0)) {
        return (equal(c, 0)) ? infinity : zero;
    }
//      if (b != 0)
    *x1 = -c / b;
    return one;
}



//------------------------------------------------
//! Solves a square equation ax2 + bx + c = 0
//!
//! \param [in]     a      a-coefficient
//! \param [in]     b      b-coefficient
//! \param [in]     c      c-coefficient
//! \param [out]    x1     Pointer to the 1st root
//! \param [out]    x2     Pointer to the 1st root
//! \return Number of roots
//!
//! \note   In case of infinite number of roots,
//!         return SS_INF_ROOTS.
//------------------------------------------------
nRoots SolveSquare (double a, double b, double c,
                 double* x1, double* x2) {

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);


    if (equal(a, 0)) {
        return SolveLinear(b, c, x1);
    }
//  if (a != 0)
    double d = b * b - 4 * a * c;
    if (equal(d, 0)) {
        *x1 = *x2 = -b / (2 * a);
        return one;
    } else if (d < 0) {
        return zero;
    }
//  if (d > 0)
    double sqrt_d = sqrt(d);

    *x1 = (-b - sqrt_d) / (2 * a);
    *x2 = (-b + sqrt_d) / (2 * a);
    return two;
}



void Test0Roots() {
    double x1 = 0, x2 = 0;
    const int kn_tests = 2;
    const int n_numbers = 3;

    printf("Testing cases, when 0 roots:\n");

    printf("1. case: a = 0, b = 0, c != 0.\n");
    int tests1[kn_tests][n_numbers] = {
            {0, 0, 1},
            {0, 0, -1},
    };
    for (int i = 0; i < kn_tests; ++i) {
        double a = tests1[i][0];
        double b = tests1[i][1];
        double c = tests1[i][2];
        assert(zero == SolveSquare(a, b, c, &x1, &x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("2. case: d < 0.\n");
    int tests2[kn_tests][n_numbers] = {
            {1, 1, 1},
            {-1, -1, -1},
    };
    for (int i = 0; i < kn_tests; ++i) {
        double a = tests2[i][0];
        double b = tests2[i][1];
        double c = tests2[i][2];
        assert(zero == SolveSquare(a, b, c, &x1, &x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}

void Test1Roots() {
    double x1 = 0, x2 = 0;
    const int kn_tests = 2;
    const int n_numbers = 4;

    printf("Testing cases, when 1 root:\n");

    printf("1. case: a = 0, b != 0, c != 0.\n");
    int tests1[kn_tests][n_numbers] = {
            {0, 1, 2, -2},
            {0, 1, -2, 2},
    };
    for (int i = 0; i < kn_tests; ++i) {
        double a = tests1[i][0];
        double b = tests1[i][1];
        double c = tests1[i][2];
        double rights_x1 = tests1[i][3];
        assert(one == SolveSquare(a, b, c, &x1, &x2));
        assert(equal(x1, rights_x1));
        printf("    %d. Ok\n", i + 1);
    }

    printf("2. case: x1 = x2.\n");
    int tests2[kn_tests][n_numbers] = {
            {1, 2, 1, -1},
            {1, -4, 4, 2},
    };
    for (int i = 0; i < kn_tests; ++i) {
        double a = tests2[i][0];
        double b = tests2[i][1];
        double c = tests2[i][2];
        double rights_x1 = tests2[i][3];
        assert(one == SolveSquare(a, b, c, &x1, &x2));
        assert(equal(x1, rights_x1));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}

void Test2Roots() {
    double x1 = 0, x2 = 0;
    const int kn_tests = 4;
    const int n_numbers = 5;

    printf("Testing cases, when 2 roots:\n");
    int tests[kn_tests][n_numbers] = {
            {1, 7, 12, -4, -3},
            {1, 3, 2, -2, -1},
            {1, 0, -1, -1, 1},
            {1, 1, -6, -3, 2}
    };
    for (int i = 0; i < kn_tests; ++i) {
        double a = tests[i][0];
        double b = tests[i][1];
        double c = tests[i][2];
        double right_x1 = tests[i][3];
        double right_x2 = tests[i][4];
        assert(two == SolveSquare(a, b, c, &x1, &x2));
        assert(equal(x1, right_x1));
        assert(equal(x2, right_x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}

void TestInfRoots() {
    double x1 = 0, x2 = 0;
    const int kn_tests = 1;
    const int n_numbers = 3;

    printf("Testing cases, when Inf roots:\n");
    int tests[kn_tests][n_numbers] = {
            {0, 0, 0},
    };
    for (int i = 0; i < kn_tests; ++i) {
        double a = tests[i][0];
        double b = tests[i][1];
        double c = tests[i][2];
        assert(infinity == SolveSquare(a, b, c, &x1, &x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}