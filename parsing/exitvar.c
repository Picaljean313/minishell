/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:44:39 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 13:55:37 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_exit(char **valad, t_vlim *varlim, char **newvalue)
{
	char	*varvalue;
	int		i;
	int		j;

	i = -1;
	j = 0;
	varvalue = ft_itoa(g_signal);
	while (++i < varlim->start)
		(*newvalue)[i] = (*valad)[i];
	while (varvalue[j])
	{
		(*newvalue)[i] = varvalue[j];
		i++;
		j++;
	}
	j = varlim->end + 1;
	while ((*valad)[j])
	{
		(*newvalue)[i] = (*valad)[j];
		i++;
		j++;
	}
	(*newvalue)[i] = '\0';
	free(varvalue);
}

int	ft_handle_var_exit_status(char **valad, t_vlim *varlim)
{
	char	*varvalue;
	char	*newvalue;
	int		offset;

	varvalue = ft_itoa(g_signal);
	if (!varvalue)
		return (1);
	offset = (int)ft_strlen(varvalue) - (varlim->end - varlim->start + 1);
	free(varvalue);
	newvalue = malloc (((int)ft_strlen(*valad) + offset + 1) * sizeof(char));
	if (!newvalue)
		return (1);
	ft_fill_exit(valad, varlim, &newvalue);
	free(*valad);
	*valad = newvalue;
	varlim->start += offset;
	varlim->end += offset;
	return (0);
}
