//FORBIDDEN cout
//FORBIDDEN cerr
//FORBIDDEN printf
//FORBIDDEN puts
//FORBIDDEN putchar
//FORBIDDEN putc
#include "util.h"
#include "c.h"

int cnt = 0; // utilisez cette variable globale

void f0() noexcept {
    enter("f0");
// AJOUTEZ VOTRE CODE ICI ...
    static C c1(++cnt);
    C c2(++cnt);
// ... FIN DE VOTRE CODE
    leave("f0");
}

C* f1() {
    enter("f1");
    C* p;
// AJOUTEZ VOTRE CODE ICI ...
    p = new C{++cnt};
// ... FIN DE VOTRE CODE
    leave("f1");
    return p;
}

C* f2() {
    enter("f2");
    C* p;
// AJOUTEZ VOTRE CODE ICI ...
    p = new C[2]{++cnt, ++cnt};
// ... FIN DE VOTRE CODE
    leave("f2");
    return p;
}

void f3(C* p) noexcept {
    enter("f3");
// AJOUTEZ VOTRE CODE ICI ...
    new(p) C{++cnt};
// ... FIN DE VOTRE CODE
    leave("f3");
}

void f4(C* p, size_t n) noexcept {
    enter("f4");
// AJOUTEZ VOTRE CODE ICI ...
    for (size_t i = 0; i < n; ++i) {
        new(p + i) C{++cnt};
    }
// ... FIN DE VOTRE CODE
    leave("f4");
}

int main() {
    enter("main");
// AJOUTEZ VOTRE CODE ICI ...
    C c1(++cnt);

    f0();
    f0();

    C *c2 = f1();
    C *c3 = f2();

    C *p1 = (C *) ::operator new(sizeof(C) * 4);
    f3((C *) p1);

    delete[] c3;
    delete c2;

    f4(p1 + 1, 2);

    p1->~C();

    f4(p1 + 3, 1);

    for (size_t i = 1; i < 4; ++i) {
        p1[i].~C();
    }
    ::operator delete(p1, sizeof(C) * 4);
// ... FIN DE VOTRE CODE
    leave("main");
}
