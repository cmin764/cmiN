#include "exercises.h"

using namespace std;

int main()
{
    cout << "1. " << countTrailingZeroes(12345) << endl;
    cout << "2. " << max(3.14, 2.56, 1.87) << endl;
    cout << "3. " << min(3.14, 2.56, 1.87) << endl;
    cout << "4. " << arithmeticMean(2, 4, 6) << endl;
    cout << "5. " << geometricMean(-3, 3, 3) << endl;
    cout << "6. " << harmonicMean(2, 4, 8) << endl;
    cout << "7. " << canBeTriangle(5, 7, 3) << endl;
    Triangle triangle = {.a = 5, .b = 6, .c = 1};
    cout << "8. " << classifyTriangleByAngle(triangle) << endl;
    cout << "9. " << classifyTriangleBySide(triangle) << endl;
    cout << "10. " << computePerimeter(triangle) << endl;
    cout << "11. " << computeArea(triangle) << endl;
    cout << "12. " << getMaxMedian(triangle) << endl;
    cout << "13. " << getMinHeight(triangle) << endl;
    cout << "14. " << getSquares(-1, 5, 10).length << endl;
    cout << "15. " << getCubes(-2, 5, 10).length << endl;
    cout << "16. " << getNthRoots(-1, 5, 10, 4).length << endl;
    DiophantineEquation e;
    e.a = e.b = e.c = 0;
    cout << "17. " << solveDiophantineEquation(e).hasSolutions << endl;
    Complex c1, c2;
    c1.a = 2; c1.b = 3;
    c2.a = 1; c2.b = 4;
    cout << "18. " << sum(c1, c2).a << endl;
    cout << "18. " << product(c1, c2).a << endl;
    return 0;
}
