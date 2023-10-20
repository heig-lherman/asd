//IN (1+((2+3)*(4*5)))
//IN ( 1 + ( (2 + 3) * ( 4 * 5 ) ) )
//IN ( 100 + ( (21 + 32) * ( 42 * 5 ) ) )
//IN ( 1 - ( (2 + 0) * ( 4 * 52 ) ) )
//IN ( ( ( 33 / 12 ) * ( 12 * 4 ) ) - ( ( 42 * 5 ) + ( 5 + 3) ) )
//IN ( 1044 % ( (2 + 3) * ( 25 / 4 ) ) )
//IN (1+((2+3)*(4*5))
//IN (+3)
//IN (2//3)

#include "evaluator.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    cout << "Quelle expression voulez-vous évaluer ? \n";
    string expression;
    getline(cin, expression);

    try {
        cout << expression << " = " << evalue(expression) << "\n";
    } catch( bad_expression ) {
        cout << "Bad expression \n";
    }
}
