/* automatically generated from src */
wfastcall struct nt_list *WIN_FUNC(ExfInterlockedInsertHeadList,3)
	(struct nt_list *head, struct nt_list *entry, NT_SPIN_LOCK *lock);
wfastcall struct nt_list *WIN_FUNC(ExInterlockedInsertHeadList,3)
	(struct nt_list *head, struct nt_list *entry, NT_SPIN_LOCK *lock);
wfastcall struct nt_list *WIN_FUNC(ExfInterlockedInsertTailList,3)
	(struct nt_list *head, struct nt_list *entry, NT_SPIN_LOCK *lock);
wfastcall struct nt_list *WIN_FUNC(ExInterlockedInsertTailList,3)
	(struct nt_list *head, struct nt_list *entry, NT_SPIN_LOCK *lock);
wfastcall struct nt_list *WIN_FUNC(ExfInterlockedRemoveHeadList,2)
	(struct nt_list *head, NT_SPIN_LOCK *lock);
wfastcall struct nt_list *WIN_FUNC(ExInterlockedRemoveHeadList,2)
	(struct nt_list *head, NT_SPIN_LOCK *lock);
wfastcall struct nt_list *WIN_FUNC(ExfInterlockedRemoveTailList,2)
	(struct nt_list *head, NT_SPIN_LOCK *lock);
wfastcall struct nt_list *WIN_FUNC(ExInterlockedRemoveTailList,2)
	(struct nt_list *head, NT_SPIN_LOCK *lock);
wfastcall void WIN_FUNC(InitializeSListHead,1)
	(nt_slist_header *head);
wfastcall struct nt_slist *WIN_FUNC(ExInterlockedPushEntrySList,3)
	(nt_slist_header *head, struct nt_slist *entry, NT_SPIN_LOCK *lock);
wstdcall struct nt_slist *WIN_FUNC(ExpInterlockedPushEntrySList,2)
	(nt_slist_header *head, struct nt_slist *entry);
wfastcall struct nt_slist *WIN_FUNC(InterlockedPushEntrySList,2)
	(nt_slist_header *head, struct nt_slist *entry);
wfastcall struct nt_slist *WIN_FUNC(ExInterlockedPopEntrySList,2)
	(nt_slist_header *head, NT_SPIN_LOCK *lock);
wstdcall struct nt_slist *WIN_FUNC(ExpInterlockedPopEntrySList,1)
	(nt_slist_header *head);
wfastcall struct nt_slist *WIN_FUNC(InterlockedPopEntrySList,1)
	(nt_slist_header *head);
wstdcall USHORT WIN_FUNC(ExQueryDepthSList,1)
	(nt_slist_header *head);
wfastcall LONG WIN_FUNC(InterlockedIncrement,1)
	(LONG volatile *val);
wfastcall LONG WIN_FUNC(InterlockedDecrement,1)
	(LONG volatile *val);
wfastcall LONG WIN_FUNC(InterlockedExchange,2)
	(LONG volatile *target, LONG val);
wfastcall LONG WIN_FUNC(InterlockedCompareExchange,3)
	(LONG volatile *dest, LONG new, LONG old);
wfastcall void WIN_FUNC(ExInterlockedAddLargeStatistic,2)
	(LARGE_INTEGER volatile *plint, ULONG n);
wstdcall void WIN_FUNC(KeInitializeTimerEx,2)
	(struct nt_timer *nt_timer, enum timer_type type);
wstdcall void WIN_FUNC(KeInitializeTimer,1)
	(struct nt_timer *nt_timer);
wstdcall BOOLEAN WIN_FUNC(KeSetTimerEx,4)
	(struct nt_timer *nt_timer, LARGE_INTEGER duetime_ticks,
	 LONG period_ms, struct kdpc *kdpc);
wstdcall BOOLEAN WIN_FUNC(KeSetTimer,3)
	(struct nt_timer *nt_timer, LARGE_INTEGER duetime_ticks,
	 struct kdpc *kdpc);
wstdcall BOOLEAN WIN_FUNC(KeCancelTimer,1)
	(struct nt_timer *nt_timer);
wstdcall BOOLEAN WIN_FUNC(KeReadStateTimer,1)
	(struct nt_timer *nt_timer);
wstdcall void WIN_FUNC(KeInitializeDpc,3)
	(struct kdpc *kdpc, void *func, void *ctx);
wstdcall void WIN_FUNC(KeFlushQueuedDpcs,0)
	(void);
wstdcall BOOLEAN WIN_FUNC(KeInsertQueueDpc,3)
	(struct kdpc *kdpc, void *arg1, void *arg2);
wstdcall BOOLEAN WIN_FUNC(KeRemoveQueueDpc,1)
	(struct kdpc *kdpc);
