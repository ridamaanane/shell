#include "minishell.h"

int is_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;

    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "env") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "export") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return 1;

    return 0;
}
void exec_builtin(t_cmd *cmd)
{
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        do_cd(cmd);
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        do_echo(cmd);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        do_exit(cmd);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        do_env(cmd);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        do_export(cmd);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        do_unset(cmd);
}

int has_pipe(t_cmd *cmd)
{
    if (cmd && cmd->next != NULL)
        return (1);
    else
        return (0);
}

void executor(t_cmd *cmd, char **envp)
{
    if (!cmd)
        return;

    if (has_pipe(cmd))
        pipe_executor(cmd, envp);
    else if (is_builtin(cmd))
    {
        find_redirection(cmd->redir);
        exec_builtin(cmd);
    }
    else
    {
        execute_external(cmd, envp);
    }
}

