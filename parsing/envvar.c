/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:24:36 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 19:36:39 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_var_value(char **valad, t_vlim *varlim, char **env)
{
	char	*value;
	char	*var;
	char	*varvalue;
	int		i;

	value = *valad;
	if (varlim->end - varlim->start == 0)
		var = ft_strdup("");
	else
	{
		var = malloc((varlim->end - varlim->start + 1) * sizeof(char));
		i = 0;
		while (value[varlim->start + 1 + i]
			&& varlim->start + 1 + i <= varlim->end)
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

void	ft_fill_val(char **valad, t_vlim *vlim, char **newval, char **env)
{
	char	*varvalue;
	int		i;
	int		j;

	i = -1;
	j = 0;
	varvalue = ft_get_var_value(valad, vlim, env);
	while (++i < vlim->start)
		(*newval)[i] = (*valad)[i];
	while (varvalue[j])
	{
		(*newval)[i] = varvalue[j];
		i++;
		j++;
	}
	j = vlim->end + 1;
	while ((*valad)[j])
	{
		(*newval)[i] = (*valad)[j];
		i++;
		j++;
	}
	(*newval)[i] = '\0';
	free(varvalue);
}

int	ft_handle_var(char **valad, t_vlim *varlim, char **env)
{
	char	*varvalue;
	char	*newvalue;
	int		newlen;
	int		offset;

	varvalue = ft_get_var_value(valad, varlim, env);
	if (!varvalue)
		return (1);
	offset = (int)ft_strlen(varvalue) - (varlim->end - varlim->start + 1);
	free(varvalue);
	newlen = (int)ft_strlen(*valad) + offset;
	newvalue = malloc ((newlen + 1) * sizeof(char));
	if (!newvalue)
		return (1);
	ft_fill_val(valad, varlim, &newvalue, env);
	free(*valad);
	*valad = newvalue;
	varlim->start += offset;
	varlim->end += offset;
	return (0);
}
