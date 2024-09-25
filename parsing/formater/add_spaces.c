/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:52:32 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/21 15:38:18 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_op(char c) {
    return (c == '|' || c == '<' || c == '>');
}

char *add_spaces(char *str) {
    char *output;
    bool open_d_quote = false;
    bool open_s_quote = false;
    int i = 0, j = 0;

    // Allocate memory for output, double the input size to handle space insertion
    output = malloc(ft_strlen(str) * 2 + 1);
    if (!output) {
        return NULL; // Handle malloc failure
    }

    while (str[i]) {
        // Toggle quote states
        if (str[i] == '\'') {
            open_s_quote = !open_s_quote;
        }
        if (str[i] == '\"') {
            open_d_quote = !open_d_quote;
        }

        // Handle cases like ">>" or "<<"
        if (((str[i] == '>' && str[i + 1] == '>')
             || (str[i] == '<' && str[i + 1] == '<'))
            && (!open_d_quote && !open_s_quote)) {
            output[j++] = ' ';
            output[j++] = str[i++];
            output[j++] = str[i++];
            output[j++] = ' ';
        }
        // Handle spacing around individual operators
        else if (is_op(str[i]) && (!open_d_quote && !open_s_quote)) {
            // Add space before the operator
            if (j > 0 && output[j - 1] != ' ') {
                output[j++] = ' ';
            }
            // Add the operator
            output[j++] = str[i++];
            // Add space after the operator
            if (str[i] && str[i] != ' ') {
                output[j++] = ' ';
            }
        } else {
            // Copy normal characters
            output[j++] = str[i++];
        }
    }

    output[j] = '\0';  // Null-terminate the output string
    return output;
}

