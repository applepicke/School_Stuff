/* automatically generated from src */
noregparm INT WIN_FUNC(_win_sprintf,12)
	(char *buf, const char *format, ...);
noregparm INT WIN_FUNC(swprintf,12)
	(wchar_t *buf, const wchar_t *format, ...);
noregparm INT WIN_FUNC(_win_vsprintf,3)
	(char *str, const char *format, va_list ap);
noregparm INT WIN_FUNC(_win_snprintf,12)
	(char *buf, SIZE_T count, const char *format, ...);
noregparm INT WIN_FUNC(_win__snprintf,12)
	(char *buf, SIZE_T count, const char *format, ...);
noregparm INT WIN_FUNC(_win_vsnprintf,4)
	(char *str, SIZE_T size, const char *format, va_list ap);
noregparm INT WIN_FUNC(_win__vsnprintf,4)
	(char *str, SIZE_T size, const char *format, va_list ap);
noregparm char *WIN_FUNC(_win_strncpy,3)
	(char *dst, char *src, SIZE_T n);
noregparm SIZE_T WIN_FUNC(_win_strlen,1)
	(const char *s);
noregparm INT WIN_FUNC(_win_strncmp,3)
	(const char *s1, const char *s2, SIZE_T n);
noregparm INT WIN_FUNC(_win_strcmp,2)
	(const char *s1, const char *s2);
noregparm INT WIN_FUNC(_win_stricmp,2)
	(const char *s1, const char *s2);
noregparm char *WIN_FUNC(_win_strncat,3)
	(char *dest, const char *src, SIZE_T n);
noregparm INT WIN_FUNC(_win_wcscmp,2)
	(const wchar_t *s1, const wchar_t *s2);
noregparm INT WIN_FUNC(_win_wcsicmp,2)
	(const wchar_t *s1, const wchar_t *s2);
noregparm SIZE_T WIN_FUNC(_win_wcslen,1)
	(const wchar_t *s);
noregparm wchar_t *WIN_FUNC(_win_wcsncpy,3)
	(wchar_t *dest, const wchar_t *src, SIZE_T n);
noregparm wchar_t *WIN_FUNC(_win_wcscpy,2)
	(wchar_t *dest, const wchar_t *src);
noregparm wchar_t *WIN_FUNC(_win_wcscat,2)
	(wchar_t *dest, const wchar_t *src);
noregparm INT WIN_FUNC(_win_towupper,1)
	(wchar_t c);
noregparm INT WIN_FUNC(_win_towlower,1)
	(wchar_t c);
noregparm INT WIN_FUNC(_win_tolower,1)
	(INT c);
noregparm INT WIN_FUNC(_win_toupper,1)
	(INT c);
noregparm void *WIN_FUNC(_win_strcpy,2)
	(void *to, const void *from);
noregparm char *WIN_FUNC(_win_strstr,2)
	(const char *s1, const char *s2);
noregparm char *WIN_FUNC(_win_strchr,2)
	(const char *s, int c);
noregparm char *WIN_FUNC(_win_strrchr,2)
	(const char *s, int c);
noregparm void *WIN_FUNC(_win_memmove,3)
	(void *to, void *from, SIZE_T count);
noregparm void *WIN_FUNC(_win_memchr,3)
	(const void *s, INT c, SIZE_T n);
noregparm void *WIN_FUNC(_win_memcpy,3)
	(void *to, const void *from, SIZE_T n);
noregparm void *WIN_FUNC(_win_memset,3)
	(void *s, char c, SIZE_T count);
noregparm int WIN_FUNC(_win_memcmp,3)
	(void *s1, void *s2, SIZE_T n);
noregparm void WIN_FUNC(_win_srand,1)
	(UINT seed);
noregparm int WIN_FUNC(rand,0)
	(void);
noregparm int WIN_FUNC(_win_atoi,1)
	(const char *ptr);
noregparm int WIN_FUNC(_win_isprint,1)
	(int c);
wstdcall s64 WIN_FUNC(_alldiv,2)
	(s64 a, s64 b);
wstdcall u64 WIN_FUNC(_aulldiv,2)
	(u64 a, u64 b);
wstdcall s64 WIN_FUNC(_allmul,2)
	(s64 a, s64 b);
wstdcall u64 WIN_FUNC(_aullmul,2)
	(u64 a, u64 b);
wstdcall s64 WIN_FUNC(_allrem,2)
	(s64 a, s64 b);
wstdcall u64 WIN_FUNC(_aullrem,2)
	(u64 a, u64 b);
__attribute__((regparm(3))) s64 WIN_FUNC(_allshl,2)
	(s64 a, u8 b);
__attribute__((regparm(3))) u64 WIN_FUNC(_aullshl,2)
	(u64 a, u8 b);
__attribute__((regparm(3))) s64 WIN_FUNC(_allshr,2)
	(s64 a, u8 b);
__attribute__((regparm(3))) u64 WIN_FUNC(_aullshr,2)
	(u64 a, u8 b);
