/*
 * Install ARM gcc on MAC.
 * https://gist.github.com/joegoggins/7763637
 * Step 1 - Install Homebrew
 * http://brew.sh/
 * Step 2 - Install GCC Arm Toolchain
 * brew tap PX4/homebrew-px4
 * brew update
 * Brew search gcc-arm-none-eabi
 * brew install gcc-arm-none-eabi-62
 * arm-none-eabi-gcc -S -O3 clock.c
 */
volatile int reg = 0;

void clock()
{
   volatile int * p = & reg;

   // asm volatile ("mfence" ::: "memory");
   // __sync_synchronize();

   asm volatile ("#Start");
   while (1) {
      *p = 1;
       //__sync_synchronize();
      *p = 0;
       //__sync_synchronize();
   } 
   asm volatile ("#End");
}
