#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include "toml.hpp"

template<typename T>
void fuzz_toml_find(const toml::value &toml_data, FuzzedDataProvider &fdp) {
    try {
        toml::find<T>(toml_data, fdp.ConsumeRandomLengthString());
    } catch (const std::out_of_range &) {}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fdp{data, size};
  try {
      std::stringstream ss;
      ss << fdp.ConsumeRandomLengthString();
      auto toml_data = toml::parse(ss);

      auto action = fdp.ConsumeIntegralInRange(0, 7);

      switch(action) {
          case 0:
                fuzz_toml_find<std::string>(toml_data, fdp);
                break;
            case 1:
                fuzz_toml_find<std::int64_t>(toml_data, fdp);
                break;
            case 2:
                fuzz_toml_find<double>(toml_data, fdp);
                break;
            case 3:
                fuzz_toml_find<bool>(toml_data, fdp);
                break;
            case 4:
                fuzz_toml_find<std::vector<int>>(toml_data, fdp);
                break;
            case 5:
                fuzz_toml_find<std::size_t>(toml_data, fdp);
                break;
          case 6:
              toml::visit([](const auto& val) -> void {
              }, toml_data);
              break;
          case 7:
              toml_data.as_table();
            default:
                break;
      }

  } catch (const toml::exception &) {
      return -1;
  } catch (const std::out_of_range & e) {
      if (std::string(e.what()).find("key") != std::string::npos)
          return -1;
      throw e;
  }
  return 0;
}