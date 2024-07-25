// Type your code here, or load an example.
#include <iostream>

struct Val
{

    Val(const Val& r) 
    {
        num = r.num;
        std::cout << "COPY Constructing with value " << r.num << " at: " << this  <<  std::endl;
    };

    Val(Val&& r) 
    {
        num = r.num;
        std::cout << "MOVE Constructing with value " << r.num << " at: " << this  <<  std::endl;
        r.num=0;
    };


    Val(int num) : num(num)
    {
        std::cout << "Constructing with value " << num << " at: " << this  <<  std::endl;
    };

    ~Val()
    {
        std::cout << "Destructing with value " << num  << " at: " << this  <<  std::endl;
    }

    int num;
};

const Val& ConstLvalRefParameterReturnParameter(const Val &val)
{
    std::cout<< "Enter ConstLvalRefParameterReturnParameter" <<std::endl;
    return val;
}

//Nothing to see here
Val&& RvalRefParameterReturnRVal(Val&& val)
{
    std::cout<< "Enter RvalRefParameterReturnRVal" <<std::endl;
    return std::move(val);
}

//Nothing to see here
Val&& LvalRefParameterReturnRVal(Val& val)
{
    std::cout<< "Enter ConstLvalRefParameterReturnRVal" <<std::endl;
    return std::move(val);
}

// BAD temp var bound to a ref
Val&& ReturnTempRvalRef(int i)
{
    std::cout<< "Enter ReturnTempRvalRef" <<std::endl;
    return Val{i};
}


const Val&& ReturnTempConstRvalRef(int i)
{
    std::cout<< "Enter ReturnTempConstRvalRef" <<std::endl;
    return Val{i};
}


// Here is the real question 
const Val& ReturnTempConstLValRef(int i)
{
    std::cout<< "Enter ReturnTempConstLValRef" <<std::endl;
    return Val{i};
}


int main()
{
    int i = 1;
    // Bind a temp to LVal
    const Val &foo{i};

    // Bind a temp to RVal
    const Val&& rvaL{++i};

    std::cout<< "const Vals created" << std::endl;

    // testfunc argument bound to temp thows away
    const Val& test_foo = ConstLvalRefParameterReturnParameter(++i);
    std::cout<< "Return ConstLvalRefParameterReturnParameter" << std::endl;

    // testfunc argument bound to temp returns try saving to local const lval  ref
    const Val& const_lval_foo2 = RvalRefParameterReturnRVal(++i);
    std::cout<< "Return testFunc store const_lval_foo2" << std::endl;

    // argument bound to temp returns try saving to local const lval  ref
    const Val& foo2{++i};
    std::cout<< "Create temp foo2" << std::endl;
    const Val& const_lval_foo3 = LvalRefParameterReturnRVal( const_cast<Val&>(foo2) );
    std::cout<< "Return LvalRefParameterReturnRVal store const_lval_foo3" << std::endl;

    // BAD temp var bound to a ref
    Val&& rval_foo4 = ReturnTempRvalRef(++i);
    std::cout<< "Return ReturnTempRvalRef  store to rval rval_foo4" << std::endl;

    const Val&& const_rval_foo4 = ReturnTempRvalRef(++i);
    std::cout<< "Return ReturnTempRvalRef  store to const rval const_rval_foo4" << std::endl;

    const Val& const_lval_foo4 = ReturnTempRvalRef(++i);
    std::cout<< "Return ReturnTempRvalRef store to const lval const_lval_foo4" << std::endl;

    // error: cannot bind rvalue reference of type 'Val&&' to lvalue of type 'const Val'     
    // Val&& rval_foo5 = ReturnTempConstLValRef(++i);
    // std::cout<< "Return ReturnTempConstLValRef store to rval rval_foo3" << std::endl;

    const Val& const_lval_foo5 = ReturnTempConstLValRef(++i);
    std::cout<< "Return ReturnTempConstLValRef store to rval const_lval_foo5" << std::endl;

    // error: cannot bind rvalue reference of type 'const Val&&' to lvalue of type 'const Val'
    // const Val&& const_rval_foo5 = ReturnTempConstLValRef(++i);
    // std::cout<< "Return ReturnTempConstLValRef store to rval const_rval_foo5" << std::endl;

    std::cout << foo.num              << std::endl;
    std::cout << rvaL.num             << std::endl;
    std::cout << test_foo.num         << std::endl;
    std::cout << const_lval_foo2.num  << std::endl; 
    std::cout << foo2.num             << std::endl;
    std::cout << const_lval_foo3.num  << std::endl;
//    std::cout << rval_foo4.num        << std::endl;
//    std::cout << const_rval_foo4.num  << std::endl;
//    std::cout << const_lval_foo4.num  << std::endl;
//    std::cout << const_lval_foo5 .num << std::endl;


    std::cout<< "Return from main" << std::endl;
    return 0;
}

