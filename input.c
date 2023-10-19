#include "main.h"

/**
 * accept_input - assigns var for stream_read
 * @inputptr: stores input string
 * @buffer: string in the buffer
 * @i: input size
 * @b: buffer size
 */
void accept_input(char **inputptr, size_t *i, char *buffer, size_t b)
{

	if (*inputptr == NULL)
	{
		if  (b > BUFSIZE)
			*i = b;

		else
			*i = BUFSIZE;
		*inputptr = buffer;
	}
	else if (*i < b)
	{
		if (b > BUFSIZE)
			*i = b;
		else
			*i = BUFSIZE;
		*inputptr = buffer;
	}
	else
	{
		_strcopy(*inputptr, buffer);
		free(buffer);
	}
}
/**
 * stream_read - Read input from stream
 * @inputptr: buffer that stores the input
 * @i: inputptr size
 * @stream: stream to read from
 * Return: number of bytes
 */
ssize_t stream_read(char **inputptr, size_t *i, FILE *stream)
{
	int a;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		a = read(STDIN_FILENO, &t, 1);
		if (a == -1 || (a == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (a == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _rlocate(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	accept_input(inputptr, i, buffer, input);
	retval = input;
	if (a != 0)
		input = 0;
	return (retval);
}

/**
 * input_read - reads the input string.
 * @i_eof: return value of stream_read function
 * Return: input string
 */
char *input_read(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = stream_read(&input, &bufsize, stdin);

	return (input);
}
