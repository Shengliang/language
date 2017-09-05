/* http://en.cppreference.com/w/cpp/atomic/memory_order */
#include<atomic>

std::atomic<int> clk = {0};
std::atomic<int> run_flag = {1};

volatile int reg = 0;

void clock_volatile()
{
   volatile int * clk = & reg;
   asm volatile ("# volatile int *");
   while (run_flag.load(std::memory_order_consume)) {
      *clk = 1;
      *clk = 0;
   } 
}

void clocksync()
{
   volatile int * clk = & reg;
   asm volatile ("# __sync_synchronize");
   while (run_flag.load(std::memory_order_consume)) {
      *clk = 1;
       __sync_synchronize();
      *clk = 0;
       __sync_synchronize();
   } 
}

void clock1()
{
   asm volatile ("# memory_order_release");
   while (run_flag.load(std::memory_order_consume)) {
      clk.store(1, std::memory_order_release);
      __sync_synchronize();
      clk.store(0, std::memory_order_release);
      __sync_synchronize();
   } 
}
void clock2()
{
   asm volatile ("# memory_order_release");
   while (run_flag.load(std::memory_order_consume)) {
      clk.store(1, std::memory_order_release);
      std::atomic_thread_fence(std::memory_order_release);
      clk.store(0, std::memory_order_release);
      std::atomic_thread_fence(std::memory_order_release);
   } 
}
void clock3()
{
   asm volatile ("# memory_order_relaxed");
   while (run_flag.load(std::memory_order_consume)) {
      clk.store(1, std::memory_order_relaxed);
      clk.store(0, std::memory_order_relaxed);
   } 
}
void clock4()
{
   asm volatile ("# memory_order_release");
   while (run_flag.load(std::memory_order_consume)) {
      clk.store(1, std::memory_order_release);
      clk.store(0, std::memory_order_release);
   } 
}
void clock5()
{
   asm volatile ("# memory_order_acq_rel");
   while (run_flag.load(std::memory_order_consume)) {
      clk.store(1, std::memory_order_acq_rel);
      std::atomic_thread_fence(std::memory_order_acq_rel);
      clk.store(0, std::memory_order_acq_rel);
      std::atomic_thread_fence(std::memory_order_acq_rel);
   } 
}
void clock6() // same as default clock7()
{
   asm volatile ("# memory_order_seq_cst");
   while (run_flag.load(std::memory_order_seq_cst)) {
      clk.store(1, std::memory_order_seq_cst);
      std::atomic_thread_fence(std::memory_order_seq_cst);
      clk.store(0, std::memory_order_seq_cst);
      std::atomic_thread_fence(std::memory_order_seq_cst);
   } 
}
void clock7()
{
   asm volatile ("# memory_order_seq_cst");
   while (run_flag) {
      clk = 1;
      std::atomic_thread_fence(std::memory_order_seq_cst);
      clk = 0;
      std::atomic_thread_fence(std::memory_order_seq_cst);
   } 
}
void clock0()
{
   asm volatile ("# atomic default");
   while (run_flag) {
      clk = 1;
      clk = 0; 
   } 
}

void func()
{	
   asm volatile ("# atomic_signal_fence(std::memory_order_seq_cst)");
      std::atomic_signal_fence(std::memory_order_seq_cst);
      std::atomic_thread_fence(std::memory_order_seq_cst);

   asm volatile ("# std::atomic_signal_fence(std::memory_order_acquire)");
      std::atomic_signal_fence(std::memory_order_acquire);
      std::atomic_thread_fence(std::memory_order_acquire);
}
int main(void){
   clock_volatile();
   return 0;
}
