#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

struct Complex
{
    double real; // 实部
    double imag; // 虚部

    // 构造函数
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 复数加法
    Complex operator+(const Complex &b) const
    {
        return Complex(real + b.real, imag + b.imag);
    }

    // 复数减法
    Complex operator-(const Complex &b) const
    {
        return Complex(real - b.real, imag - b.imag);
    }

    // 复数乘法
    Complex operator*(const Complex &b) const
    {
        return Complex(real * b.real - imag * b.imag,
                       real * b.imag + imag * b.real);
    }

    // 复数除法
    Complex operator/(const Complex &b) const
    {
        double denom = b.real * b.real + b.imag * b.imag;
        if (denom == 0)
        {
            throw invalid_argument("Division by zero");
        }
        return Complex((real * b.real + imag * b.imag) / denom,
                       (imag * b.real - real * b.imag) / denom);
    }

    // 复数共轭
    Complex conjugate() const
    {
        return Complex(real, -imag);
    }

    // 打印复数
    void print() const
    {
        cout << real;
        if (imag > 0)
        {
            cout << " + " << imag << "i";
        }
        else if (imag < 0)
        {
            cout << " - " << -imag << "i";
        }
        // 如果虚部为0，不输出任何内容
    }
};

int main()
{
    // 测试数据
    Complex data[5][2] = {
        {Complex(0, 0), Complex(0, 0)},
        {Complex(3.1, 0), Complex(4.22, 8.9)},
        {Complex(-1.33, 2.34), Complex(0.1, -6.5)},
        {Complex(0, 9.7), Complex(-2.1, -9.7)},
        {Complex(7.7, -8), Complex(-7.7, 0)}};

    // 对每对数据进行运算
    for (int i = 0; i < 5; ++i)
    {
        Complex a = data[i][0];
        Complex b = data[i][1];

        // 求和
        cout << "Test case " << (i + 1) << ": " << endl
             << "a = ";
        a.print();
        cout << ", b = ";
        b.print();
        cout << endl;
        cout << "a的实部为：" << a.real << "，虚部为：" << a.imag << endl;
        cout << "b的实部为：" << b.real << "，虚部为：" << b.imag << endl;
        cout << endl;

        cout << "a + b = ";
        (a + b).print();
        cout << endl;

        // 求差
        cout << "a - b = ";
        (a - b).print();
        cout << endl;

        // 求积
        cout << "a * b = ";
        (a * b).print();
        cout << endl;

        // 求商
        try
        {
            cout << "a / b = ";
            (a / b).print();
            cout << endl;
        }
        catch (const invalid_argument &e)
        {
            cout << "错误！0不能作为除数！" << endl;
        }

        // 求共轭
        cout << "a的共轭 = ";
        a.conjugate().print();
        cout << endl;

        cout << "b的共轭 = ";
        b.conjugate().print();
        cout << endl;

        cout << "---------------------------------" << endl;
    }

    return 0;
}