#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cmath>
#include <ctime>
#include <random>
#include "matrix.hpp"

using namespace std; 


Matrix::Matrix()
{
    _row=0;
    _col=0;
    _data=nullptr;
}

Matrix::Matrix(size_t row,size_t col)
{
    create(row,col);
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

Matrix::Matrix(std::vector<double> matVec)
{
    //default contruct column vector
    create(1, matVec.size());
    int i = 0;
    for (auto beg = matVec.begin(); beg != matVec.end(); ++beg)
    {
        this->_data[0][i] = *beg;
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

void Matrix::create(size_t row,size_t col)
{
    _col=col;
    _row=row;
    _data=nullptr;
    _data= new double * [_row];
    for(int i=0;i<_row;i++)
        _data[i]=new double[_col];

}

Matrix Matrix::slice(size_t brow,size_t erow,size_t bcol,size_t ecol)
{
    size_t row=erow-brow+1;
    size_t col=ecol-bcol+1;
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

Matrix Matrix::eye(size_t row,size_t col)
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

Matrix Matrix::ones(size_t row,size_t col)
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

Matrix Matrix::zeros(size_t row,size_t col)
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



Matrix Matrix::rand(size_t row,size_t col)
{
    static Matrix matrand(static_max_size,static_max_size);
    if(row>static_max_size||col>static_max_size)
    {
        std::cout<<"Out of max size"<<static_max_size<<std::endl;
        matrand._row=4;
        matrand._col=4;
        return matrand;
    }
    static std::uniform_real_distribution<double> u;
    static std::default_random_engine e(static_cast<unsigned>(time(0)));
    for(int i=0;i<matrand._row;i++)
    {
        for(int j=0;j<matrand._col;j++)
        {
           matrand._data[i][j]=u(e);
        }
    }
    matrand._row=row;
    matrand._col=col;
    return matrand;
}

double& Matrix::operator()(size_t i)
{
    if(this->_col==1)
    {
        double &data_i1=_data[i][0];
        return data_i1;
    }
    if(this->_row==1)
    {
        double &data_1i=_data[0][i];
        return data_1i;
    }

    std::cout<<"No a vector, check it!"<<std::endl;
    double &data_ij=_data[0][0];

    return data_ij;
}

Matrix Matrix::operator()(size_t brow,size_t erow,range r)
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

Matrix Matrix::operator()(range r,size_t bcol,size_t ecol)
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

Matrix Matrix::operator()(range r,size_t col)
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

Matrix Matrix::operator()(size_t row,range r)
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


double& Matrix::operator()(size_t i,size_t j)
{
    double &data_ij=_data[i][j]; 
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


bool Matrix::operator==(const Matrix rmat)
{
    if(rmat._row!=this->_row||rmat._col!=this->_col)
    {
        return false;
    }
    for(int i=0;i<this->_row;i++)
      {
          for(int j=0;j<this->_col;j++)
          {
              if(rmat._data[i][j]!=this->_data[i][j])
                  return false;
          }
      }
    return true;
}


bool Matrix::operator!=(const Matrix rmat)
{
    if(rmat._row!=this->_row||rmat._col!=this->_col)
    {
        return true;
    }
    for(int i=0;i<this->_row;i++)
      {
          for(int j=0;j<this->_col;j++)
          {
              if(rmat._data[i][j]!=this->_data[i][j])
                  return true;
          }
      }
    return false;
}


//double& Matrix::replace(size_t i,Matrix m)
//{
//    double t;
//    return t;
//}
Matrix Matrix::replace(size_t brow,size_t erow,range r,Matrix m)
{
    return Matrix::zeros(1, 1);
}
Matrix Matrix::replace(range r,size_t bcol,size_t ecol,Matrix m)
{
    return Matrix::zeros(1, 1);

}
//replace row th
Matrix Matrix::replace(size_t row,range r,Matrix m)
{
    //Matrix result=*this;
    if(m._col>this->_col||m._row!=1)
    {
        std::cout<<"Not a single row or not enough room to replace!"<<std::endl;
    }
    else
    {
        for(int i=0;i<m._col;i++)
        {
            this->_data[row][i]=m(0,i);
        }
    }  
    return *this;
}

Matrix Matrix::rowExchange(size_t r1, size_t r2)
{
    Matrix result=*this;
    if (r1 >= 0 && r1 < _row && r2>=0 && r2 < _row)
    {
        if (r1 == r2)
        {
            return *this;
        }
        Matrix mr1=result.slice(r1, r1, 0, this->_col - 1);
        Matrix mr2=result.slice(r2, r2, 0, this->_col - 1);
        result= result.replace(r2, all, mr1);
        result= result.replace(r1, all, mr2);
    }
    return result;
}
Matrix Matrix::colExchange(size_t c1, size_t c2)
{
    Matrix result = *this;
    if (c1 >= 0 && c1 < _row && c2 >= 0 && c2 < _row)
    {
        if (c1 == c2)
        {
            return *this;
        }
        Matrix mc1 = result.slice(0, this->_row - 1,c1, c1);
        Matrix mc2 = result.slice(0, this->_row - 1, c2, c2);
        result = result.replace(all, c2, mc1);
        result = result.replace(all, c1, mc2);
    }
    return result;
}

//replace col th
Matrix Matrix::replace(range r,size_t col,Matrix m)
{
    if(m._row>this->_row||m._col!=1)
    {
        std::cout<<"Not a single col or not enough room to replace!"<<std::endl;
    }
    else
    {
        for(int i=0;i<m._row;i++)
        {
            this->_data[i][col]=m(i,0);
        }
    }  
    return *this;
}


Matrix Matrix::addkrow(size_t row2bereplace,size_t baserow,double k)
{
    Matrix BaseMat=(*this)(baserow,all);
    (*this).replace(row2bereplace,all,BaseMat*k+(*this)(row2bereplace,all));
    return *this;
}

Matrix Matrix::addkcol(size_t col2bereplace,size_t basecol,double k)
{

    Matrix BaseMat=(*this)(all,basecol);
    (*this).replace(all,col2bereplace,BaseMat*k+(*this)(all,col2bereplace));
    return *this;
}

Matrix Matrix::minorM(size_t row,size_t col)
{
    Matrix result;
    std::set<int> validArea;
    //border cheak
    if(row==0)
    {
        validArea.insert(3);
        validArea.insert(4);
    }
    if(col==0)
    {
        validArea.insert(2);
        validArea.insert(4);
    }
    if(row==this->_row-1)
    {
        validArea.insert(1);
        validArea.insert(2);
    }
    if(col==this->_col-1)
    {
        validArea.insert(1);
        validArea.insert(3);
    }
    if(validArea.empty())
    {
        validArea.insert(1);
        validArea.insert(2);
        validArea.insert(3);
        validArea.insert(4);
    }
    Matrix S1,S2,S3,S4;

    if(validArea.find(1)!=validArea.end())
    {
        S1=slice(0,row-1,0,col-1);
        //std::cout<<"S1 = "<<S1;
    }
    if(validArea.find(2)!=validArea.end())
    {
        S2=slice(0,row-1,col+1,this->_col-1);
        //std::cout<<"S2 = "<<S2;
    }
    
    if(validArea.find(3)!=validArea.end())
    {
        S3=slice(row+1,this->_row-1,0,col-1);
        //std::cout<<"S3 = "<<S3;
    }
    if(validArea.find(4)!=validArea.end())
    {
        S4=slice(row+1,this->_row-1,col+1,this->_col-1);
       // std::cout<<"S4 = "<<S4;
    }
    Matrix S12,S34;
    if(validArea.size()==1)
    {
        if(!S1.is_empty())
            result=S1;
        if(!S2.is_empty())
            result=S2;
        if(!S3.is_empty())
            result=S3;
        if(!S4.is_empty())
            result=S4;
    }
    else if(validArea.size()==2)
    {
        if(!S1.is_empty()&&!S2.is_empty())
            result=hori(S1,S2);
        if(!S1.is_empty()&&!S3.is_empty())
            result=vert(S1,S3);
        if(!S2.is_empty()&&!S4.is_empty())
            result=vert(S2,S4); 
        if(!S3.is_empty()&&!S4.is_empty())
            result=hori(S3,S4);      
    }
    else
    {
        S12=hori(S1,S2);
        S34=hori(S3,S4);
        result=vert(S12,S34);
    }

    return result; 
}

double Matrix::det()
{
    double sum=0.0;
    Matrix M=*this;

    if (this->size() == 1)
    {
        return M(0, 0);
    }

    if (this->size() == 2)
    {
        //cout << *this << endl;
       // cout << "return value Mat: " << endl;
        //cout << M << endl;
        return M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0);
    }

    double value = 0.0;
    Matrix MM;

    for (int i = 0; i < M.size(); i++)
    {
        //cout << "pivot = " << M(0, i) << endl;
       // cout << "sign = " << pow(-1, i) << endl;
        //cout << "MM" << M.minorM(0,i) << endl;

        MM=M.minorM(0, i);
        value += MM.det() * pow(-1, i) *M(0,i);

    }

    sum += value;

    return sum;

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

Matrix Matrix::reshape(size_t row,size_t col)
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
    size_t row=1;
    size_t col=1;
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
    size_t row=1;
    size_t col=1;
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

Matrix Matrix::inverse()
{
    Matrix M = *this;
    if (M.det() == 0)
    {
        std::cout << "Matrix::inverse\A3\BANot a invertible Matrix " << std::endl;
        return M;
    }
    double detVal=M.det();

    Matrix result = M;

    for (int i = 0; i < M._row; i++)
    {
        for (int j = 0; j < M._col; j++)
        {
           // cout << "M.minorM(i, j) ="<<endl << M.minorM(i, j) << endl;
            result(i, j) = pow(-1,i+j)*(M.minorM(i, j).det());
        }
    }
    
    return result.transpose()*(1/detVal);

}


bool Matrix::is_empty()
{
    if(this->_col==0&&this->_row==0)
        return true;
    return false;
}

bool Matrix::is_square()
{
    return _row==_col;
}

size_t Matrix::size()
{
    return this->_row;    
}
