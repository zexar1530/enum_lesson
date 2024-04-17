#include <iostream>
#include <vector>
#include <memory>

class tridiagonal_matrix
{
public:
    std::vector<double> m_down;
    std::vector<double> m_upper;
    std::vector<double> m_middle;
    tridiagonal_matrix(
        const std::vector<double>& down,
        const std::vector<double>& upper,
        const std::vector<double>& middle) :
        m_down{ down }, m_upper{ upper }, m_middle{ middle }
    {};
    ~tridiagonal_matrix() { std::cout << "destructor called\n"; }

    std::unique_ptr<tridiagonal_matrix> clone() {
        return std::make_unique<tridiagonal_matrix>(*this);  //наверно это самый правильный вариант? 
 //       std::unique_ptr<tridiagonal_matrix> ptr(new tridiagonal_matrix(*this)); // а как лучше?
 //       std::unique_ptr<tridiagonal_matrix> ptr(new tridiagonal_matrix(std::move(*this)));   // и с move работает
 //       return ptr;
    }
};

int main()
{
    auto down = std::vector<double>{ -4.0, 5.0 };
    auto upper = std::vector<double>{ 14.0, 8.0 };
    auto middle = std::vector<double>{ 3.0, 1.0, 7.0 };
    auto matrix = std::make_unique<tridiagonal_matrix>(
        down,
        upper,
        middle
    );
    
    auto matrix_clone = matrix->clone();
    auto nnn = matrix_clone->clone();
    std::cout << matrix->m_down[0]<< std::endl; 
    std::cout << matrix_clone->m_down[0] << std::endl;
   

    return 0;
}