#include "main.h"

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_t *out, unsigned int printed,
		unsigned char flags, int wid);

/**
 * print_width - stores leading spaces to a buffer for width modifier
 * @output: a buffer_t struct containing a char array
 * @printed: number of characters printed to output for a specifier
 * @flags: flags modifier
 * @wid: width modifier
 *
 * Return: number of bytes stored to buffer
 */

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		for (wid -= printed; wid > 0;)
			ret += _memcpy(output, &width, 1);
	}

	return (ret);
}

/**
 * print_string_width - stores leading spaces to a buffer for
 * width modifier
 * @output: a buffer_t struct containing a char array
 * @flags: flags modifier
 * @wid: width modifier
 * @prec: precision modifier
 * @size: size of string
 *
 * Return: number of bytes stored to the buffer
 */

unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		wid -= (prec == -1) ? size : prec;
		for (; wid > 0; wid--)
			ret += _memcpy(output, &width, 1);
	}

	return (ret);
}

/**
 * print_neg_width - stores trailing spaces to buffer for '-' flag
 * @output: a buffer struct containing a char array
 * @printed: number of bytes stored to output for a specifier
 * @flags: flag modifier
 * @wid: width modifier
 *
 * Return: number of bytes stored to buffer
 */

unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 1)
	{
		for (wid -= printed; wid > 0; wid--)
			ret += _memcpy(output, &width, 1);
	}

	return (ret);
}
