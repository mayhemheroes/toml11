FROM --platform=linux/amd64 ubuntu:22.04 as builder

## Install build dependencies.
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y clang cmake make --no-install-recommends

## Add source code to the build stage.
ADD . /src


##build
WORKDIR /src/build
RUN cmake -DCMAKE_CXX_STANDARD=20 -Dtoml11_BUILD_FUZZER=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
RUN cmake --build .

## Package Stage
FROM --platform=linux/amd64 ubuntu:22.04
COPY --from=builder /src/build/mayhem/fuzz_toml /fuzz_toml

ENTRYPOINT []
CMD ["/fuzz_toml"]
