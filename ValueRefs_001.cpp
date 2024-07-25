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
    Val&& rval_foo = ReturnTempRvalRef(++i);
    std::cout<< "Return ReturnTempRvalRef  store to rval" << std::endl;

    const Val&& const_rval_foo = ReturnTempRvalRef(++i);
    std::cout<< "Return ReturnTempRvalRef  store to const rval const_rval_foo" << std::endl;

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

    std::cout<< "Return from main" << std::endl;
    return 0;
}