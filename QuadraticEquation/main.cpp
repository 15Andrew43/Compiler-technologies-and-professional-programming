#include <stdio.h>
#include <math.h>
#include <assert.h>

const double eps = 0.0001;

enum nRoots {
    zeroRoots,
    oneRoots,
    twoRoots,
    infinityRoots
};


bool equal(double x, double y);
nRoots SolveLinear(double b, double c, double* x1);
nRoots SolveSquare (double a, double b, double c,
                    double* x1, double* x2);



struct Test;

void RunTests();
void Test0Roots();
void Test1Roots();
void Test2Roots();
void TestInfRoots();

void ExtractValues(const Test& test, double& a, double& b, double& c, double& x1, double& x2);




int main() {
    printf("# Square equation solver\n"
           "# (c) Andrew Borovets, 2021\n\n");
    printf("enter 0 - to run test\n");

    char answer = '0';
    scanf("%c", &answer);

    if (answer == '0') {
        RunTests();
        printf("All tests are passed successfully!\n");
    }

    printf("# Enter a, b, c: ");
    double a = 0, b = 0, c = 0;
    scanf("%lg %lg %lg", &a, &b, &c);
    double x1 = 0, x2 = 0;
    int nRoots = SolveSquare(a, b, c, &x1, &x2);
    switch (nRoots) {
        case zeroRoots:
            printf("No roots\n");
            break;
        case oneRoots:
            printf("x = %lg\n", x1);
            break;
        case twoRoots:
            printf("x1 = %lg, x2 = %lg\n", x1, x2);
            break;
        case infinityRoots:
            printf("Any number");
            break;
        default:
            printf("main(): ERROR: nRoots = %d\n",
                   nRoots);
            return 1;
    }
}



//------------------------------------------------
//! Checks the equality of two doubles
//!
//! \param [in]     x   first double
//! \param [in]     y   second double
//! \return The validity of the equality of two numbers
//------------------------------------------------
bool equal(double x, double y) {
    return abs(x - y) < eps;
}



//------------------------------------------------
//! Solves a linear equation bx + c = 0
//!
//! \param [in]     b      b-coefficient
//! \param [in]     c      c-coefficient
//! \param [out]    x      Pointer to the root
//! \return Number of roots
//!
//! \note   In case of infinite number of roots,
//!         return 'infinityRoots'.
//------------------------------------------------
nRoots SolveLinear(double b, double c, double* x) {
    if (equal(b, 0)) {
        return (equal(c, 0)) ? infinityRoots : zeroRoots;
    }
//  if (b != 0)
    *x = -c / b;
    return oneRoots;
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
//!         return 'infinityRoots'.
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
        return oneRoots;
    } else if (d < 0) {
        return zeroRoots;
    }
//  if (d > 0)
    double sqrt_d = sqrt(d);

    *x1 = (-b - sqrt_d) / (2 * a);
    *x2 = (-b + sqrt_d) / (2 * a);

    return twoRoots;
}



struct Test {
    double a = 0;
    double b = 0;
    double c = 0;
    double x1 = 0;
    double x2 = 0;
};

void RunTests() {
    Test0Roots();
    Test1Roots();
    Test2Roots();
    TestInfRoots();
}

void Test0Roots() {
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    double right_x1 = 0, right_x2 = 0;
    const int kn_tests = 2;

    printf("Testing cases, when 0 roots:\n");

    printf("1. case: a = 0, b = 0, c != 0.\n");
    Test tests1[kn_tests] = {
            {0, 0, 1},
            {0, 0, -1},
    };
    for (int i = 0; i < kn_tests; ++i) {
        ExtractValues(tests1[i], a, b, c, right_x1, right_x2);
        assert(zeroRoots == SolveSquare(a, b, c, &x1, &x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("2. case: d < 0.\n");
    Test tests2[kn_tests] = {
            {1, 1, 1},
            {-1, -1, -1},
    };
    for (int i = 0; i < kn_tests; ++i) {
        ExtractValues(tests2[i], a, b, c, right_x1, right_x2);
        assert(zeroRoots == SolveSquare(a, b, c, &x1, &x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}

void Test1Roots() {
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    double right_x1 = 0, right_x2 = 0;
    const int kn_tests = 2;

    printf("Testing cases, when 1 root:\n");

    printf("1. case: a = 0, b != 0, c != 0.\n");
    Test tests1[kn_tests] = {
            {0, 1, 2, -2},
            {0, 1, -2, 2},
    };
    for (int i = 0; i < kn_tests; ++i) {
        ExtractValues(tests1[i], a, b, c, right_x1, right_x2);
        assert(oneRoots == SolveSquare(a, b, c, &x1, &x2));
        assert(equal(x1, right_x1));
        printf("    %d. Ok\n", i + 1);
    }

    printf("2. case: x1 = x2.\n");
    Test tests2[kn_tests] = {
            {1, 2, 1, -1},
            {1, -4, 4, 2},
    };
    for (int i = 0; i < kn_tests; ++i) {
        ExtractValues(tests2[i], a, b, c, right_x1, right_x2);
        assert(oneRoots == SolveSquare(a, b, c, &x1, &x2));
        assert(equal(x1, right_x1));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}

void Test2Roots() {
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    double right_x1 = 0, right_x2 = 0;
    const int kn_tests = 4;

    printf("Testing cases, when 2 roots:\n");
    Test tests[kn_tests] = {
            {1, 7, 12, -4, -3},
            {1, 3, 2, -2, -1},
            {1, 0, -1, -1, 1},
            {1, 1, -6, -3, 2}
    };
    for (int i = 0; i < kn_tests; ++i) {
        ExtractValues(tests[i], a, b, c, right_x1, right_x2);
        assert(twoRoots == SolveSquare(a, b, c, &x1, &x2));
        assert(equal(x1, right_x1));
        assert(equal(x2, right_x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}

void TestInfRoots() {
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    double right_x1 = 0, right_x2 = 0;
    const int kn_tests = 1;

    printf("Testing cases, when Inf roots:\n");
    Test tests[kn_tests] = {
            {0, 0, 0},
    };
    for (int i = 0; i < kn_tests; ++i) {
        ExtractValues(tests[i], a, b, c, right_x1, right_x2);
        assert(infinityRoots == SolveSquare(a, b, c, &x1, &x2));
        printf("    %d. Ok\n", i + 1);
    }

    printf("\n\n");
}

void ExtractValues(const Test& test, double& a, double& b, double& c, double& x1, double& x2) {
    a = test.a;
    b = test.b;
    c = test.c;
    x1 = test.x1;
    x2 = test.x2;
}