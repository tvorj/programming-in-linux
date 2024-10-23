#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <string>
#include <fcntl.h>
#include <sys/wait.h>

void curDir2Path()
{
    char *curPath = getenv("PATH");
    if (curPath == NULL)
    {
        std::cerr << "error finding PATH" << std::endl;
        exit(errno);
    }
    char curDir[4096];
    if (getcwd(curDir, 4096) == NULL)
    {
        std::cerr << "error while getting current directory" << std::endl;
        exit(errno);
    }
    std::string newPath = std::string(curDir) + ":" + curPath;
    if (setenv("PATH", newPath.c_str(), 1) == -1)
    {
        std::cerr << "error while setting environment" << std::endl;
        exit(errno);
    }
}

std::vector<std::string> parsing(const std::string &str)
{
    std::vector<std::string> vec;
    std::string strstr;
    for (auto &i : str)
    {
        if (i == ' ')
        {
            if (!strstr.empty())
            {
                vec.push_back(strstr);
                strstr.clear();
            }
        }
        else
        {
            strstr += i;
        }
    }
    if (!strstr.empty())
    {
        vec.push_back(strstr);
    }
    return vec;
}

bool do_commands(const std::string &str, bool silent_mode)
{
    std::vector<std::string> vec = parsing(str);
    if (vec.empty())
    {
        return false;
    }
    bool append = false;
    auto it = vec.begin();
    // if we need to redirection then store the file name
    std::string redirto;
    while (it != vec.end())
    {
        if (*it == ">")
        {
            it = vec.erase(it);
            if (it != vec.end())
            {
                redirto = *it;
                it = vec.erase(it);
                append = false;
            }
            continue;
        }
        if (*it == ">>")
        {
            it = vec.erase(it);
            if (it != vec.end())
            {
                redirto = *it;
                it = vec.erase(it);
                append = true;
            }
            continue;
        }
        it++;
    }

    pid_t p = fork();
    if (p < 0)
    {
        std::cerr << "error while creating a child process" << std::endl;
        exit(errno);
    }
    if (p == 0)
    {
        if (silent_mode)
        {
            std::string log = std::to_string(getpid()) + ".log";
            int log_fd = open(log.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (log_fd < 0)
            {
                std::cerr << "error opening file " << std::endl;
                exit(errno);
            }
            dup2(log_fd, STDOUT_FILENO);
            dup2(log_fd, STDERR_FILENO);
            close(log_fd);
        }
        else if (!redirto.empty())
        {
            int fd;
            if (append)
            {
                fd = open(redirto.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
            }
            else
            {
                fd = open(redirto.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd < 0)
            {
                std::cerr << "error opening file " << std::endl;
                exit(errno);
            }
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }
        std::vector<char *> vecexec;
        for (auto &i : vec)
        {
            vecexec.push_back(&i[0]);
        }
        vecexec.push_back(nullptr);

        execvp(vecexec[0], vecexec.data());
        std::cerr << "error executing command " << std::endl;
        exit(errno);
    }
    else
    {
        int wait_status;
        if (wait(&wait_status) == -1)
        {
            std::cerr << "error while waiting" << std::endl;
            exit(errno);
        }
        return WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == 0;
    }
    return false;
}


void interactive_shell()
{
    bool stop = false;
    while (!stop)
    {
        std::string line;
        getline(std::cin, line);
        if (line.empty())
        {
            continue;
        }
        std::vector<std::string> vec = parsing(line);
        std::string str;
        bool prev = true;
        bool silent_mode = false;

        for (auto &i : vec)
        {
            if (i == "exit")
            {
                stop = true;
                break;
            }
            if (i == "silent")
            {
                silent_mode = true;
                continue;
            }
            if (i == "&&")
            {
                if (prev == true)
                {
                    prev = do_commands(str, silent_mode);
                }
                str.clear();
                silent_mode = false;
                continue;
            }
            if (i == "||")
            {
                if (prev == false)
                {
                    prev = do_commands(str, silent_mode);
                }
                str.clear();
                silent_mode = false;
                continue;
            }
            if (i == ";")
            {
                prev = do_commands(str, silent_mode);
                str.clear();
                silent_mode = false;
                continue;
            }
            str += i + " ";
        }
        if (!str.empty())
        {
            prev = do_commands(str, silent_mode);
        }
    }
}

int main()
{
    curDir2Path();
    interactive_shell();
    return 0;
}

