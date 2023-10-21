#include "main.h"

/**
 * ptr_null - frees pointer and NULLs
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, else 0.
 */
int ptr_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
