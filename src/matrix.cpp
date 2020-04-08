#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cmath>
#include "matrix.hpp"

Matrix::Matrix()
{
    _row=0;
    _col=0;
    _data=nullptr;
}

Matrix::Matrix(int row,int col)
{
    create(row,col);
}

void Matrix::print()
{
    for(int i=0;i<_row;i++)
    {
        for(int j=0;j<_col;j++)
        {
            std::cout<<std::fixed<<std::setprecision(6)<<std::setw(12)<<_data[i][j]<<" ";
        }
        std::cout<<std::endl;
    }    
    std::cout<<std::endl;
}

Matrix::Matrix(const Matrix & mat)
{
    create(mat._row,mat._col);
    for(int i=0;i<mat._row;i++)
    {
        for(int j=0;j<mat._col;j++)
        {
            _data[i][j]=mat._data[i][j];
        }
    }
}

Matrix::Matrix(std::initializer_list<double> lst)
{
    create(1,lst.size());
    int i=0;
    for(auto beg=lst.begin();beg!=lst.end();++beg)
    {
        this->_data[0][i]=*beg;
        i++;
    }
}

Matrix::~Matrix()
{
    destroy();
}

void Matrix::destroy()
{
    if(_data!=nullptr)
    {
        for(int i=0;i<_row;i++)
        {
            delete []_data[i];
        }
        delete []_data;
    }
    _data=nullptr;
    _row=0;
    _col=0;
}

void Matrix::create(int row,int col)
{
    _col=col;
    _row=row;
    _data=nullptr;
    _data= new double * [_row];
    for(int i=0;i<_row;i++)
        _data[i]=new double[_col];

}

Matrix Matrix::slice(int brow,int erow,int bcol,int ecol)
{
    int row=erow-brow+1;
    int col=ecol-bcol+1;
    if(row<0||col<0||row>this->_row||col>this->_col)
    {
        std::cout<<"Invalid slice parameter, ";
        std::cout<<"Returning original matrix: "<<std::endl;
        return *this;
    }

    Matrix tmp(row,col);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            tmp._data[i][j]=this->_data[i+brow][j+bcol];
        }
    }
    
    return tmp;
}

Matrix Matrix::eye(int row,int col)
{
    static Matrix mateye(static_max_size,static_max_size);
    if(row>static_max_size||col>static_max_size)
    {
        std::cout<<"Out of max size"<<static_max_size<<std::endl;
        mateye._row=4;
        mateye._col=4;
        return mateye;
    }

    for(int i=0;i<mateye._row;i++)
    {
        for(int j=0;j<mateye._col;j++)
        {
            if(i!=j)
                mateye._data[i][j]=0;
            else
                mateye._data[i][j]=1;
        }
    }
    mateye._row=row;
    mateye._col=col;
    return mateye;
}

Matrix Matrix::ones(int row,int col)
{
    static Matrix matones(static_max_size,static_max_size);
    if(row>static_max_size||col>static_max_size)
    {
        std::cout<<"Out of max size"<<static_max_size<<std::endl;
        matones._row=4;
        matones._col=4;
        return matones;
    }
    for(int i=0;i<matones._row;i++)
    {
        for(int j=0;j<matones._col;j++)
        {
           matones._data[i][j]=1;
        }
    }
    matones._row=row;
    matones._col=col;
    return matones;
}

Matrix Matrix::zeros(int row,int col)
{
    static Matrix matzeros(static_max_size,static_max_size);
    if(row>static_max_size||col>static_max_size)
    {
        std::cout<<"Out of max size"<<static_max_size<<std::endl;
        matzeros._row=4;
        matzeros._col=4;
        return matzeros;
    }
    for(int i=0;i<matzeros._row;i++)
    {
        for(int j=0;j<matzeros._col;j++)
        {
           matzeros._data[i][j]=0;
        }
    }
    matzeros._row=row;
    matzeros._col=col;
    return matzeros;
}