/*


C++

C++
152153148149150151146147142143144145140141138139134135136137132133129130131127128125126123124121122154155156157158159160161162119120117118115116
    // std::cout<< "Return ReturnTempConstLValRef store to rval const_rval_foo5" << std::endl;

    std::cout << foo.num              << std::endl;
    std::cout << rvaL.num             << std::endl;
    std::cout << test_foo.num         << std::endl;
    std::cout << const_lval_foo2.num  << std::endl; 
    std::cout << foo2.num             << std::endl;
    std::cout << const_lval_foo3.num  << std::endl;
//    std::cout << rval_foo4.num        << std::endl;
//    std::cout << const_rval_foo4.num  << std::endl;

ReturnTempConstLValRef
3 of 8

x86-64 gcc 14.1
x86-64 gcc 14.1
-std=c++20
12345678910111213141516171819202122232425262728293031323334353637383940414243
.LC0:
        .string "Constructing with value "
.LC1:
        .string " at: "
Val::Val(int) [base object constructor]:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     QWORD PTR [rbp-8], rdi
        mov     DWORD PTR [rbp-12], esi

x86-64 gcc 14.1 - cached (223209B) ~13541 lines filtered
<source>: In function 'Val&& ReturnTempRvalRef(int)':
<source>:58:12: warning: returning reference to temporary [-Wreturn-local-addr]
   58 |     return Val{i};
      |            ^~~~~~
<source>: In function 'const Val&& ReturnTempConstRvalRef(int)':
<source>:65:12: warning: returning reference to temporary [-Wreturn-local-addr]
   65 |     return Val{i};
      |            ^~~~~~
<source>: In function 'const Val& ReturnTempConstLValRef(int)':
<source>:73:12: warning: returning reference to temporary [-Wreturn-local-addr]
   73 |     return Val{i};
      |            ^~~~~~
ASM generation compiler returned: 0
<source>: In function 'Val&& ReturnTempRvalRef(int)':
<source>:58:12: warning: returning reference to temporary [-Wreturn-local-addr]
   58 |     return Val{i};
      |            ^~~~~~
<source>: In function 'const Val&& ReturnTempConstRvalRef(int)':
<source>:65:12: warning: returning reference to temporary [-Wreturn-local-addr]
   65 |     return Val{i};
      |            ^~~~~~
<source>: In function 'const Val& ReturnTempConstLValRef(int)':
<source>:73:12: warning: returning reference to temporary [-Wreturn-local-addr]
   73 |     return Val{i};
      |            ^~~~~~
Execution build compiler returned: 0
Program returned: 0
Constructing with value 1 at: 0x7ffedfc597fc
Constructing with value 2 at: 0x7ffedfc597f8
const Vals created
Constructing with value 3 at: 0x7ffedfc59800
Enter ConstLvalRefParameterReturnParameter
Destructing with value 3 at: 0x7ffedfc59800
Return ConstLvalRefParameterReturnParameter
Constructing with value 4 at: 0x7ffedfc59804
Enter RvalRefParameterReturnRVal
Destructing with value 4 at: 0x7ffedfc59804
Return testFunc store const_lval_foo2
Constructing with value 5 at: 0x7ffedfc597f4
Create temp foo2
Enter ConstLvalRefParameterReturnRVal
Return LvalRefParameterReturnRVal store const_lval_foo3
Enter ReturnTempRvalRef
Constructing with value 6 at: 0x7ffedfc597cc
Destructing with value 6 at: 0x7ffedfc597cc
Return ReturnTempRvalRef  store to rval rval_foo4
Enter ReturnTempRvalRef
Constructing with value 7 at: 0x7ffedfc597cc
Destructing with value 7 at: 0x7ffedfc597cc
Return ReturnTempRvalRef  store to const rval const_rval_foo4
Enter ReturnTempRvalRef
Constructing with value 8 at: 0x7ffedfc597cc
Destructing with value 8 at: 0x7ffedfc597cc
Return ReturnTempRvalRef store to const lval const_lval_foo4
Enter ReturnTempConstLValRef
Constructing with value 9 at: 0x7ffedfc597cc
Destructing with value 9 at: 0x7ffedfc597cc
Return ReturnTempConstLValRef store to rval const_lval_foo5
1
2
3
4
5
5
Return from main
Destructing with value 5 at: 0x7ffedfc597f4
Destructing with value 2 at: 0x7ffedfc597f8
Destructing with value 1 at: 0x7ffedfc597fc

*/