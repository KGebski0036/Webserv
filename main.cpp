#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {


    if (pipe(pipefd) == -1) {
        std::cerr << "Failed to create pipe." << std::endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Fork failed." << std::endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe

        // Execute the desired program (e.g., "ls" command)
	if (execl("/home/sztorm/webserv/www/cgi-bin/simple_cgi.sh", "simple_cgi.sh", NULL) == -1) {
		std::cerr << "execl failed: " << strerror(errno) << std::endl;
		return 1;
	}
    } else {
        // Parent process
        close(pipefd[1]); // Close the write end of the pipe
        wait(NULL); // Wait for the child process to finish

        // Read the output from the child process
        int bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);

        if (bytesRead == -1) {
            std::cerr << "Failed to read from the pipe." << std::endl;
            return 1;
        }

        // Null-terminate the buffer
        buffer[bytesRead] = '\0';

        // Revert back order of file descriptors
        dup2(1, pipefd[0]);

        // Print the output to the console
        std::cout << "Output from child process:\n" << buffer << std::endl;
    }
    return 0;
}
