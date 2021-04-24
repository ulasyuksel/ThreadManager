#include <iostream>
#include <sstream>
#include <string>

#include "ThreadManager.hpp"


static const std::string STATUS_KEY("status");
static const std::string ABORT_KEY("abort");
static const std::string START_KEY("start");
static const std::string PAUSE_KEY("pause");
static const std::string RESUME_KEY("resume");
static const std::string QUIT_KEY("quit");


static const std::string RENDER_COMMAND_LIST =
"##############################################################################\n"
"Enter command: \n"
"* status – returns ids and status of all registered jobs.\n"
"*       The job status can be one of the following: idle/running/paused/aborted\n"
"* start <id> - starts job with the given id \n"
"* abort <id> - aborts execution of a job with the given id \n"
"* pause <id> - halts execution of a job with the given id \n"
"* resume <id> - resumes execution of a halted job \n"
"* quit – aborts all running jobs and quits the application\n"
"##############################################################################\n";


static void usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)>"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-N <# of thread>, #number of threads to be created greater than zero"
              << std::endl;
}


int main(int argc, char **argv)
{
    int return_val = 1;
    if (argc == 2)
    {
        const std::string arg1(argv[1]);
        if (arg1 == "-h" || arg1 == "--help")
        {
            usage(argv[0]);
            return_val = 0;
        }


    }
    else if (argc == 3)
    {
        const std::string arg1(argv[1]);
        if (arg1 == "-N")
        {
            std::stringstream convert{ argv[2] };

            unsigned int number_of_threads;
            if (!(convert >> number_of_threads))
            {
                return_val = 1;
            }
            else if (number_of_threads > 0) // at least 1 thread should be created
            {
                return_val = 0;
                std::cout << "Creating " << number_of_threads << " threads\n";
                std::string in_command;
                ThreadManager my_local_thread_manager(number_of_threads);

                while (true)
                {
                    std::cout << RENDER_COMMAND_LIST;
                    getline (std::cin,in_command);

                    if(in_command.find(QUIT_KEY) == 0)
                    {
                        std::cout << "quit" << std::endl;
                        break;
                    }
                    else
                    {
                        unsigned int thread_id;
                        std::size_t pos = in_command.find(" ");
                        if (pos != std::string::npos)
                        {
                            std::string id_str = in_command.substr (pos);
                            std::stringstream string_convert{ id_str };
                            if (!(string_convert >> thread_id))
                            {
                                std::cout << "wrong command format" << std::endl;
                            }
                            else
                            {
                                // Check the command which has to be run.
                                if (in_command.find(STATUS_KEY) == 0)
                                {
                                    std::cout << STATUS_KEY << ": " << thread_id << " --> " << threadStateToString(my_local_thread_manager.status(thread_id)) << std::endl;
                                }
                                else if(in_command.find(START_KEY) == 0)
                                {
                                    std::cout << START_KEY << ": " << thread_id << std::endl;
                                    my_local_thread_manager.start(thread_id);
                                }
                                else if(in_command.find(ABORT_KEY) == 0)
                                {
                                    std::cout << ABORT_KEY << ": " << thread_id << std::endl;
                                    my_local_thread_manager.abort(thread_id);
                                }
                                else if(in_command.find(PAUSE_KEY) == 0)
                                {
                                    std::cout << PAUSE_KEY << ": " << thread_id << std::endl;
                                    my_local_thread_manager.pause(thread_id);
                                }
                                else if(in_command.find(RESUME_KEY) == 0)
                                {
                                    std::cout << RESUME_KEY << ": " << thread_id << std::endl;
                                    my_local_thread_manager.resume(thread_id);
                                }
                                else
                                {
                                    std::cout << "wrong command format" << std::endl;
                                }
                            }
                        }
                        else
                        {
                            std::cout << "wrong command format" << std::endl;
                        }
                    }
                }
            }
        }

    }

    if (return_val != 0)
    {
        usage(argv[0]);
    }
    return return_val;
}
