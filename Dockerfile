from debian:bullseye-slim

RUN apt-get update && apt-get install -y nasm cmake git gcc g++ pkg-config

RUN mkdir -p CameraLib/build && cd CameraLib

COPY . /CameraLib

RUN cd /CameraLib/build && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j$(nproc) 
