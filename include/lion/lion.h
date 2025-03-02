#ifndef LION_H
#define LION_H

#include <iostream>

#include "animal.h"

class Lion : public Animal {
    public:
        Lion() = default;
        void make_sound() const override;
        std::string name() const override;

        typedef std::unique_ptr<Lion> Ptr;
        static Ptr create() { return std::make_unique<Lion>(); }
};


#endif // LION_H