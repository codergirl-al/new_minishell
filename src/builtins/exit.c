/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:25:14 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/28 15:17:02 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static int my_atoi(const char *str, int *out) {
//     int result = 0;
//     int sign = 1;
//     int digit;

//     if (*str == '-') {
//         sign = -1;
//         str++;
//     } else if (*str == '+') {
//         str++;
//     }
//     while (*str) {
//         if (*str < '0' || *str > '9') {
//             return -1; // Signal error if non-numeric character found
//         }
//         digit = *str - '0';
//         if (result > (INT_MAX - digit) / 10) { // Adjusted for general INT_MAX
//             return -1; // Signal overflow error
//         }
//         result = result * 10 + digit;
//         str++;
//     }
//     *out = result * sign;
//     return 0; // Success
// }

// void b_exit(t_data *data, char **args) {
//     if (args[1] && args[2]) {
//         fprintf(stderr, "exit: too many arguments\n");
//         data->exit_status = 1; // Preserve shell's running state if too many args
//         return;
//     }
//     if (args[1]) {
//         int status;
//         if (my_atoi(args[1], &status) == -1) {
//             fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
//             data->exit_status = 2; // Exit status for numeric argument required
//         } else {
//             data->exit_status = status;
//         }
//     }
//     exit((char)data->exit_status); // Use exit_status directly
// }
