// Replacement for the newlib's stdio.h.
//

#ifndef SCR_BSP_STDIO_H
#define SCR_BSP_STDIO_H

#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PRINTF_LEVEL
#define stdin ((void*)0)
#define stdout ((void*)1)
#define stderr ((void*)2)
#endif /* PRINTF_LEVEL */

int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap);
int vprintf(const char *format, va_list ap);

int snprintf(char *buf, size_t size, const char *fmt, ...) __attribute__((format (printf, 3, 4)));
int printf(const char *fmt, ...) __attribute__((format (printf, 1, 2)));
int putchar(int c);
int puts(const char *str);

// interlocked variant
int printk(const char *fmt, ...) __attribute__((format (printf, 1, 2)));

#define fprintf(file, fmt, ...) printf(fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // SCR_BSP_STDIO_H
