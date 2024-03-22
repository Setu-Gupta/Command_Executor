This library provides two APIs to execute commands on the shell from C++.

# How to use
  1. Include the header into you code.
  2. Use the `exec` API directly for synchronous calls, else create an object of `async_proc` class. For the latter case, call `get()` to retrieve the output (`stdout`) of the command.
  Refer to the test case for more details

# API details
  1. `aync_proc<N>(std::string&& cmd)`:
     Constructor for the `async_proc`. `N` is the buffer size (number of characters) for temporarily holding the output. `cmd` is the command to be executed.
  
  2. `std::string async_proc::get`:
     Wait for `cmd` to finish executing and return the output as a string.
       
  3. `std::string exec(std::string&& cmd)`:
      Run `cmd` synchronously and return the output as a string.