wstdcall void WIN_FUNC(KeSetImportanceDpc,2)
	(struct kdpc *kdpc, enum kdpc_importance importance);
wstdcall void WIN_FUNC(KeInitializeSpinLock,1)
	(NT_SPIN_LOCK *lock);
wstdcall void WIN_FUNC(KeAcquireSpinLock,2)
	(NT_SPIN_LOCK *lock, KIRQL *irql);
wstdcall void WIN_FUNC(KeReleaseSpinLock,2)
	(NT_SPIN_LOCK *lock, KIRQL oldirql);
wstdcall void WIN_FUNC(KeAcquireSpinLockAtDpcLevel,1)
	(NT_SPIN_LOCK *lock);
wstdcall void WIN_FUNC(KeReleaseSpinLockFromDpcLevel,1)
	(NT_SPIN_LOCK *lock);
wstdcall void WIN_FUNC(KeRaiseIrql,2)
	(KIRQL newirql, KIRQL *oldirql);
wstdcall KIRQL WIN_FUNC(KeRaiseIrqlToDpcLevel,0)
	(void);
wstdcall void WIN_FUNC(KeLowerIrql,1)
	(KIRQL irql);
wstdcall KIRQL WIN_FUNC(KeAcquireSpinLockRaiseToDpc,1)
	(NT_SPIN_LOCK *lock);
wstdcall void *WIN_FUNC(ExAllocatePoolWithTag,3)
	(enum pool_type pool_type, SIZE_T size, ULONG tag);
wstdcall void WIN_FUNC(ExFreePoolWithTag,2)
	(void *addr, ULONG tag);
wstdcall void WIN_FUNC(ExFreePool,1)
	(void *addr);
wstdcall void WIN_FUNC(ExInitializeNPagedLookasideList,7)
	(struct npaged_lookaside_list *lookaside,
	 LOOKASIDE_ALLOC_FUNC *alloc_func, LOOKASIDE_FREE_FUNC *free_func,
	 ULONG flags, SIZE_T size, ULONG tag, USHORT depth);
wstdcall void WIN_FUNC(ExDeleteNPagedLookasideList,1)
	(struct npaged_lookaside_list *lookaside);
wstdcall NTSTATUS WIN_FUNC(ExCreateCallback,4)
	(struct callback_object **object, struct object_attributes *attributes,
	 BOOLEAN create, BOOLEAN allow_multiple_callbacks);
wstdcall void *WIN_FUNC(ExRegisterCallback,3)
	(struct callback_object *object, PCALLBACK_FUNCTION func, void *context);
wstdcall void WIN_FUNC(ExUnregisterCallback,1)
	(struct callback_func *callback);
wstdcall void WIN_FUNC(ExNotifyCallback,3)
	(struct callback_object *object, void *arg1, void *arg2);
wstdcall NTSTATUS WIN_FUNC(KeWaitForMultipleObjects,8)
	(ULONG count, void *object[], enum wait_type wait_type,
	 KWAIT_REASON wait_reason, KPROCESSOR_MODE wait_mode,
	 BOOLEAN alertable, LARGE_INTEGER *timeout,
	 struct wait_block *wait_block_array);
wstdcall NTSTATUS WIN_FUNC(KeWaitForSingleObject,5)
	(void *object, KWAIT_REASON wait_reason, KPROCESSOR_MODE wait_mode,
	 BOOLEAN alertable, LARGE_INTEGER *timeout);
wstdcall void WIN_FUNC(KeInitializeEvent,3)
	(struct nt_event *nt_event, enum event_type type, BOOLEAN state);
wstdcall LONG WIN_FUNC(KeSetEvent,3)
	(struct nt_event *nt_event, KPRIORITY incr, BOOLEAN wait);
wstdcall void WIN_FUNC(KeClearEvent,1)
	(struct nt_event *nt_event);
wstdcall LONG WIN_FUNC(KeResetEvent,1)
	(struct nt_event *nt_event);
wstdcall LONG WIN_FUNC(KeReadStateEvent,1)
	(struct nt_event *nt_event);
wstdcall void WIN_FUNC(KeInitializeMutex,2)
	(struct nt_mutex *mutex, ULONG level);
wstdcall LONG WIN_FUNC(KeReleaseMutex,2)
	(struct nt_mutex *mutex, BOOLEAN wait);
wstdcall void WIN_FUNC(KeInitializeSemaphore,3)
	(struct nt_semaphore *semaphore, LONG count, LONG limit);
wstdcall LONG WIN_FUNC(KeReleaseSemaphore,4)
	(struct nt_semaphore *semaphore, KPRIORITY incr, LONG adjustment,
	 BOOLEAN wait);
