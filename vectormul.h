#ifndef VECTORMUL_H
#define VECTORMUL_H
#define NUM double
#define VECTOR vector<double>
#define MATRIX vector<vector<double>>
#define FVVN function<VECTOR(VECTOR,NUM)>
#define FNVV function<NUM(VECTOR,VECTOR)>
#define FVMV function<VECTOR(MATRIX,VECTOR)>
#define FMMN function<MATRIX(MATRIX,NUM)>
#define FMMM function<MATRIX(MATRIX,MATRIX)>
#include <vector>
#include <functional>
#include <chrono>
#include <string>
using namespace std;

VECTOR randomVector(int n);
MATRIX randomMatrix(int n, int m);

template<typename p1,typename p2>
class FunCallerTwoParams{
protected:
    int n;
    virtual void callFun(p1,p2) = 0;
    virtual p1 getRandomP1() = 0;
    virtual p2 getRandomP2() = 0;

public:
    FunCallerTwoParams(int n){
        this->n = n;
    }
    int getTimeRandom(){
        auto param1 = getRandomP1();
        auto param2 = getRandomP2();
        auto start = chrono::system_clock::now();
        callFun(param1,param2);
        auto time = chrono::duration_cast<std::chrono::microseconds>
                (chrono::system_clock::now() - start).count();
        return time;
    }
};

//--------------------------------------------------------------

class VectorMulNum : public FunCallerTwoParams<VECTOR,NUM>{
private:
    VECTOR vectorMulNum(VECTOR v,NUM a){
        VECTOR res;
        res.resize(v.size());
        for(int i = 0; i < v.size(); i++)
            res[i] = v[i] * a;
        return res;

    }

public:
    using FunCallerTwoParams::FunCallerTwoParams;
    VECTOR getRandomP1(){
        return randomVector(n);
    }
    NUM getRandomP2(){
        return rand();
    }
    void callFun(VECTOR v,NUM num){
        auto x = vectorMulNum(v,num);
    }
};

//--------------------------------------------------------------

class MatrixMulNum : public FunCallerTwoParams<MATRIX,NUM>{
private:
    MATRIX matrixMulNum(MATRIX m,NUM a){
        MATRIX res;
        res.resize(m.size());
        for(int i = 0; i < m.size(); i++){
            res[i].resize(m[i].size());
            for(int j = 0; j < m[i].size(); j++ ){
                res[i][j] = m[i][j] * a;
            }
        }
        return res;
    }

public:
    using FunCallerTwoParams::FunCallerTwoParams;
    MATRIX getRandomP1(){
        return randomMatrix(2*n,n);
    }
    NUM getRandomP2(){
        return rand();
    }
    void callFun(MATRIX v,NUM num){
        auto x = matrixMulNum(v,num);
    }
};

//--------------------------------------------------------------

class VectorMulVector : public FunCallerTwoParams<VECTOR,VECTOR>{
private:
    NUM vectorMulVector(VECTOR v1, VECTOR v2){
        double res = 0;
        if (v1.size() == v2.size()){
            for(int i = 0; i <v1.size(); i++)
                res += v1[i]*v2[i];
        }
        return res;
    }

public:
    using FunCallerTwoParams::FunCallerTwoParams;
    VECTOR getRandomP1(){
        return randomVector(n);
    }
    VECTOR getRandomP2(){
        return randomVector(n);
    }
    void callFun(VECTOR v1,VECTOR v2){
        auto x = vectorMulVector(v1,v2);
    }
};

//--------------------------------------------------------------

class MatrixMulVector : public FunCallerTwoParams<MATRIX,VECTOR>{
private:

    VECTOR matrixMulVector(MATRIX M, VECTOR x){
        VECTOR res;
        if (M[0].size() == x.size()){
            res.resize(M.size());
            for(int i = 0; i < M.size(); i++){
                res[i] = 0;
                for(int j = 0; j < M[i].size();j++){
                    res[i] += M[i][j] * x[j];
                }
           }
        }
        return res;
    }

public:
    using FunCallerTwoParams::FunCallerTwoParams;
    MATRIX getRandomP1(){
        return randomMatrix(2*n,n);
    }
    VECTOR getRandomP2(){
        return randomVector(n);
    }
    void callFun(MATRIX m,VECTOR v){
        auto x = matrixMulVector(m,v);
    }
};

//--------------------------------------------------------------

class MatrixMulMatrix : public FunCallerTwoParams<MATRIX,MATRIX>{
private:


    MATRIX matrixMulMatrix(MATRIX m1, MATRIX m2 ){
        MATRIX res;
        if (m1[0].size() == m2.size()){
            res.resize(m1.size());

            for(int i = 0; i < res.size(); i++){
                res[i].resize(m2[0].size());
                for(int j = 0; j < res[0].size(); j++){
                    res[i][j] = 0;
                    for(int k = 0; k < m2.size(); k++ )
                        res[i][j] += m1[i][k]*m2[k][j];
               }
            }
        }
        return res;
    }


public:
    using FunCallerTwoParams::FunCallerTwoParams;
    MATRIX getRandomP1(){
        return randomMatrix(2*n,n);
    }
    MATRIX getRandomP2(){
        return randomMatrix(n,3*n);
    }
    void callFun(MATRIX m1,MATRIX m2){
        auto x = matrixMulMatrix(m1,m2);
    }
};

//--------------------------------------------------------------

void outVector(VECTOR v){
    for(auto e: v  )
        cout << '|'<< e << '|' <<endl;
}
void outMatrix(MATRIX m){
    for(auto r : m){
        for(auto elem : r)
            cout << elem << ' ';
        cout << endl;
    }
}
MATRIX randomMatrix(int n,int m){
    MATRIX M;
    M.resize(n);
    for(int i = 0; i < n; i++){
       M[i].resize(m);
       for(int j = 0; j < m; j++)
           M[i][j] = rand();
    }
    return M;
}

VECTOR randomVector(int n){
    VECTOR V;
    V.resize(n);
    for(int i = 0; i < n; i++)
        V[i] = rand();
    return V;
}


#endif // VECTORMUL_H
