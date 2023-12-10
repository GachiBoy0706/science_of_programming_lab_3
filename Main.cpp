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

    Wrapper wrapper(&subj, &Subject::f4, { {"arg1", 0}, {"arg2", 0} });
    Engine engine;

    engine.register_command(&wrapper, "command1");

    std::cout << engine.execute("command1", { {"arg2", 5}, {"arg1", 4} }) << std::endl;

}