wstdcall NTSTATUS WIN_FUNC(KeDelayExecutionThread,3)
	(KPROCESSOR_MODE wait_mode, BOOLEAN alertable, LARGE_INTEGER *interval);
wstdcall ULONGLONG WIN_FUNC(KeQueryInterruptTime,0)
	(void);
wstdcall ULONG WIN_FUNC(KeQueryTimeIncrement,0)
	(void);
wstdcall void WIN_FUNC(KeQuerySystemTime,1)
	(LARGE_INTEGER *time);
wstdcall void WIN_FUNC(KeQueryTickCount,1)
	(LARGE_INTEGER *count);
wstdcall LARGE_INTEGER WIN_FUNC(KeQueryPerformanceCounter,1)
	(LARGE_INTEGER *counter);
wstdcall KAFFINITY WIN_FUNC(KeQueryActiveProcessors,0)
	(void);
wstdcall struct nt_thread *WIN_FUNC(KeGetCurrentThread,0)
	(void);
wstdcall KPRIORITY WIN_FUNC(KeQueryPriorityThread,1)
	(struct nt_thread *thread);
wstdcall KPRIORITY WIN_FUNC(KeSetPriorityThread,2)
	(struct nt_thread *thread, KPRIORITY prio);
wstdcall NTSTATUS WIN_FUNC(PsCreateSystemThread,7)
	(void **handle, ULONG access, void *obj_attr, void *process,
	 void *client_id, void (*func)(void *) wstdcall, void *ctx);
wstdcall NTSTATUS WIN_FUNC(PsTerminateSystemThread,1)
	(NTSTATUS status);
wstdcall BOOLEAN WIN_FUNC(KeRemoveEntryDeviceQueue,2)
	(struct kdevice_queue *dev_queue, struct kdevice_queue_entry *entry);
wstdcall BOOLEAN WIN_FUNC(KeSynchronizeExecution,3)
	(struct kinterrupt *interrupt, PKSYNCHRONIZE_ROUTINE synch_routine,
	 void *ctx);
wstdcall void *WIN_FUNC(MmAllocateContiguousMemorySpecifyCache,5)
	(SIZE_T size, PHYSICAL_ADDRESS lowest, PHYSICAL_ADDRESS highest,
	 PHYSICAL_ADDRESS boundary, enum memory_caching_type cache_type);
wstdcall void WIN_FUNC(MmFreeContiguousMemorySpecifyCache,3)
	(void *base, SIZE_T size, enum memory_caching_type cache_type);
wstdcall PHYSICAL_ADDRESS WIN_FUNC(MmGetPhysicalAddress,1)
	(void *base);
wstdcall void __iomem *WIN_FUNC(MmMapIoSpace,3)
	(PHYSICAL_ADDRESS phys_addr, SIZE_T size,
	 enum memory_caching_type cache);
wstdcall void WIN_FUNC(MmUnmapIoSpace,2)
	(void __iomem *addr, SIZE_T size);
wstdcall ULONG WIN_FUNC(MmSizeOfMdl,2)
	(void *base, ULONG length);
wstdcall void WIN_FUNC(IoBuildPartialMdl,4)
	(struct mdl *source, struct mdl *target, void *virt, ULONG length);
wstdcall void WIN_FUNC(MmBuildMdlForNonPagedPool,1)
	(struct mdl *mdl);
wstdcall void *WIN_FUNC(MmMapLockedPages,2)
	(struct mdl *mdl, KPROCESSOR_MODE access_mode);
wstdcall void *WIN_FUNC(MmMapLockedPagesSpecifyCache,6)
	(struct mdl *mdl, KPROCESSOR_MODE access_mode,
	 enum memory_caching_type cache_type, void *base_address,
	 ULONG bug_check, enum mm_page_priority priority);
wstdcall void WIN_FUNC(MmUnmapLockedPages,2)
	(void *base, struct mdl *mdl);
wstdcall void WIN_FUNC(MmProbeAndLockPages,3)
	(struct mdl *mdl, KPROCESSOR_MODE access_mode,
	 enum lock_operation operation);
wstdcall void WIN_FUNC(MmUnlockPages,1)
	(struct mdl *mdl);
wstdcall BOOLEAN WIN_FUNC(MmIsAddressValid,1)
	(void *virt_addr);
wstdcall void *WIN_FUNC(MmLockPagableDataSection,1)
	(void *address);
wstdcall void WIN_FUNC(MmUnlockPagableImageSection,1)
	(void *handle);
wstdcall NTSTATUS WIN_FUNC(ObReferenceObjectByHandle,6)
	(void *handle, ACCESS_MASK desired_access, void *obj_type,
	 KPROCESSOR_MODE access_mode, void **object, void *handle_info);
