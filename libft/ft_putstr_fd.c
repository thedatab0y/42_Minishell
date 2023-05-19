/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:09:25 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/17 23:02:15 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
}

//int main(void)
//{
//	char *test = "Something to test";
//	char *test1 ="32453";
//	char *test2 ="Something \0";
//	char *test3 ="";
//
//	ft_putstr_fd(test, 0);
//	write(1,"\n",1);
//	ft_putstr_fd(test1, 0);
//	write(1,"\n",1);
//	ft_putstr_fd(test2, 0);
//	write(1,"\n",1);
//	ft_putstr_fd(test3, 0);
//	write(1,"\n",1);
//}