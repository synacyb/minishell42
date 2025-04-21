#include "../../minishell.h"

void    set_data(t_node *data)
{
    if (!data)
        return;
    data->append = 0;
    data->args = NULL;
    data->cmd = NULL;
    data->infile = NULL;
    data->outfile = NULL;
    data->pipe_in = 0;
    data->pipe_out = 0;
}