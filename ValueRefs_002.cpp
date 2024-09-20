/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

int&& func()
{
    return 42;
}

void  funcP(int&& foo)
{
    std::cout << "funcP Foo 1st " <<  foo << "\n";
    foo = 55;
    std::cout << "funcP Foo 2nd " <<  foo << "\n";
}


int main()
{
    funcP(50);
    try
    {
        int foo =  func();
    
        std::cout << "Foo 1st " <<  foo << "\n";
        foo = 4;
        std::cout << "Foo 2nd " <<  foo << "\n";
    }
    catch(std::exception & e)
    {
        std::cerr<< "err:" << e.what() << "\n";   
    }
    return 0;
}