#include "Common.h"
#include "CourseSystem.h"

int main() {
    try { CourseSystem system; system.menu(); }
    catch(const exception& e) { cerr<<"Unexpected error: "<<e.what()<<"\n"; return 1; }
    return 0;
}