double& Matrix::operator()(int i)
{
    if(this->_col==1)
    {
        decltype(_data[i][0]) data_i1=_data[i][0];
        return data_i1;
    }
    if(this->_row==1)
    {
        decltype(_data[0][i]) data_1i=_data[0][i];
        return data_1i;
    }

    std::cout<<"No a vector, check it!"<<std::endl;
    decltype(_data[0][0]) data_ij=_data[0][0];

    return data_ij;
}

Matrix Matrix::operator()(int brow,int erow,range r)
{
    switch (r)
    {
        case all:
        {
            Matrix result=slice(brow,erow,0,this->_col-1);
            return result;
        }
    }
    return *this; 
}

Matrix Matrix::operator()(range r,int bcol,int ecol)
{
    switch (r)
    {
        case all:
        {
            Matrix result=slice(0,this->_row-1,bcol,ecol);
            return result;
        }
    }
    return *this; 
}

Matrix Matrix::operator()(range r,int col)
{
    switch (r)
    {
        case all:
        {
            Matrix result=slice(0,this->_row-1,col,col);
            return result;
        }
    }
    return *this; 
}

Matrix Matrix::operator()(int row,range r)
{
    switch (r)
    {
        case all:
        {
            Matrix result=slice(row,row,0,this->_col-1);
            return result;
        }
    }
    return *this; 
}


double& Matrix::operator()(int i,int j)
{
    decltype(_data[i][j]) data_ij=_data[i][j]; 
    return data_ij;
}

