/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sigint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:41:53 by hyunahn           #+#    #+#             */
/*   Updated: 2024/10/14 15:56:59 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void interruptHandler(int sig)
{
	printf("this program will be exited in 3 seconds...\n");
	sleep(3);
	exit(0);
}

int main()
{
	signal(SIGINT, interruptHandler);  //sigint처리하기
	signal(SIGQUIT, SIG_IGN);	//sigquit 처리하기(아무것도 하지않게 SIG_IGN  사용)
	printf("input ctrl+c\n");
	while (1);
}
