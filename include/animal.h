#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <memory>

#if defined(_MSC_VER)
    #define ANIMAL_EXPORT __declspec(dllexport)
    #define ANIMAL_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    #define ANIMAL_EXPORT __attribute__((visibility("default")))
    #define ANIMAL_IMPORT __attribute__((visibility("default")))
#else
    #define ANIMAL_EXPORT
    #define ANIMAL_IMPORT
#endif

#ifdef BUILDING_ANIMAL
    #define ANIMAL_API ANIMAL_EXPORT
#else
    #define ANIMAL_API ANIMAL_IMPORT
#endif

class ANIMAL_API Animal {
    public:
        Animal() = default;
        virtual ~Animal() = default;
        virtual void make_sound() const = 0;
        virtual std::string name() const = 0;
    
        typedef std::unique_ptr<Animal> Ptr;
};

extern "C" ANIMAL_API Animal::Ptr create_animal();

#endif // ANIMAL_H
