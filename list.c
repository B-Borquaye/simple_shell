#include "main.h"

/**
 * add_separator_end - adds a separator found at the end of the separator_list.
 * @head: head of linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
separator_list *add_separator_end(separator_list **head, char sep)
{
	separator_list *new, *temp;

	new = malloc(sizeof(separator_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_separator_list - frees a separator_list
 * @head: head of linked list.
 * Return: no return.
 */
void free_separator_list(separator_list **head)
{
	separator_list *temp;
	separator_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_end - adds a command line to the end of the line_list.
 * @head: head of linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_line_list - frees line_list
 * @head: head of linked list.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_rvariable_end - this adds a variable at the end of r_variable list.
 * @head: head of linked list.
 * @lengthvar: length of the variable.
 * @val: value of the variable.
 * @lvalue: length of the value.
 * Return: address of the head.
 */
r_variable *add_rvariable_end(r_variable **head, int lengthvar, char *val, int lvalue)
{
	r_variable *new, *temp;

	new = malloc(sizeof(r_variable));
	if (new == NULL)
		return (NULL);

	new->len_var = lengthvar;
	new->val = val;
	new->len_val = lvalue;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_rvariable_list - frees r_variable list
 * @head: head of linked list.
 * Return: no return.
 */
void free_rvariable_list(r_variable **head)
{
	r_variable *temp;
	r_variable *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
