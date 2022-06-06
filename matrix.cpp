#include <iostream>
#include <vector>

class Matrix {

public:
	Matrix(int n_rows, int n_cols) : matrix_(n_rows, std::vector<double>(n_cols, 0)) {}

	Matrix(int n_order) : matrix_(n_order, std::vector<double>(n_order, 0)) {}

	Matrix(const std::vector<std::vector<double>>& matrix) : matrix_(matrix) {}

	Matrix& operator+=(const Matrix& rhs) {
		for (size_t row = 0; row < rhs.Rows(); ++row) {
			for (size_t col = 0; col < rhs.Columns(); ++col) {
				(*this)(row, col) += rhs(row, col);
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& rhs) {
		Matrix output(this->Rows(), this->Columns());

		for (size_t row = 0; row < rhs.Rows(); ++row) {
			for (size_t col = 0; col < rhs.Columns(); ++col) {
				output(row, col) = (*this)(row, col) + rhs(row, col);
			}
		}
		return output;
	}

	Matrix& operator-=(const Matrix& rhs) {
		for (size_t row = 0; row < rhs.Rows(); ++row) {
			for (size_t col = 0; col < rhs.Columns(); ++col) {
				(*this)(row, col) -= rhs(row, col);
			}
		}
		return *this;
	}

	Matrix operator-(const Matrix& rhs) {
		Matrix output(this->Rows(), this->Columns());

		for (size_t row = 0; row < rhs.Rows(); ++row) {
			for (size_t col = 0; col < rhs.Columns(); ++col) {
				output(row, col) = (*this)(row, col) - rhs(row, col);
			}
		}
		return output;
	}

	Matrix operator*(const Matrix& rhs) {
		Matrix output(this->Rows(), rhs.Columns());

		for (size_t row = 0; row < output.Rows(); ++row) {
			for (size_t col = 0; col < output.Columns(); ++col) {
				for (size_t index = 0; index < this->Columns(); ++index) {
					output(row, col) += (*this)(row, index) * rhs(index, col);
				}
			}
		}
		return output;
	}

	Matrix& operator*=(const Matrix& rhs) {
		Matrix copy_instance = *this;

		for (size_t row = 0; row < this->Rows(); ++row) {
			for (size_t col = 0; col < rhs.Columns(); ++col) {
				(*this)(row, col) = 0;
				for (size_t index = 0; index < this->Columns(); ++index) {
					(*this)(row, col) += copy_instance(row, index) * rhs(index, col);
				}
			}
		}
		return *this;
	}

	int Rows() const {
		return matrix_.size();
	}

	int Columns() const {
		return matrix_[0].size();
	}

	double& operator()(int row, int col) {
		return matrix_[row][col];
	}

	double operator()(int row, int col) const {
		return matrix_[row][col];
	}

	void Print() const {
		for (const auto& row : matrix_) {
			for (const auto& element : row) {
				std::cout << element << " ";
			}
			std::cout << "\n";
		}
	}

private:
	std::vector<std::vector<double>> matrix_;
};

Matrix Transpose(const Matrix& matrix) {
	Matrix transposed(matrix.Columns(), matrix.Rows());

	for (size_t row = 0; row < matrix.Rows(); ++row) {
		for (size_t col = 0; col < matrix.Columns(); ++col) {
			transposed(col, row) = matrix(row, col);
		}
	}
	return transposed;
}

Matrix Identity(int n_order) {
	Matrix identity_matrix(n_order);
	for (size_t index = 0; index < identity_matrix.Rows(); ++index) {
		identity_matrix(index, index) = 1;
	}
	return identity_matrix;
}

int main() {
	Matrix p = Identity(10);
	p += Identity(10);
	// p.Print();

	Matrix g = Identity(10);
	g += Identity(10);
	// Matrix g = Identity(10);
	p *= g;
	p.Print();
	return 0;
}