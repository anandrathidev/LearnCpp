/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

// Example program
#include <iostream>
#include <string>
#include <semaphore>
#include <memory>
 
using Sem = std::counting_semaphore<256>;
struct SemReleaser 
{
    bool operator()(Sem *s) const 
    { 
        std::cout << "\nTry  release() SemReleaser \n ";
        s->release(); 
        std::cout << "SemReleaser release() OK\n ";
        return true;
    }
};

class AnonymousTokenPool 
{
    public:
    Sem sem_{20};
    using Token = std::unique_ptr<Sem, SemReleaser>;
    
    Token borrowToken() 
    {
        std::cout << "borrowToken() may block \n";
        sem_.acquire(); // may block
        std::cout << "Return Token  \n";
        return Token(&sem_);
    }
};

int main()
{
  AnonymousTokenPool pool ;
  {
    std::cout << "t1  \n";
    AnonymousTokenPool::Token& t1 = pool.borrowToken() ;
    /*
    std::cout << "t2  \n";
    AnonymousTokenPool::Token t2 = pool.borrowToken() ;
    std::cout << "t3  \n";
    AnonymousTokenPool::Token t3 = pool.borrowToken() ;
    */
  }
  if(0)
  {
    std::cout << "new block  \n";
    std::cout << "t11  \n";
    AnonymousTokenPool::Token t11 = pool.borrowToken() ;
    std::cout << "t12  \n";
    AnonymousTokenPool::Token t12 = pool.borrowToken() ;
  }
  
  std::cout << "End Return Main \n";
  return 0;

}