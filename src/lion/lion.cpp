#include "lion/lion.h"   

void Lion::make_sound() const {
    std::cout << "Roar!" << std::endl;
}

std::string Lion::name() const {
    return "Lion";
}

extern "C" Animal::Ptr create_animal() {
    return Lion::create();
}