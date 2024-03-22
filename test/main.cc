#include <executor.h>
#include <iostream>

int main()
{
        std::cout << exec("sleep 10; ls");
        std::cout << "Synchronous test" << std::endl;
        async_proc ap("sleep 10; ls");
        std::cout << "Asynchronous test" << std::endl;
        std::cout << ap.get();
}
