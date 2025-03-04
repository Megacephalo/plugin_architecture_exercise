#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include <string>
#include <ltdl.h>
#include <memory>

#include "animal.h"

namespace fs = std::filesystem;

Animal::Ptr load_animal(std::string animalLib, lt_dlhandle& pluginHandle);


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

    /* initializing ltdl */
    if (lt_dlinit() != 0) {
        std::cerr << " Error initializing libltdl: " << lt_dlerror() << std::endl;
        return EXIT_FAILURE;
    }

    lt_dlhandle pluginHandle = nullptr;
    Animal::Ptr animal = load_animal(animalLib, pluginHandle);

    std::cout << "Animal loaded: " << animal->name() << " makes the sound: ";
    animal->make_sound();
    
    std::cout << std::endl;

    animal.reset();
    if (pluginHandle != nullptr)  lt_dlclose(pluginHandle);
    lt_dlexit();

    return EXIT_SUCCESS;
}

Animal::Ptr load_animal(std::string animalLib, lt_dlhandle& pluginHandle) {
    if (not fs::exists(fs::path(animalLib)) ) {
        std::cerr << "The provided library: " << animalLib << " NOT found." << std::endl;
        return nullptr;
    }
    animalLib = fs::canonical(animalLib).string();
    std::cout << "Loading in plugin from " << animalLib << std::endl;

    pluginHandle = lt_dlopenext(animalLib.c_str());
    if (pluginHandle == nullptr) {
        std::cerr << "Error loading plugin: " << lt_dlerror() << std::endl;
        return nullptr;
    }

    // Create the plugin function
    void* sym = lt_dlsym(pluginHandle, "create_animal");
    if (sym == nullptr) {
        std::cerr << "Error loading symbol: " << lt_dlerror() << std::endl;
        lt_dlclose(pluginHandle);
        return nullptr;
    }

    // Cast to function pointer type
    using CreateAnimal_t = Animal::Ptr (*)();
    auto create_animal = reinterpret_cast<CreateAnimal_t>(sym);
    if (create_animal == nullptr) {
        std::cerr << "Error loading symbol: " << lt_dlerror() << std::endl;
        lt_dlclose(pluginHandle);
        return nullptr;
    }

    return create_animal();
}