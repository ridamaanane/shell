#include "minishell.h"
void free_split_content(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
        free(array[i++]);
    free(array);
}
char *get_cmd_path(char *cmd)
{
    int i;
    char *chunk;
    char *full_path;
    char **paths;
    
    paths = ft_split(getenv("PATH"), ':');
    full_path = NULL;
    i = 0;
    while (paths && paths[i])
    {
        chunk = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(chunk, cmd);
        free(chunk);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        i++;
    }
    free_split_content(paths);
    return (full_path);
}

void execute_external(char *cmd, char **env)
{
    char *found_path = NULL;
    pid_t pid;

    found_path = get_cmd_path(cmd);
    if (found_path)
    {
        pid = fork();
        char *args[] = {cmd, NULL};
        if (pid == 0) //child process success
        {
            execve(found_path, args, env); //hna machi darori dir if statemn because howa la kan match kaydkhel okaydir khdmto  (replaces the current process with a new program)
            perror("execve failed");
            exit(127);
        }
        else if (pid > 0)
            waitpid(pid, NULL, 0); //bghinah ytsena child osf without specifie chi haaja
        else
            perror("fork failed");
        free(found_path);  
    }
    else
        printf("%s: command not found\n", cmd);
}

int main(int argc, char **argv, char **envp)
{
    (void) argc;

    execute_external(argv[1], envp);
}