Matrix Matrix::operator=(const Matrix rmat)
{    
    create(rmat._row,rmat._col);
    for(int i=0;i<rmat._row;i++)
    {
        for(int j=0;j<rmat._col;j++)
        {
            this->_data[i][j]=rmat._data[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix rmat)
{
    Matrix result(rmat._row,rmat._col);
    for(int i=0;i<result._row;i++)
    {
        for(int j=0;j<result._col;j++)
        {
           result._data[i][j]=this->_data[i][j]+rmat._data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix rmat)
{
    Matrix result(rmat._row,rmat._col);
    for(int i=0;i<result._row;i++)
    {
        for(int j=0;j<result._col;j++)
        {
           result._data[i][j]=this->_data[i][j]-rmat._data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix rmat)
{
    Matrix result(this->_row,rmat._col);
    if(this->_col!=rmat._row)
    {
        std::cout<<"operation * col not equal to row";
        return *this;
    }
    
    double sum=0;
    int i,j,k;
    for(i=0;i<this->_row;i++)
    {
        for(j=0;j<rmat._col;j++)
        {
            for(k=0;k<this->_col;k++)
            {
                sum+=this->_data[i][k]*rmat._data[k][j];
            }
            result._data[i][j]=sum;
            sum=0;
        }
    }
    return result;
}

Matrix Matrix::operator*(double k)
{
    Matrix result(_row,_col);
    for(int i=0;i<this->_row;i++)
    {
        for(int j=0;j<this->_col;j++)
        {
            result._data[i][j]=k*_data[i][j];
        }
    }
    return result;
}



Matrix Matrix::hori(Matrix a,Matrix b)
{
    if(a._row!=b._row&&(!a.is_empty()||!b.is_empty()))
    {
        if(a.is_empty())
            return b;
        if(b.is_empty())
            return a;
        std::cout<<"Unmatch hori"<<std::endl;
        return a;
    }
    Matrix result(a._row,a._col+b._col);
    for(int i=0;i<result._row;i++)
    {
        for(int j=0;j<result._col;j++)
        {
            if(j<a._col)
            {
                result(i,j)=a(i,j);
            }
            else
            {
                result(i,j)=b(i,j-a._col);
            }
            
        }
    }
    return result;
}

Matrix Matrix::vert(Matrix a,Matrix b)
{
    if(a._col!=b._col)
    {
        if(a.is_empty())
            return b;
        if(b.is_empty())
            return a;
        std::cout<<"Unmatch vert"<<std::endl;
        return a;
    }
    Matrix result(a._row+b._row,a._col);
    for(int i=0;i<result._row;i++)
    {
        for(int j=0;j<result._col;j++)
        {
            if(i<a._row)
            {
                result(i,j)=a(i,j);
            }
            else
            {
                result(i,j)=b(i-a._row,j);
            }
            
        }
    }
    return result;
}

Matrix Matrix::reshape(int row,int col)
{
    if(row*col!=_row*_col)
    {
        std::cout<<"Reshape failed, unmatch numbers"<<std::endl;
        return *this;
    }

    Matrix result(row,col);

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            result._data[i][j]=_data[(i*col+j)/_col][(i*col+j)%_col];
        }
    }
    
    return result;
}

std::ostream &operator<<(std::ostream &os,const Matrix &mat)
{
    for(int i=0;i<mat._row;i++)
    {
        for(int j=0;j<mat._col;j++)
        {
            os<<std::fixed<<std::setprecision(6)<<std::setw(12)<<mat._data[i][j]<<" ";
        }
        os<<std::endl;
    }    
    return os;
}

std::istream &operator>>(std::istream &is,Matrix &mat)
{
    std::string strmat;
    is>>strmat;
    std::string tmpstr=strmat;
    std::vector<double> result;
    int row=1;
    int col=1;
    for(int i=0;i<tmpstr.size();i++)
    {
        if(tmpstr[i]==';') 
        {
            tmpstr[i]=',';
            row++;
        }
    }
    split(tmpstr,",",result);
    col=result.size()/row;

    mat.destroy();
    mat.create(row,col);

    for(int i=0;i<mat._row;i++)
    {
        for(int j=0;j<mat._col;j++)
        {
            mat._data[i][j]=result[i*mat._col+j];
        }
    }
    return is;
}

void operator>>(std::string strmat,Matrix &mat)
{
    std::string tmpstr=strmat;
    std::vector<double> result;
    int row=1;
    int col=1;
    for(int i=0;i<tmpstr.size();i++)
    {
        if(tmpstr[i]==';') 
        {
            tmpstr[i]=',';
            row++;
        }
    }
    split(tmpstr,",",result);
    col=result.size()/row;

    mat.destroy();
    mat.create(row,col);

    for(int i=0;i<mat._row;i++)
    {
        for(int j=0;j<mat._col;j++)
        {
            mat._data[i][j]=result[i*mat._col+j];
        }
    }
}

void split(const std::string&s,const std::string & delim,std::vector<double> &ele)
{
    size_t last=0;
    size_t index;
    int row=1;
    index=s.find_first_of(delim,last);
    std::string str;
    double digit;
    while(index!=std::string::npos)
    {
        str=s.substr(last,index-last);
        digit=stod(str);
        ele.push_back(digit);
        last=index+1;
        index=s.find_first_of(delim,last);
    }
    if(index-last>0)
    {
        str=s.substr(last,index-last);
        digit=stod(str);
        ele.push_back(digit);
    }
}

Matrix Matrix::transpose()
{
    Matrix result(_col,_row);

    for(int i=0;i<_col;i++)
    {
        for(int j=0;j<_row;j++)
        {
            result(i,j)=_data[j][i];
        }
    }
    return result;

}



bool Matrix::is_empty()
{
    if(this->_col==0&&this->_col==0)
        return true;
    return false;
}

void Matrix::test()
{
    std::cout<<"testing"<<std::endl;
    std::vector<double> result;
    int row=1;
    std::string str("34.2,56.55,56.66;3.14,22.33,5.16");
    std::string tmpstr=str;
    for(int i=0;i<tmpstr.size();i++)
    {
        if(tmpstr[i]==';') 
        {
            tmpstr[i]=',';
            row++;
        }
    }
    split(tmpstr,",",result);
    std::cout<<"row = "<<row<<std::endl;
    for_each(result.begin(),result.end(),[](double ele){std::cout<<ele<<" ";});
}


