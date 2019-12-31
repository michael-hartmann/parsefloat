#ifndef __STRTODOUBLE_H
#define __STRTODOUBLE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Convert string to float
 *
 * Convert the string str to a double. If success is not NULL, after exit
 * success is 1 if the conversion was successful or 0 if an error occured.
 *
 * @param [in]  str         string to parse
 * @param [out] success     1 if successful, 0 if an error occured
 * @retval      value       converted value
 */
double strtodouble(const char *str, int *success);

#ifdef __cplusplus
}
#endif

#endif // __STRTODOUBLE_H
