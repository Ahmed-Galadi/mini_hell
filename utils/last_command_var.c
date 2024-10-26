#include "../minishell.h"

char *get_last_command_path(const char *cmd, t_shell *data)
{
    char *cmd_path;
    char *pwd;

    if (!cmd)
        return (NULL);
    if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || 
        (cmd[1] == '.' && cmd[2] == '/'))))
    {
        if (cmd[0] == '.')
        {
            pwd = getcwd(NULL, 0);
            if (!pwd)
                return (NULL);
            cmd_path = malloc(ft_strlen(pwd) + ft_strlen(cmd) + 2);
            if (!cmd_path)
                return (NULL);
            sprintf(cmd_path, "%s/%s", pwd, cmd);
        }
        else
            cmd_path = ft_strdup(cmd);
    }
    else
        cmd_path = find_command((char *)cmd,env_to_array(data->env));
    return (cmd_path);
}

void update_underscore_var(t_shell *data, char **command)
{
    char *cmd_path;
    t_env *env_var;

    if (!command || !command[0])
        return;
    
    cmd_path = get_last_command_path(command[0], data);
    if (!cmd_path)
        return;
    data->last_exec_cmd = cmd_path;

    // Look for existing "_" variable
    env_var = data->env;
    while (env_var)
    {
        if (ft_strcmp(env_var->key, "_") == 0)
        {
            env_var->value = ft_strdup(cmd_path);
            return;
        }
        env_var = env_var->next;
    }

    // If "_" doesn't exist, create new env node
    env_var = gc_malloc(sizeof(t_env), GLOBAL);
    if (!env_var)
        return;

    env_var->key = ft_strdup("_");
    env_var->value = ft_strdup(cmd_path);
    env_var->next = data->env;
    data->env = env_var;
}