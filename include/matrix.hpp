#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <string>
#include <vector>
const unsigned int static_max_size=100;
const double pi=3.141592653;
const double rad2deg = 180 / pi;
const double deg2rad = pi / 180;
const double eps=10e-6;

enum range
{
    all,
};

class Matrix
{
    public:
        //constructor and destructor
        Matrix();
        Matrix(size_t row,size_t col);
        Matrix(const Matrix & mat);
        Matrix(std::initializer_list<double> lst);
        ~Matrix();
        //overload cout and cin
        friend std::ostream &operator<<(std::ostream &os,const Matrix &mat);
        friend std::istream &operator>>(std::istream &is,Matrix &mat);
        friend void operator>>(std::string strmat,Matrix &mat);
        //overload operator + - * / and scalar multimple
        Matrix operator+(const Matrix rmat);
        Matrix operator-(const Matrix rmat);
        Matrix operator*(const Matrix rmat);
        Matrix operator*(double k);
        Matrix operator=(const Matrix rmat);
        bool operator==(const Matrix rmat);
        bool operator!=(const Matrix rmat);
        
        //submatrix operator
        double& operator()(size_t i,size_t j);
        double& operator()(size_t i);
        Matrix operator()(size_t brow,size_t erow,range r);
        Matrix operator()(range r,size_t bcol,size_t ecol);
        Matrix operator()(size_t row,range r);
        Matrix operator()(range r,size_t col);
    
        //concatenates and reshape
        static Matrix hori(Matrix a,Matrix b);
        static Matrix vert(Matrix a,Matrix b);
        Matrix reshape(size_t row,size_t col);
        Matrix slice(size_t brow,size_t erow,size_t bcol,size_t ecol);
    
        //common matrix form
        static Matrix eye(size_t row,size_t col);
        static Matrix ones(size_t row,size_t col);
        static Matrix zeros(size_t row,size_t col);
        static Matrix rand(size_t row,size_t col);
    
        //extra operator: transpose,inverse
        Matrix transpose();
        //bool inverse
        
        //status of the matrix
        bool is_empty();
        void print();
        void test();
    private:
        size_t _row;
        size_t _col;
        double ** _data;
        void destroy();
        void create(size_t row,size_t col);
};
void split(const std::string&s,const std::string & delim,std::vector<double> &ele);



enum SpinSequence
{
	//relative
	zyx = 6,
	yzx = 9,
	zxy = 18,
	xzy = 24,
	yxz = 33,
	xyz = 36,
	xyx = 4,
	xzx = 8,
	yxy = 17,
	yzy = 25,
	zxz = 34,
	zyz = 38,
	//Absolute
	azyx = 70,
	ayzx = 73,
	azxy = 82,
	axzy = 88,
	ayxz = 97,
	axyz = 100,
	axyx = 68,
	axzx = 72,
	ayxy = 81,
	ayzy = 89,
	azxz = 98,
	azyz = 102,
};
#endif 
