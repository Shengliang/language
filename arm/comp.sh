# Download gcc-linaro-6.2.1-2016.11-i686_aarch64-linux-gnu
# https://releases.linaro.org/components/toolchain/binaries/latest/aarch64-linux-gnu/
aarch64-linux-gnu-gcc -O3 -DATOMIC -S a.c -o a.atomic.s  
aarch64-linux-gnu-gcc -O3 -S a.c -o a.non_atomic.s
