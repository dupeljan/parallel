#include <iostream>
#include "vectormul.h"
#include <ctime>
#include <chrono>
using namespace std;




int main(int argc, char *argv[])
{
    srand(unsigned(std::time(0)));
    const int n = 100;

    cout << "vectorMulNum" << endl;
    cout << "time: " <<  VectorMulNum(n).getTimeRandom() << endl;

    cout << "vectorMulVector" << endl;
    cout << "time: " <<  VectorMulVector(n).getTimeRandom() << endl;

    cout << "matrixMulVector" << endl;
    cout << "time: " <<  MatrixMulVector(n).getTimeRandom() << endl;

    cout << "matrixMulMatrix" << endl;
    cout << "time: " <<  MatrixMulMatrix(n).getTimeRandom() << endl;

    cout << "matrixMulNum" << endl;
    cout << "time: " <<  MatrixMulNum(n).getTimeRandom() << endl;


}
