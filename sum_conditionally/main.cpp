#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif
unsigned int divisible_by_3_or_7(unsigned int nb)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------


    // Add your implementation here

    if(nb%3==0 || nb%7==0){
        if(nb==0){return nb;}
        return nb+divisible_by_3_or_7(nb-1);
    }
    else{
        if(nb==0){return 0;}
        return divisible_by_3_or_7(nb-1);
    }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int upper_bound;
    std::cout << "Enter an upper bound: ";
    std::cin >> upper_bound;
    std::cout << "Sum of non-negative integers between 0 and " << upper_bound << " and divisible by 3 or 7 is " << divisible_by_3_or_7(upper_bound) << std::endl;
    return EXIT_SUCCESS;
}
#endif
