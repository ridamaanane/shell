#include "pipe_executor.h"

int count_cmds(t_cmd *cmd)
{
    int count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return count;
}

int *create_pipes(t_cmd *cmd)
{
    int nb_cmd = count_cmds(cmd);
    int nb_pipes = nb_cmd - 1;
    int *pipes = malloc(sizeof(int) * nb_pipes * 2); //2 mean read and write
    if (!pipes)
        return (NULL);

    int i = 0;
    while (i < nb_pipes)
    {
        if (pipe(&pipes[i * 2]) < 0)
        {
            perror("pipe failed");
            free(pipes);
            return NULL;
        }
        i++;
    }
    return (pipes);
}
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
void close_pipe_and_wait(int nb_cmds, int nb_pipes, int *pipes)
{
    // parent: close pipes
    int i = 0;
    while (i < nb_pipes * 2)
    {
        close(pipes[i]);
        i++;
    }

    // wait all children
    int j = 0;
    while (j < nb_cmds)
    {
        wait(NULL);
        j++;
    }
    free(pipes); //7it deja allocinahom fcreate pipes
}
void pipe_executor(t_cmd *cmd, char **envp)
{
    int nb_cmds = count_cmds(cmd);
    int nb_pipes = nb_cmds - 1;
    int *pipes = create_pipes(cmd);
    if (!pipes)
    {
        perror("failed to create pipes");
        return;
    }
    t_cmd *temp;
    int i = 0;
    int j = 0;

    temp = cmd;
    while (temp)
    {
        pid_t pid = fork();
        char *path = get_cmd_path(temp->argv[0]);
        if (pid == 0)
        {
            if (i != 0)
                dup2(pipes[(i - 1) * 2], STDIN_FILENO); //(STDIN Mean read end dial prev pipe)
            if (temp->next)
                dup2(pipes[i * 2 + 1], STDOUT_FILENO);
            while (j < nb_pipes * 2)
            {
                close(pipes[j]);
                j++;
            }
            if (!path)
            {
                printf("%s: command not found\n", temp->argv[0]);
                exit(127);
            }
            execve(path, temp->argv, envp); //temp->argv = { "ls", "-l", NULL }
            perror("execve failed");
            exit(127); //command not found
            
        }
        else if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }
        temp = temp->next;
        i++;
    }
    close_pipe_and_wait(nb_cmds, nb_pipes, pipes);
}


int main(int argc, char **argv, char **envp)
{
    (void)argc;  // mask unused warnings
    (void)argv;

    // Build t_cmd list: ls -l | wc -l | cat
    t_cmd cmd1, cmd2, cmd3;

    char *args1[] = {"ls", "-l", NULL};
    char *args2[] = {"wc", "-l", NULL};
    char *args3[] = {"cat", NULL};

    cmd1.argv = args1;
    cmd1.next = &cmd2;

    cmd2.argv = args2;
    cmd2.next = &cmd3;

    cmd3.argv = args3;
    cmd3.next = NULL;

    pipe_executor(&cmd1, envp); 
    // ✅ envp = environment variables dyal process
    // ✅ lfa2ida:
    
    // bach command ywarath environment dyal terminal dyalek (ex: PATH, HOME...)
    
    // ✅ ila madirtich envp → cmd mayla9ach PATH → maykhdemch
    
    // 💡 yes: envp katsowb bach cmd ykhdm f nafs environment dyal terminal dyalek


    return 0;
}

