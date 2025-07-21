/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:24:36 by anony             #+#    #+#             */
/*   Updated: 2025/07/21 17:25:11 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_get_var_value(char **adress, t_varlimits *varlim, char **env)
{
    char *value;
    char *var;
    char *varvalue;
    int i;
    
    value = *adress;
    if (varlim->end - varlim->start == 0)
        var = ft_strdup("");
    else
    {
        var = malloc((varlim->end - varlim->start + 1) * sizeof(char));
        i = 0;
        while(value[varlim->start + 1 + i] && varlim->start + 1 + i <= varlim->end)
        {
            var[i] = value[varlim->start + 1 + i];
            i++;
        }
        var[i] = '\0';
    }
    varvalue = ft_getenv(var, env);
    if (!varvalue)
        varvalue = ft_strdup("");
    free(var);
    return (varvalue);
}

void ft_fill_new_value_var(char **adress, t_varlimits *varlim, char **newvalue, char **env)
{
    char *varvalue;
    int i;
    int j;
    
    i = -1;
    j = 0;
    varvalue = ft_get_var_value(adress, varlim, env);
    while (++i < varlim->start)
        (*newvalue)[i] = (*adress)[i];
    while (varvalue[j])
    {
        (*newvalue)[i] = varvalue[j];
        i++;
        j++;
    }
    j = varlim->end + 1;
    while ((*adress)[j])
    {
        (*newvalue)[i] = (*adress)[j];
        i++;
        j++;
    }
    (*newvalue)[i] = '\0';
    free(varvalue);
}

int ft_handle_var(char **adress, t_varlimits *varlim, char **env)
{
    char *varvalue;
    char *newvalue;
    int newlen;
    int offset;

    varvalue = ft_get_var_value(adress, varlim, env);
    if (!varvalue)
        return (1);
    offset = (int)ft_strlen(varvalue) - (varlim->end - varlim->start + 1);
    free(varvalue);
    newlen = (int)ft_strlen(*adress) + offset;
    newvalue = malloc ((newlen + 1) * sizeof(char));
    if (!newvalue)
        return (1);
    ft_fill_new_value_var(adress, varlim, &newvalue, env);
    free(*adress);
    *adress = newvalue;
    varlim->start += offset;
    varlim->end += offset;
    return (0);
}
