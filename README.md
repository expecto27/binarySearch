


## Preinstall

For linux ubuntu

    sudo apt install python3
    pip install conan
    conan profile detect --force
    conan profile update settings.compiler.libcxx=libstdc++11 default
    conan config install https://github.com/conan-io/conan-extensions.git

## Build

    conan install . -of .build --build=missing
    cmake -H. -B.build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
    cmake --build .build
