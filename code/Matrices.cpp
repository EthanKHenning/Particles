#include "Matrices.h"
namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;
		/*
		a.resize(rows);
		for (size_t i = 0; i < rows; i++)
		{
			a.at(i).resize(cols, 0);
		}
		*/
		a.resize(rows, vector<double>(cols, 0));
	}

	///Add each corresponing element.
	///usage: c = a+b;
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
            throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), a.getCols());
		
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}

		return c;
	}
    ///Matrix multiply.  See description.
    ///usage:  c = a * b;
	Matrix operator*(const Matrix& a, const Matrix& b)
	{
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }

		Matrix c(a.getRows(), b.getCols());
        double sum;

        for (int k = 0; k < b.getCols(); k++)
        {
            for (int i = 0; i < a.getRows(); i++)
            {
                sum = 0;
                for (int j = 0; j < a.getCols(); j++)
                {
                    sum += a(i, j) * b(j, k);
                }
                c(i, k) = sum;
            }
        }
        return c;
	}

	///Matrix comparison.  See description.
	///usage:  a == b
	bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if (abs(a(i,j) - b(i,j)) > 0.001)
                    return false;
            }
        }
        return true;
	}

	///Matrix comparison.  See description.
	///usage:  a != b
	bool operator!=(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return true;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if ( abs(a(i,j) - b(i,j)) > 0.001 )
                    return true;
            }
        }
        return false;
    }

	///Output matrix.
	///Separate columns by ' ' and rows by '\n'
	ostream& operator<<(ostream& os, const Matrix& a)
	{
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(10) << a(i, j) << ' ';
            }
            os << '\n';
        }
        return os;
	}
    RotationMatrix::RotationMatrix(double theta) : Matrix(2,2) {
        a.at(0).at(0) = cos(theta);
        a.at(0).at(1) = (sin(theta)) * -1;
        a.at(1).at(0) = sin(theta);
        a.at(1).at(1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2,2){
        a.at(0).at(0) = scale;
        a.at(0).at(1) = 0;
        a.at(1).at(0) = 0;
        a.at(1).at(1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < nCols; j++)
            {
                if (i == 0) {a.at(i).at(j) = xShift;}

                else {a.at(i).at(j) = yShift;}
            }
        }
    }

}