#ifdef CONFIG_X86_64
WIN_FUNC_DECL(_alldiv, 2)
WIN_FUNC_DECL(_allmul, 2)
WIN_FUNC_DECL(_allrem, 2)
WIN_FUNC_DECL(_allshl, 2)
WIN_FUNC_DECL(_allshr, 2)
WIN_FUNC_DECL(_aulldiv, 2)
WIN_FUNC_DECL(_aullmul, 2)
WIN_FUNC_DECL(_aullrem, 2)
WIN_FUNC_DECL(_aullshl, 2)
WIN_FUNC_DECL(_aullshr, 2)
WIN_FUNC_DECL(_win__snprintf, 12)
WIN_FUNC_DECL(_win__vsnprintf, 4)
WIN_FUNC_DECL(_win_atoi, 1)
WIN_FUNC_DECL(_win_isprint, 1)
WIN_FUNC_DECL(_win_memchr, 3)
WIN_FUNC_DECL(_win_memcmp, 3)
WIN_FUNC_DECL(_win_memcpy, 3)
WIN_FUNC_DECL(_win_memmove, 3)
WIN_FUNC_DECL(_win_memset, 3)
WIN_FUNC_DECL(_win_snprintf, 12)
WIN_FUNC_DECL(_win_sprintf, 12)
WIN_FUNC_DECL(_win_srand, 1)
WIN_FUNC_DECL(_win_strchr, 2)
WIN_FUNC_DECL(_win_strcmp, 2)
WIN_FUNC_DECL(_win_strcpy, 2)
WIN_FUNC_DECL(_win_stricmp, 2)
WIN_FUNC_DECL(_win_strlen, 1)
WIN_FUNC_DECL(_win_strncat, 3)
WIN_FUNC_DECL(_win_strncmp, 3)
WIN_FUNC_DECL(_win_strncpy, 3)
WIN_FUNC_DECL(_win_strrchr, 2)
WIN_FUNC_DECL(_win_strstr, 2)
WIN_FUNC_DECL(_win_tolower, 1)
WIN_FUNC_DECL(_win_toupper, 1)
WIN_FUNC_DECL(_win_towlower, 1)
WIN_FUNC_DECL(_win_towupper, 1)
WIN_FUNC_DECL(_win_vsnprintf, 4)
WIN_FUNC_DECL(_win_vsprintf, 3)
WIN_FUNC_DECL(_win_wcscat, 2)
WIN_FUNC_DECL(_win_wcscmp, 2)
WIN_FUNC_DECL(_win_wcscpy, 2)
WIN_FUNC_DECL(_win_wcsicmp, 2)
WIN_FUNC_DECL(_win_wcslen, 1)
WIN_FUNC_DECL(_win_wcsncpy, 3)
WIN_FUNC_DECL(rand, 0)
WIN_FUNC_DECL(swprintf, 12)
#endif
extern struct wrap_export crt_exports[];
struct wrap_export crt_exports[] = {
	WIN_SYMBOL(_alldiv, 2),
	WIN_SYMBOL(_allmul, 2),
	WIN_SYMBOL(_allrem, 2),
	WIN_SYMBOL(_allshl, 2),
	WIN_SYMBOL(_allshr, 2),
	WIN_SYMBOL(_aulldiv, 2),
	WIN_SYMBOL(_aullmul, 2),
	WIN_SYMBOL(_aullrem, 2),
	WIN_SYMBOL(_aullshl, 2),
	WIN_SYMBOL(_aullshr, 2),
	WIN_SYMBOL(rand, 0),
	WIN_SYMBOL(swprintf, 12),
	WIN_WIN_SYMBOL(_snprintf, 12),
	WIN_WIN_SYMBOL(_vsnprintf, 4),
	WIN_WIN_SYMBOL(atoi, 1),
	WIN_WIN_SYMBOL(isprint, 1),
	WIN_WIN_SYMBOL(memchr, 3),
	WIN_WIN_SYMBOL(memcmp, 3),
	WIN_WIN_SYMBOL(memcpy, 3),
	WIN_WIN_SYMBOL(memmove, 3),
	WIN_WIN_SYMBOL(memset, 3),
	WIN_WIN_SYMBOL(snprintf, 12),
	WIN_WIN_SYMBOL(sprintf, 12),
	WIN_WIN_SYMBOL(srand, 1),
	WIN_WIN_SYMBOL(strchr, 2),
	WIN_WIN_SYMBOL(strcmp, 2),
	WIN_WIN_SYMBOL(strcpy, 2),
	WIN_WIN_SYMBOL(stricmp, 2),
	WIN_WIN_SYMBOL(strlen, 1),
	WIN_WIN_SYMBOL(strncat, 3),
	WIN_WIN_SYMBOL(strncmp, 3),
	WIN_WIN_SYMBOL(strncpy, 3),
	WIN_WIN_SYMBOL(strrchr, 2),
	WIN_WIN_SYMBOL(strstr, 2),
	WIN_WIN_SYMBOL(tolower, 1),
	WIN_WIN_SYMBOL(toupper, 1),
	WIN_WIN_SYMBOL(towlower, 1),
	WIN_WIN_SYMBOL(towupper, 1),
	WIN_WIN_SYMBOL(vsnprintf, 4),
	WIN_WIN_SYMBOL(vsprintf, 3),
	WIN_WIN_SYMBOL(wcscat, 2),
	WIN_WIN_SYMBOL(wcscmp, 2),
	WIN_WIN_SYMBOL(wcscpy, 2),
	WIN_WIN_SYMBOL(wcsicmp, 2),
	WIN_WIN_SYMBOL(wcslen, 1),
	WIN_WIN_SYMBOL(wcsncpy, 3),
	{NULL, NULL}
};
