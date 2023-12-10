#include <iostream>
#include "Wrapper.h"
#include "Engine.h"
#include <array>

class Subject {
public:
    int f1(int a, int b) {
        return a + b;
    };

    int f2(int a) {
        return a * 2;
    };

    int f3(int a, int b) {
        return a * b;
    };

    int f4(int a, int b) {
        return a - b;
    }
};

int main() {
    Subject subj;

    Wrapper wrapper1(&subj, &Subject::f4, { {"arg1", 0}, {"arg2", 0} });
    Engine engine1;
   
    engine1.register_command(&wrapper1, "command1");

    std::cout << engine1.execute("command1", { {"arg2", 5}, {"arg1", 4} }) << std::endl;

    Wrapper wrapper2(&subj, &Subject::f1, { {"arg1", 0}, {"arg2", 0} });

    Engine engine2;

    engine2.register_command(&wrapper2, "command2");

    std::cout << engine2.execute("command2", { {"arg2", 5}, {"arg1", 4} }) << std::endl;
}