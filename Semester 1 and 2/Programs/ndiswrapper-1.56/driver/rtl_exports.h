/* automatically generated from src */
wstdcall SIZE_T WIN_FUNC(RtlCompareMemory,3)
	(const void *a, const void *b, SIZE_T len);
wstdcall void WIN_FUNC(RtlCopyMemory,3)
	(void *dst, const void *src, SIZE_T length);
wstdcall void WIN_FUNC(RtlZeroMemory,2)
	(void *dst, SIZE_T length);
wstdcall void WIN_FUNC(RtlSecureZeroMemory,2)
	(void *dst, SIZE_T length);
wstdcall void WIN_FUNC(RtlFillMemory,3)
	(void *dest, SIZE_T length, UCHAR fill);
wstdcall void WIN_FUNC(RtlMoveMemory,3)
	(void *dest, const void *src, SIZE_T length);
wstdcall LONG WIN_FUNC(RtlCompareString,3)
	(const struct ansi_string *s1, const struct ansi_string *s2,
	 BOOLEAN case_insensitive);
wstdcall LONG WIN_FUNC(RtlCompareUnicodeString,3)
	(const struct unicode_string *s1, const struct unicode_string *s2,
	 BOOLEAN case_insensitive);
wstdcall BOOLEAN WIN_FUNC(RtlEqualString,3)
	(const struct ansi_string *s1, const struct ansi_string *s2,
	 BOOLEAN case_insensitive);
wstdcall BOOLEAN WIN_FUNC(RtlEqualUnicodeString,3)
	(const struct unicode_string *s1, const struct unicode_string *s2,
	 BOOLEAN case_insensitive);
wstdcall void WIN_FUNC(RtlCopyUnicodeString,2)
	(struct unicode_string *dst, struct unicode_string *src);
wstdcall void WIN_FUNC(RtlCopyString,2)
	(struct ansi_string *dst, struct ansi_string *src);
wstdcall NTSTATUS WIN_FUNC(RtlAppendUnicodeToString,2)
	(struct unicode_string *dst, wchar_t *src);
wstdcall NTSTATUS WIN_FUNC(RtlAppendUnicodeStringToString,2)
	(struct unicode_string *dst, struct unicode_string *src);
wstdcall ULONG WIN_FUNC(RtlxAnsiStringToUnicodeSize,1)
	(const struct ansi_string *string);
wstdcall ULONG WIN_FUNC(RtlxUnicodeStringToAnsiSize,1)
	(const struct unicode_string *string);
wstdcall NTSTATUS WIN_FUNC(RtlAnsiStringToUnicodeString,3)
	(struct unicode_string *dst, const struct ansi_string *src,
	 BOOLEAN alloc);
wstdcall NTSTATUS WIN_FUNC(RtlUnicodeStringToAnsiString,3)
	(struct ansi_string *dst, const struct unicode_string *src,
	 BOOLEAN alloc);
wstdcall NTSTATUS WIN_FUNC(RtlUnicodeStringToInteger,3)
	(struct unicode_string *ustring, ULONG base, ULONG *value);
wstdcall NTSTATUS WIN_FUNC(RtlCharToInteger,3)
	(const char *string, ULONG base, ULONG *value);
wstdcall NTSTATUS WIN_FUNC(RtlIntegerToUnicodeString,3)
	(ULONG value, ULONG base, struct unicode_string *ustring);
wstdcall LARGE_INTEGER WIN_FUNC(RtlConvertUlongToLargeInteger,1)
	(ULONG ul);
wfastcall USHORT WIN_FUNC(RtlUshortByteSwap,1)
	(USHORT src);
wfastcall ULONG WIN_FUNC(RtlUlongByteSwap,1)
	(ULONG src);
wstdcall NTSTATUS WIN_FUNC(RtlUpcaseUnicodeString,3)
	(struct unicode_string *dst, struct unicode_string *src, BOOLEAN alloc);
wstdcall void WIN_FUNC(RtlInitUnicodeString,2)
	(struct unicode_string *dst, const wchar_t *src);
wstdcall void WIN_FUNC(RtlInitAnsiString,2)
	(struct ansi_string *dst, const char *src);
wstdcall void WIN_FUNC(RtlInitString,2)
	(struct ansi_string *dst, const char *src);
wstdcall void WIN_FUNC(RtlFreeUnicodeString,1)
	(struct unicode_string *string);
wstdcall void WIN_FUNC(RtlFreeAnsiString,1)
	(struct ansi_string *string);
wstdcall NTSTATUS WIN_FUNC(RtlGUIDFromString,2)
	(struct unicode_string *guid_string, struct guid *guid);
wstdcall NTSTATUS WIN_FUNC(RtlQueryRegistryValues,5)
	(ULONG relative, wchar_t *path, struct rtl_query_registry_table *tbl,
	 void *context, void *env);
wstdcall NTSTATUS WIN_FUNC(RtlWriteRegistryValue,6)
	(ULONG relative, wchar_t *path, wchar_t *name, ULONG type,
	 void *data, ULONG length);
wstdcall NTSTATUS WIN_FUNC(RtlDeleteRegistryValue,3)
	(ULONG relative, wchar_t *path, wchar_t *name);
wstdcall void WIN_FUNC(RtlAssert,4)
	(char *failed_assertion, char *file_name, ULONG line_num, char *message);
wstdcall void WIN_FUNC(RtlUnwind,0)
	(void);
wstdcall void WIN_FUNC(RtlRaiseException,1)
	(void *exception_record);
