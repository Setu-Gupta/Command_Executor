// This code is stolen from https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
// This code is stolen from https://stackoverflow.com/questions/7686939/c-simple-return-value-from-stdthread

#include <array>
#include <cstdio>
#include <future>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>

template<int N = 128>
class async_proc
{
        private:
                std::promise<std::string> promise;
                std::thread               worker;

                std::string exec(const std::string&& cmd)
                {
                        std::array<char, N> output_buffer;
                        std::string         output;

                        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
                        if(!pipe)
                                throw std::runtime_error("Could not open pipe");

                        while(fgets(output_buffer.data(), N, pipe.get()) != nullptr) output += output_buffer.data();

                        return output;
                }

        public:
                async_proc(std::string&& cmd)
                {
                        this->worker = std::thread(
                                [cmd {std::move(cmd)}, this]()
                                {
                                        this->promise.set_value(this->exec(std::move(cmd)));
                                });
                }

                std::string get()
                {
                        this->worker.join();
                        return this->promise.get_future().get();
                }
};

template<int N = 128>
std::string exec(std::string&& cmd)
{
        std::array<char, N> output_buffer;
        std::string         output;

        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
        if(!pipe)
                throw std::runtime_error("Could not open pipe");

        while(fgets(output_buffer.data(), N, pipe.get()) != nullptr) output += output_buffer.data();

        return output;
}
