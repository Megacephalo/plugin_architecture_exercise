# Plugin Architecture Practice

This is a barebone implementation of a plugin architecture using modern C++. The implementation in this project address two key requirements:
- Cross-platform
- Safe memory management by using smart pointers instead of raw ones

This project serves as a supporting reference material for the article [How to create a memory safe cross platform plugin with C++](https://megacephalo.github.io/posts/area-software-design/how_to_reate_a_memory_safe_cross_platform_plugin/)

# How to install?

Assume you already place your current path to this project's root directory. Insert the following commands in your console:

```bash
# Get to the root directory of this project
cmake -DCMAKE_BUILD_TYPE=Release -B build
cmake --build build
```

or

```bash
mkdir build
cd build
cmake ..
make 
```

For subsequent compiling, just do:

```bash
cmake --build build
```

or

```bash
$ cd build
$ make
```

# How to run?

Assume you already place your current path to this project's root directory. Insert the following commands in your console:

```bash
cd bin
./main_pipeline <your YAML file>
```

This project comes with a example YAML file under `resources/` called `test_pipeline.yaml`. If you want to use that YAML file along with this program, insert the command:

```bash
cd bin/
./main_pipeline path/to/your/test_pipeline.yaml
```

Update to your YAML file path accordingly.

If the main program cannot find the plugin from the provided path in your provided YAML file, it will return with the following messages:

```shell
Launching main pipeline
Loading config file: "path/to/your/test_pipeline.yaml"
Failed to open library: path/you/specified/to/your/liblion.so: cannot open shared object file: No such file or directory
Failed to load animal
```

Otherwise you will see the following:

```shell
Launching main pipeline
Loading config file: "/home/charlyhuang/Documents/tech-blog-reference-source-codes/plugin_architecture_exercise/resources/test_pipeline.yaml"
Animal loaded: Lion  Roar!
```

Congratulations! You just succeeded in running a barebone plugin!


# Any suggestion, advice, question?

Please contact the author of this project:

- [Charly Huang](mailto:charly.charlongo@gmail.com)

Or simply file a ticket on this repo's GitHub issue page.

# Want to contribute?

You are more than welcome to contribute to this project. To do so, fork the project and start sending in PR.

# Legal notice

Not yet decided....Let's give it a BSD for now. :stuck_out_tongue_closed_eyes: