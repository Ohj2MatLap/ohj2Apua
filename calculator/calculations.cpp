// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double potens(double left, double right){
    double amount = 1;
    double score = left;
    while(amount<right){
        amount++;
        score=score*left;
    }
    return score;
}
