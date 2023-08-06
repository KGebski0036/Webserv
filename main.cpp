int main()
{
    if (pipe(pipefd) == -1) {
        return "";
    }

    pid_t pid = fork();

    if (pid == -1) {
        return "";
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end of the pipe

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Close the original write end of the pipe (no longer needed)
        close(pipefd[1]);

        // Execute the CGI script
        execl(, NULL);

        // execl should not return if successful
        std::cerr << "execl failed." << std::endl;
        _exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]); // Close write end of the pipe

        std::string output;
        char buffer[4096];
        int bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, bytesRead);
        }

        close(pipefd[0]); // Close read end of the pipe
        waitpid(pid, NULL, 0); // Wait for the child process to finish
        return output;
    }
	return 0;
}