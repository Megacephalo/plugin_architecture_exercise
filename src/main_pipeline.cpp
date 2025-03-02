
#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include <string>
#include <dlfcn.h>
#include "plugin_core.h"

#include "animal.h"

Animal::Ptr load_animal(const std::string& animalLib, DLibHandle& pluginHandle);


std::string print_usage(const std::string& program_name) {
    std::stringstream stst;
    stst << "Usage: " << program_name << " <config_file>" << std::endl;
    return stst.str();
}

int main(int argc, char** argv) {
    std::cout << "Launching main pipeline" << std::endl;

    if (argc != 2) {
        std::cerr << print_usage( std::string(argv[0]) ) << std::endl;
        return EXIT_FAILURE;
    }

    // check if the config file exists
    std::filesystem::path config_file(argv[1]); 
    if (not std::filesystem::exists(config_file)) {
        std::cerr << "Config file does not exist: " << config_file << std::endl;
        return EXIT_FAILURE;
    }

    if (config_file.extension() != ".yaml") {
        std::cerr << "Config file must have a .yaml extension" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Loading config file: " << config_file << std::endl;
    YAML::Node config = YAML::LoadFile(config_file.string());
    
    std::string animalLib = config["animal_library"].as<std::string>();
    DLibHandle pluginHandle = nullptr;
    Animal::Ptr animal = load_animal(animalLib, pluginHandle);

    if (animal == nullptr) {
        std::cerr << "Failed to load animal" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Animal loaded: " << animal->name() << "  ";
    animal->make_sound();
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

Animal::Ptr load_animal(const std::string& animalLib, DLibHandle& pluginHandle) {
    pluginHandle = DLibHandle(dlopen(animalLib.c_str(), RTLD_NOW));
    if (pluginHandle == nullptr) {
        std::cerr << "Failed to open library: " << dlerror() << std::endl;
        return nullptr;
    }

    typedef Animal::Ptr (*create_animal_t)();
    create_animal_t create_animal = nullptr;
    create_animal = reinterpret_cast<create_animal_t>(dlsym(pluginHandle.get(), "create_animal"));

    if (create_animal == nullptr) {
        std::cerr << "Failed to find create_animal symbol" << std::endl;
        return nullptr;
    }

    return create_animal();
    
}