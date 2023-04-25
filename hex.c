#include "main.h"

unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * covert_x - converts unsiged int argument to hex using abcdef
 * @args: va_list pointing to the argument to be converted
 * @flags: flag modifier
 * @wid: width modifier
 * @prec: precesion modifier
 * @len: length modifier
 * @output: buffer_t struct containting a character
 * Return: the number of bytes stored to the buffer.
 */
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;

	unsigned int ret = 0;

	char *lead = "0x";

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);
	if (!(num == 0 && prec == 0))
		ret += convert_ubase(output, num, "0123456789abcdef",
				flags, wid, prec);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}
/**
 * convert_X - converts an unsigned int argument to hex using ABCDEF
 * @args: va_list pointing to the argument
 * @flags: flag modifiers
 * @wid: width modifier
 * @prec: precision modifer
 * @len: length modifier
 * @output: Buffer_t struct containing a character array
 * Return: number of bytes stored
 */
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;

	unsigned int ret = 0;

	char *lead = "0X";

	if (len == LONG)
		num = va_arg(args, unsigned long);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);
	if (!(num == 0 && prec == 0))
		ret += convert_ubase(output, num, "0123456789ABCDEF",
				flags, wid, prec);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}