#ifdef CONFIG_X86_64
WIN_FUNC_DECL(RtlAnsiStringToUnicodeString, 3)
WIN_FUNC_DECL(RtlAppendUnicodeStringToString, 2)
WIN_FUNC_DECL(RtlAppendUnicodeToString, 2)
WIN_FUNC_DECL(RtlAssert, 4)
WIN_FUNC_DECL(RtlCharToInteger, 3)
WIN_FUNC_DECL(RtlCompareMemory, 3)
WIN_FUNC_DECL(RtlCompareString, 3)
WIN_FUNC_DECL(RtlCompareUnicodeString, 3)
WIN_FUNC_DECL(RtlConvertUlongToLargeInteger, 1)
WIN_FUNC_DECL(RtlCopyMemory, 3)
WIN_FUNC_DECL(RtlCopyString, 2)
WIN_FUNC_DECL(RtlCopyUnicodeString, 2)
WIN_FUNC_DECL(RtlDeleteRegistryValue, 3)
WIN_FUNC_DECL(RtlEqualString, 3)
WIN_FUNC_DECL(RtlEqualUnicodeString, 3)
WIN_FUNC_DECL(RtlFillMemory, 3)
WIN_FUNC_DECL(RtlFreeAnsiString, 1)
WIN_FUNC_DECL(RtlFreeUnicodeString, 1)
WIN_FUNC_DECL(RtlGUIDFromString, 2)
WIN_FUNC_DECL(RtlInitAnsiString, 2)
WIN_FUNC_DECL(RtlInitString, 2)
WIN_FUNC_DECL(RtlInitUnicodeString, 2)
WIN_FUNC_DECL(RtlIntegerToUnicodeString, 3)
WIN_FUNC_DECL(RtlMoveMemory, 3)
WIN_FUNC_DECL(RtlQueryRegistryValues, 5)
WIN_FUNC_DECL(RtlRaiseException, 1)
WIN_FUNC_DECL(RtlSecureZeroMemory, 2)
WIN_FUNC_DECL(RtlUlongByteSwap, 1)
WIN_FUNC_DECL(RtlUnicodeStringToAnsiString, 3)
WIN_FUNC_DECL(RtlUnicodeStringToInteger, 3)
WIN_FUNC_DECL(RtlUnwind, 0)
WIN_FUNC_DECL(RtlUpcaseUnicodeString, 3)
WIN_FUNC_DECL(RtlUshortByteSwap, 1)
WIN_FUNC_DECL(RtlWriteRegistryValue, 6)
WIN_FUNC_DECL(RtlZeroMemory, 2)
WIN_FUNC_DECL(RtlxAnsiStringToUnicodeSize, 1)
WIN_FUNC_DECL(RtlxUnicodeStringToAnsiSize, 1)
#endif
extern struct wrap_export rtl_exports[];
struct wrap_export rtl_exports[] = {
	WIN_SYMBOL(RtlAnsiStringToUnicodeString, 3),
	WIN_SYMBOL(RtlAppendUnicodeStringToString, 2),
	WIN_SYMBOL(RtlAppendUnicodeToString, 2),
	WIN_SYMBOL(RtlAssert, 4),
	WIN_SYMBOL(RtlCharToInteger, 3),
	WIN_SYMBOL(RtlCompareMemory, 3),
	WIN_SYMBOL(RtlCompareString, 3),
	WIN_SYMBOL(RtlCompareUnicodeString, 3),
	WIN_SYMBOL(RtlConvertUlongToLargeInteger, 1),
	WIN_SYMBOL(RtlCopyMemory, 3),
	WIN_SYMBOL(RtlCopyString, 2),
	WIN_SYMBOL(RtlCopyUnicodeString, 2),
	WIN_SYMBOL(RtlDeleteRegistryValue, 3),
	WIN_SYMBOL(RtlEqualString, 3),
	WIN_SYMBOL(RtlEqualUnicodeString, 3),
	WIN_SYMBOL(RtlFillMemory, 3),
	WIN_SYMBOL(RtlFreeAnsiString, 1),
	WIN_SYMBOL(RtlFreeUnicodeString, 1),
	WIN_SYMBOL(RtlGUIDFromString, 2),
	WIN_SYMBOL(RtlInitAnsiString, 2),
	WIN_SYMBOL(RtlInitString, 2),
	WIN_SYMBOL(RtlInitUnicodeString, 2),
	WIN_SYMBOL(RtlIntegerToUnicodeString, 3),
	WIN_SYMBOL(RtlMoveMemory, 3),
	WIN_SYMBOL(RtlQueryRegistryValues, 5),
	WIN_SYMBOL(RtlRaiseException, 1),
	WIN_SYMBOL(RtlSecureZeroMemory, 2),
	WIN_SYMBOL(RtlUlongByteSwap, 1),
	WIN_SYMBOL(RtlUnicodeStringToAnsiString, 3),
	WIN_SYMBOL(RtlUnicodeStringToInteger, 3),
	WIN_SYMBOL(RtlUnwind, 0),
	WIN_SYMBOL(RtlUpcaseUnicodeString, 3),
	WIN_SYMBOL(RtlUshortByteSwap, 1),
	WIN_SYMBOL(RtlWriteRegistryValue, 6),
	WIN_SYMBOL(RtlZeroMemory, 2),
	WIN_SYMBOL(RtlxAnsiStringToUnicodeSize, 1),
	WIN_SYMBOL(RtlxUnicodeStringToAnsiSize, 1),
	{NULL, NULL}
};
