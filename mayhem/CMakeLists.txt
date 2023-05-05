add_executable(fuzz_toml fuzz_toml.cpp)

target_compile_options(fuzz_toml PUBLIC -fsanitize=fuzzer,address,undefined)
target_link_options(fuzz_toml PUBLIC -fsanitize=fuzzer,address,undefined)

target_link_libraries(fuzz_toml PUBLIC toml11)