wfastcall LONG WIN_FUNC(ObfReferenceObject,1)
	(void *object);
wfastcall void WIN_FUNC(ObfDereferenceObject,1)
	(void *object);
wstdcall NTSTATUS WIN_FUNC(ZwCreateFile,11)
	(void **handle, ACCESS_MASK access_mask,
	 struct object_attributes *obj_attr, struct io_status_block *iosb,
	 LARGE_INTEGER *size, ULONG file_attr, ULONG share_access,
	 ULONG create_disposition, ULONG create_options, void *ea_buffer,
	 ULONG ea_length);
wstdcall NTSTATUS WIN_FUNC(ZwOpenFile,6)
	(void **handle, ACCESS_MASK access_mask,
	 struct object_attributes *obj_attr, struct io_status_block *iosb,
	 ULONG share_access, ULONG open_options);
wstdcall NTSTATUS WIN_FUNC(ZwReadFile,9)
	(void *handle, struct nt_event *event, void *apc_routine,
	 void *apc_context, struct io_status_block *iosb, void *buffer,
	 ULONG length, LARGE_INTEGER *byte_offset, ULONG *key);
wstdcall NTSTATUS WIN_FUNC(ZwWriteFile,9)
	(void *handle, struct nt_event *event, void *apc_routine,
	 void *apc_context, struct io_status_block *iosb, void *buffer,
	 ULONG length, LARGE_INTEGER *byte_offset, ULONG *key);
wstdcall NTSTATUS WIN_FUNC(ZwClose,1)
	(void *handle);
wstdcall NTSTATUS WIN_FUNC(ZwQueryInformationFile,5)
	(void *handle, struct io_status_block *iosb, void *info,
	 ULONG length, enum file_info_class class);
wstdcall NTSTATUS WIN_FUNC(ZwOpenSection,3)
	(void **handle, ACCESS_MASK access, struct object_attributes *obj_attrs);
wstdcall NTSTATUS WIN_FUNC(ZwMapViewOfSection,10)
	(void *secn_handle, void *process_handle, void **base_address,
	 ULONG zero_bits, LARGE_INTEGER *secn_offset, SIZE_T *view_size,
	 enum section_inherit inherit, ULONG alloc_type, ULONG protect);
wstdcall NTSTATUS WIN_FUNC(ZwUnmapViewOfSection,2)
	(void *process_handle, void *base_address);
wstdcall NTSTATUS WIN_FUNC(ZwCreateKey,7)
	(void **handle, ACCESS_MASK desired_access,
	 struct object_attributes *attr, ULONG title_index,
	 struct unicode_string *class, ULONG create_options,
	 ULONG *disposition);
wstdcall NTSTATUS WIN_FUNC(ZwOpenKey,3)
	(void **handle, ACCESS_MASK desired_access,
	 struct object_attributes *attr);
wstdcall NTSTATUS WIN_FUNC(ZwSetValueKey,6)
	(void *handle, struct unicode_string *name, ULONG title_index,
	 ULONG type, void *data, ULONG data_size);
wstdcall NTSTATUS WIN_FUNC(ZwQueryValueKey,6)
	(void *handle, struct unicode_string *name,
	 enum key_value_information_class class, void *info,
	 ULONG length, ULONG *res_length);
wstdcall NTSTATUS WIN_FUNC(ZwDeleteKey,1)
	(void *handle);
wstdcall NTSTATUS WIN_FUNC(ZwPowerInformation,4)
	(INT info_level, void *in_buf, ULONG in_buf_len, void *out_buf,
	 ULONG out_buf_len);
wstdcall NTSTATUS WIN_FUNC(WmiSystemControl,4)
	(struct wmilib_context *info, struct device_object *dev_obj,
	 struct irp *irp, void *irp_disposition);
wstdcall NTSTATUS WIN_FUNC(WmiCompleteRequest,5)
	(struct device_object *dev_obj, struct irp *irp, NTSTATUS status,
	 ULONG buffer_used, CCHAR priority_boost);
noregparm NTSTATUS WIN_FUNC(WmiTraceMessage,12)
	(void *tracehandle, ULONG message_flags,
	 void *message_guid, USHORT message_no, ...);
wstdcall NTSTATUS WIN_FUNC(WmiQueryTraceInformation,4)
	(enum trace_information_class trace_info_class, void *trace_info,
	 ULONG *req_length, void *buf);
noregparm ULONG WIN_FUNC(DbgPrint,12)
	(char *format, ...);
wstdcall void WIN_FUNC(KeBugCheck,1)
	(ULONG code);
