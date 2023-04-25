#include "main.h"

unsigned char handle_flags(const char *flag, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flags - matches flags with similar values
 * @flag: pointer to a pointer string of flags
 * @index: index counter for original format string
 *
 * Return: if flag chars are matched - a similar value, else 0
 */

unsigned char handle_flags(const char *flag, char *index)
{
	int i, j;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_length - matches length modifiers with their matching value
 * @modifier: pointer to a length modifier
 * @index: index counter for original format string
 *
 * Return: if length modifier is matched - its corresponding valu
 * otherwise - 0
 */

unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == '|')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - matches a width modifier with a matching value
 * @args: a va_list of arguments
 * @modifier: a pointer to width modifier
 * @index: an index counter for original format string
 *
 * Return: if width modifier is matched - its value
 * otherwse - 0
 */

int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);

			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - matches a precision modifier with
 * its matching value
 * @args: va_list of arguments
 * @modifier: a pointer to precision modifier
 * @index: index counter for original format string
 *
 * Return: if a precision modifier is matched, its value
 * if precision modifier is empty, zero, or negative - 0
 * else return (-1)
 */

int handle_precision(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') && *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
			(*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}
		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specifiers - matches a conversion specifier with
 * with a matching function
 * @specifier: pointer to a conversion specifier
 *
 * Return: if a conversion function is matched
 * a pointer to function, else NULL
 */

unsigned int (*handle_specifiers(const char *specifier))(va_list,
		buffer_t *, unsigned char, int, int, unsigned char)
{
	int i;

	converter_t converters[] = {
		{'c', convert_c},
		{'s', convert_s},
		{'d', convert_di},
		{'i', convert_di},
		{'%', convert_percent},
		{'b', convert_b},
		{'u', convert_u},
		{'o', convert_o},
		{'x', convert_x},
		{'X', convert_X},
		{'S', convert_S},
		{'p', convert_p},
		{'r', convert_r},
		{'R', convert_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
