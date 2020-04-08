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
        Matrix();
        Matrix(int row,int col);
        Matrix(const Matrix & mat);
        Matrix(std::initializer_list<double> lst);
        ~Matrix();

        friend std::ostream &operator<<(std::ostream &os,const Matrix &mat);
        friend std::istream &operator>>(std::istream &is,Matrix &mat);
        friend void operator>>(std::string strmat,Matrix &mat);

        Matrix operator+(const Matrix rmat);
        Matrix operator-(const Matrix rmat);
        Matrix operator*(const Matrix rmat);
        Matrix operator*(double k);
        Matrix operator=(const Matrix rmat);
        Matrix& operator()(std::string range);
        double& operator()(int i,int j);
        double& operator()(int i);
        Matrix operator()(int brow,int erow,range r);
        Matrix operator()(range r,int bcol,int ecol);
        Matrix operator()(int row,range r);
        Matrix operator()(range r,int col);

        static Matrix hori(Matrix a,Matrix b);
        static Matrix vert(Matrix a,Matrix b);
        Matrix reshape(int row,int col);
        Matrix transpose();
        Matrix slice(int brow,int erow,int bcol,int ecol);
        static Matrix eye(int row,int col);
        static Matrix ones(int row,int col);
        static Matrix zeros(int row,int col);
        bool is_empty();
        void print();
        void test();
    public:
        int _row;
        int _col;
        double ** _data;
    private:
        void destroy();
        void create(int row,int col);
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