wstdcall void WIN_FUNC(KeBugCheckEx,5)
	(ULONG code, ULONG_PTR param1, ULONG_PTR param2,
	 ULONG_PTR param3, ULONG_PTR param4);
wstdcall void WIN_FUNC(ExSystemTimeToLocalTime,2)
	(LARGE_INTEGER *system_time, LARGE_INTEGER *local_time);
wstdcall ULONG WIN_FUNC(ExSetTimerResolution,2)
	(ULONG time, BOOLEAN set);
wstdcall void WIN_FUNC(DbgBreakPoint,0)
	(void);
wstdcall void WIN_FUNC(_except_handler3,0)
	(void);
wstdcall void WIN_FUNC(__C_specific_handler,0)
	(void);
wstdcall void WIN_FUNC(_purecall,0)
	(void);
wstdcall void WIN_FUNC(__chkstk,0)
	(void);
#ifdef CONFIG_X86_64
WIN_FUNC_DECL(DbgBreakPoint, 0)
WIN_FUNC_DECL(DbgPrint, 12)
WIN_FUNC_DECL(ExAllocatePoolWithTag, 3)
WIN_FUNC_DECL(ExCreateCallback, 4)
WIN_FUNC_DECL(ExDeleteNPagedLookasideList, 1)
WIN_FUNC_DECL(ExFreePool, 1)
WIN_FUNC_DECL(ExFreePoolWithTag, 2)
WIN_FUNC_DECL(ExInitializeNPagedLookasideList, 7)
WIN_FUNC_DECL(ExInterlockedAddLargeStatistic, 2)
WIN_FUNC_DECL(ExInterlockedInsertHeadList, 3)
WIN_FUNC_DECL(ExInterlockedInsertTailList, 3)
WIN_FUNC_DECL(ExInterlockedPopEntrySList, 2)
WIN_FUNC_DECL(ExInterlockedPushEntrySList, 3)
WIN_FUNC_DECL(ExInterlockedRemoveHeadList, 2)
WIN_FUNC_DECL(ExInterlockedRemoveTailList, 2)
WIN_FUNC_DECL(ExNotifyCallback, 3)
WIN_FUNC_DECL(ExQueryDepthSList, 1)
WIN_FUNC_DECL(ExRegisterCallback, 3)
WIN_FUNC_DECL(ExSetTimerResolution, 2)
WIN_FUNC_DECL(ExSystemTimeToLocalTime, 2)
WIN_FUNC_DECL(ExUnregisterCallback, 1)
WIN_FUNC_DECL(ExfInterlockedInsertHeadList, 3)
WIN_FUNC_DECL(ExfInterlockedInsertTailList, 3)
WIN_FUNC_DECL(ExfInterlockedRemoveHeadList, 2)
WIN_FUNC_DECL(ExfInterlockedRemoveTailList, 2)
WIN_FUNC_DECL(ExpInterlockedPopEntrySList, 1)
WIN_FUNC_DECL(ExpInterlockedPushEntrySList, 2)
WIN_FUNC_DECL(InitializeSListHead, 1)
WIN_FUNC_DECL(InterlockedCompareExchange, 3)
WIN_FUNC_DECL(InterlockedDecrement, 1)
WIN_FUNC_DECL(InterlockedExchange, 2)
WIN_FUNC_DECL(InterlockedIncrement, 1)
WIN_FUNC_DECL(InterlockedPopEntrySList, 1)
WIN_FUNC_DECL(InterlockedPushEntrySList, 2)
WIN_FUNC_DECL(IoBuildPartialMdl, 4)
WIN_FUNC_DECL(KeAcquireSpinLock, 2)
WIN_FUNC_DECL(KeAcquireSpinLockAtDpcLevel, 1)
WIN_FUNC_DECL(KeAcquireSpinLockRaiseToDpc, 1)
WIN_FUNC_DECL(KeBugCheck, 1)
WIN_FUNC_DECL(KeBugCheckEx, 5)
WIN_FUNC_DECL(KeCancelTimer, 1)
WIN_FUNC_DECL(KeClearEvent, 1)
WIN_FUNC_DECL(KeDelayExecutionThread, 3)
WIN_FUNC_DECL(KeFlushQueuedDpcs, 0)
WIN_FUNC_DECL(KeGetCurrentThread, 0)
WIN_FUNC_DECL(KeInitializeDpc, 3)
WIN_FUNC_DECL(KeInitializeEvent, 3)
WIN_FUNC_DECL(KeInitializeMutex, 2)
WIN_FUNC_DECL(KeInitializeSemaphore, 3)
WIN_FUNC_DECL(KeInitializeSpinLock, 1)
WIN_FUNC_DECL(KeInitializeTimer, 1)
WIN_FUNC_DECL(KeInitializeTimerEx, 2)
WIN_FUNC_DECL(KeInsertQueueDpc, 3)
WIN_FUNC_DECL(KeLowerIrql, 1)
WIN_FUNC_DECL(KeQueryActiveProcessors, 0)
WIN_FUNC_DECL(KeQueryInterruptTime, 0)
WIN_FUNC_DECL(KeQueryPerformanceCounter, 1)
WIN_FUNC_DECL(KeQueryPriorityThread, 1)
WIN_FUNC_DECL(KeQuerySystemTime, 1)
WIN_FUNC_DECL(KeQueryTickCount, 1)
WIN_FUNC_DECL(KeQueryTimeIncrement, 0)
WIN_FUNC_DECL(KeRaiseIrql, 2)
WIN_FUNC_DECL(KeRaiseIrqlToDpcLevel, 0)
WIN_FUNC_DECL(KeReadStateEvent, 1)
WIN_FUNC_DECL(KeReadStateTimer, 1)
WIN_FUNC_DECL(KeReleaseMutex, 2)
WIN_FUNC_DECL(KeReleaseSemaphore, 4)
WIN_FUNC_DECL(KeReleaseSpinLock, 2)
WIN_FUNC_DECL(KeReleaseSpinLockFromDpcLevel, 1)
WIN_FUNC_DECL(KeRemoveEntryDeviceQueue, 2)
WIN_FUNC_DECL(KeRemoveQueueDpc, 1)
WIN_FUNC_DECL(KeResetEvent, 1)
WIN_FUNC_DECL(KeSetEvent, 3)
WIN_FUNC_DECL(KeSetImportanceDpc, 2)
WIN_FUNC_DECL(KeSetPriorityThread, 2)
WIN_FUNC_DECL(KeSetTimer, 3)
WIN_FUNC_DECL(KeSetTimerEx, 4)
WIN_FUNC_DECL(KeSynchronizeExecution, 3)
WIN_FUNC_DECL(KeWaitForMultipleObjects, 8)
WIN_FUNC_DECL(KeWaitForSingleObject, 5)
WIN_FUNC_DECL(MmAllocateContiguousMemorySpecifyCache, 5)
WIN_FUNC_DECL(MmBuildMdlForNonPagedPool, 1)
WIN_FUNC_DECL(MmFreeContiguousMemorySpecifyCache, 3)
WIN_FUNC_DECL(MmGetPhysicalAddress, 1)
WIN_FUNC_DECL(MmIsAddressValid, 1)
WIN_FUNC_DECL(MmLockPagableDataSection, 1)
WIN_FUNC_DECL(MmMapIoSpace, 3)
WIN_FUNC_DECL(MmMapLockedPages, 2)
WIN_FUNC_DECL(MmMapLockedPagesSpecifyCache, 6)
WIN_FUNC_DECL(MmProbeAndLockPages, 3)
WIN_FUNC_DECL(MmSizeOfMdl, 2)
WIN_FUNC_DECL(MmUnlockPagableImageSection, 1)
WIN_FUNC_DECL(MmUnlockPages, 1)
WIN_FUNC_DECL(MmUnmapIoSpace, 2)
WIN_FUNC_DECL(MmUnmapLockedPages, 2)
WIN_FUNC_DECL(ObReferenceObjectByHandle, 6)
WIN_FUNC_DECL(ObfDereferenceObject, 1)
WIN_FUNC_DECL(ObfReferenceObject, 1)
WIN_FUNC_DECL(PsCreateSystemThread, 7)
WIN_FUNC_DECL(PsTerminateSystemThread, 1)
WIN_FUNC_DECL(WmiCompleteRequest, 5)
WIN_FUNC_DECL(WmiQueryTraceInformation, 4)
WIN_FUNC_DECL(WmiSystemControl, 4)
WIN_FUNC_DECL(WmiTraceMessage, 12)
WIN_FUNC_DECL(ZwClose, 1)
WIN_FUNC_DECL(ZwCreateFile, 11)
WIN_FUNC_DECL(ZwCreateKey, 7)
WIN_FUNC_DECL(ZwDeleteKey, 1)
WIN_FUNC_DECL(ZwMapViewOfSection, 10)
WIN_FUNC_DECL(ZwOpenFile, 6)
WIN_FUNC_DECL(ZwOpenKey, 3)
WIN_FUNC_DECL(ZwOpenSection, 3)
WIN_FUNC_DECL(ZwPowerInformation, 4)
WIN_FUNC_DECL(ZwQueryInformationFile, 5)
WIN_FUNC_DECL(ZwQueryValueKey, 6)
WIN_FUNC_DECL(ZwReadFile, 9)
WIN_FUNC_DECL(ZwSetValueKey, 6)
WIN_FUNC_DECL(ZwUnmapViewOfSection, 2)
WIN_FUNC_DECL(ZwWriteFile, 9)
WIN_FUNC_DECL(__C_specific_handler, 0)
WIN_FUNC_DECL(__chkstk, 0)
WIN_FUNC_DECL(_except_handler3, 0)
WIN_FUNC_DECL(_purecall, 0)
#endif
extern struct wrap_export ntoskernel_exports[];
struct wrap_export ntoskernel_exports[] = {
	WIN_SYMBOL(DbgBreakPoint, 0),
	WIN_SYMBOL(DbgPrint, 12),
	WIN_SYMBOL(ExAllocatePoolWithTag, 3),
	WIN_SYMBOL(ExCreateCallback, 4),
	WIN_SYMBOL(ExDeleteNPagedLookasideList, 1),
	WIN_SYMBOL(ExFreePool, 1),
	WIN_SYMBOL(ExFreePoolWithTag, 2),
	WIN_SYMBOL(ExInitializeNPagedLookasideList, 7),
	WIN_SYMBOL(ExInterlockedAddLargeStatistic, 2),
	WIN_SYMBOL(ExInterlockedInsertHeadList, 3),
	WIN_SYMBOL(ExInterlockedInsertTailList, 3),
	WIN_SYMBOL(ExInterlockedPopEntrySList, 2),
	WIN_SYMBOL(ExInterlockedPushEntrySList, 3),
	WIN_SYMBOL(ExInterlockedRemoveHeadList, 2),
	WIN_SYMBOL(ExInterlockedRemoveTailList, 2),
	WIN_SYMBOL(ExNotifyCallback, 3),
	WIN_SYMBOL(ExQueryDepthSList, 1),
	WIN_SYMBOL(ExRegisterCallback, 3),
	WIN_SYMBOL(ExSetTimerResolution, 2),
	WIN_SYMBOL(ExSystemTimeToLocalTime, 2),
	WIN_SYMBOL(ExUnregisterCallback, 1),
	WIN_SYMBOL(ExfInterlockedInsertHeadList, 3),
	WIN_SYMBOL(ExfInterlockedInsertTailList, 3),
	WIN_SYMBOL(ExfInterlockedRemoveHeadList, 2),
	WIN_SYMBOL(ExfInterlockedRemoveTailList, 2),
	WIN_SYMBOL(ExpInterlockedPopEntrySList, 1),
	WIN_SYMBOL(ExpInterlockedPushEntrySList, 2),
	WIN_SYMBOL(InitializeSListHead, 1),
	WIN_SYMBOL(InterlockedCompareExchange, 3),
	WIN_SYMBOL(InterlockedDecrement, 1),
	WIN_SYMBOL(InterlockedExchange, 2),
	WIN_SYMBOL(InterlockedIncrement, 1),
	WIN_SYMBOL(InterlockedPopEntrySList, 1),
	WIN_SYMBOL(InterlockedPushEntrySList, 2),
	WIN_SYMBOL(IoBuildPartialMdl, 4),
	WIN_SYMBOL(KeAcquireSpinLock, 2),
	WIN_SYMBOL(KeAcquireSpinLockAtDpcLevel, 1),
	WIN_SYMBOL(KeAcquireSpinLockRaiseToDpc, 1),
	WIN_SYMBOL(KeBugCheck, 1),
	WIN_SYMBOL(KeBugCheckEx, 5),
	WIN_SYMBOL(KeCancelTimer, 1),
	WIN_SYMBOL(KeClearEvent, 1),
	WIN_SYMBOL(KeDelayExecutionThread, 3),
	WIN_SYMBOL(KeFlushQueuedDpcs, 0),
	WIN_SYMBOL(KeGetCurrentThread, 0),
	WIN_SYMBOL(KeInitializeDpc, 3),
	WIN_SYMBOL(KeInitializeEvent, 3),
	WIN_SYMBOL(KeInitializeMutex, 2),
	WIN_SYMBOL(KeInitializeSemaphore, 3),
	WIN_SYMBOL(KeInitializeSpinLock, 1),
	WIN_SYMBOL(KeInitializeTimer, 1),
	WIN_SYMBOL(KeInitializeTimerEx, 2),
	WIN_SYMBOL(KeInsertQueueDpc, 3),
	WIN_SYMBOL(KeLowerIrql, 1),
	WIN_SYMBOL(KeQueryActiveProcessors, 0),
	WIN_SYMBOL(KeQueryInterruptTime, 0),
	WIN_SYMBOL(KeQueryPerformanceCounter, 1),
	WIN_SYMBOL(KeQueryPriorityThread, 1),
	WIN_SYMBOL(KeQuerySystemTime, 1),
	WIN_SYMBOL(KeQueryTickCount, 1),
	WIN_SYMBOL(KeQueryTimeIncrement, 0),
	WIN_SYMBOL(KeRaiseIrql, 2),
	WIN_SYMBOL(KeRaiseIrqlToDpcLevel, 0),
	WIN_SYMBOL(KeReadStateEvent, 1),
	WIN_SYMBOL(KeReadStateTimer, 1),
	WIN_SYMBOL(KeReleaseMutex, 2),
	WIN_SYMBOL(KeReleaseSemaphore, 4),
	WIN_SYMBOL(KeReleaseSpinLock, 2),
	WIN_SYMBOL(KeReleaseSpinLockFromDpcLevel, 1),
	WIN_SYMBOL(KeRemoveEntryDeviceQueue, 2),
	WIN_SYMBOL(KeRemoveQueueDpc, 1),
	WIN_SYMBOL(KeResetEvent, 1),
	WIN_SYMBOL(KeSetEvent, 3),
	WIN_SYMBOL(KeSetImportanceDpc, 2),
	WIN_SYMBOL(KeSetPriorityThread, 2),
	WIN_SYMBOL(KeSetTimer, 3),
	WIN_SYMBOL(KeSetTimerEx, 4),
	WIN_SYMBOL(KeSynchronizeExecution, 3),
	WIN_SYMBOL(KeWaitForMultipleObjects, 8),
	WIN_SYMBOL(KeWaitForSingleObject, 5),
	WIN_SYMBOL(MmAllocateContiguousMemorySpecifyCache, 5),
	WIN_SYMBOL(MmBuildMdlForNonPagedPool, 1),
	WIN_SYMBOL(MmFreeContiguousMemorySpecifyCache, 3),
	WIN_SYMBOL(MmGetPhysicalAddress, 1),
	WIN_SYMBOL(MmIsAddressValid, 1),
	WIN_SYMBOL(MmLockPagableDataSection, 1),
	WIN_SYMBOL(MmMapIoSpace, 3),
	WIN_SYMBOL(MmMapLockedPages, 2),
	WIN_SYMBOL(MmMapLockedPagesSpecifyCache, 6),
	WIN_SYMBOL(MmProbeAndLockPages, 3),
	WIN_SYMBOL(MmSizeOfMdl, 2),
	WIN_SYMBOL(MmUnlockPagableImageSection, 1),
	WIN_SYMBOL(MmUnlockPages, 1),
	WIN_SYMBOL(MmUnmapIoSpace, 2),
	WIN_SYMBOL(MmUnmapLockedPages, 2),
	WIN_SYMBOL(ObReferenceObjectByHandle, 6),
	WIN_SYMBOL(ObfDereferenceObject, 1),
	WIN_SYMBOL(ObfReferenceObject, 1),
	WIN_SYMBOL(PsCreateSystemThread, 7),
	WIN_SYMBOL(PsTerminateSystemThread, 1),
	WIN_SYMBOL(WmiCompleteRequest, 5),
	WIN_SYMBOL(WmiQueryTraceInformation, 4),
	WIN_SYMBOL(WmiSystemControl, 4),
	WIN_SYMBOL(WmiTraceMessage, 12),
	WIN_SYMBOL(ZwClose, 1),
	WIN_SYMBOL(ZwCreateFile, 11),
	WIN_SYMBOL(ZwCreateKey, 7),
	WIN_SYMBOL(ZwDeleteKey, 1),
	WIN_SYMBOL(ZwMapViewOfSection, 10),
	WIN_SYMBOL(ZwOpenFile, 6),
	WIN_SYMBOL(ZwOpenKey, 3),
	WIN_SYMBOL(ZwOpenSection, 3),
	WIN_SYMBOL(ZwPowerInformation, 4),
	WIN_SYMBOL(ZwQueryInformationFile, 5),
	WIN_SYMBOL(ZwQueryValueKey, 6),
	WIN_SYMBOL(ZwReadFile, 9),
	WIN_SYMBOL(ZwSetValueKey, 6),
	WIN_SYMBOL(ZwUnmapViewOfSection, 2),
	WIN_SYMBOL(ZwWriteFile, 9),
	WIN_SYMBOL(__C_specific_handler, 0),
	WIN_SYMBOL(__chkstk, 0),
	WIN_SYMBOL(_except_handler3, 0),
	WIN_SYMBOL(_purecall, 0),
	{"KeTickCount", (generic_func)&jiffies},
	{"NlsMbCodePageTag", (generic_func)FALSE},
	{NULL, NULL}
};
