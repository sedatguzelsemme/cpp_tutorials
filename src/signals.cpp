#include <csignal>
#include <cstdlib> // for  exit()
#include <iostream>
#include <unistd.h> // getpid()

void SIGSEGV_Handler(int signum) {
  std::cout << "oh my god! segmenation fault happened" << std::endl;
  printf("Process %d got signal %d\n", getpid(), signum);
  // kill(getpid(), signum);
  exit(signum);
}

void SIGINT_Handler(int signum) {
  std::cout << "Interrupt signal (" << signum << ") received.\n";
  // Cleanup and close up logic
  exit(signum);
}

sig_atomic_t s_value = 0;
void SIGTERM_Handler(int signum) { s_value = signum; }

int main() {
  // signal(SIGSEGV, SIGSEGV_Handler);
  // int *p;
  // *p = 10;

  // //  Register signal SIGINT and signal handler
  // signal(SIGINT, SIGINT_Handler);

  signal(SIGTERM, SIGTERM_Handler);
  std::cout << "Before called Signal = " << s_value << std::endl;
  raise(SIGTERM);
  std::cout << "After called Signal = " << s_value << std::endl;
}
