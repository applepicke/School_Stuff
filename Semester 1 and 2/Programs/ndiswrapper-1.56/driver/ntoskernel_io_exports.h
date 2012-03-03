/* automatically generated from src */
wstdcall void WIN_FUNC(IoAcquireCancelSpinLock,1)
	(KIRQL *irql) __acquires(irql);
wstdcall void WIN_FUNC(IoReleaseCancelSpinLock,1)
	(KIRQL irql) __releases(irql);
wstdcall int WIN_FUNC(IoIsWdmVersionAvailable,2)
	(UCHAR major, UCHAR minor);
wstdcall BOOLEAN WIN_FUNC(IoIs32bitProcess,1)
	(struct irp *irp);
wstdcall void WIN_FUNC(IoInitializeIrp,3)
	(struct irp *irp, USHORT size, CCHAR stack_count);
wstdcall void WIN_FUNC(IoReuseIrp,2)
	(struct irp *irp, NTSTATUS status);
wstdcall struct irp *WIN_FUNC(IoAllocateIrp,2)
	(char stack_count, BOOLEAN charge_quota);
wstdcall BOOLEAN WIN_FUNC(IoCancelIrp,1)
	(struct irp *irp);
wstdcall void IoQueueThreadIrp(struct irp *irp);
wstdcall void IoDequeueThreadIrp(struct irp *irp);
wstdcall void WIN_FUNC(IoFreeIrp,1)
	(struct irp *irp);
wstdcall struct irp *WIN_FUNC(IoBuildAsynchronousFsdRequest,6)
	(ULONG major_fn, struct device_object *dev_obj, void *buffer,
	 ULONG length, LARGE_INTEGER *offset,
	 struct io_status_block *user_status);
wstdcall struct irp *WIN_FUNC(IoBuildSynchronousFsdRequest,7)
	(ULONG major_fn, struct device_object *dev_obj, void *buf,
	 ULONG length, LARGE_INTEGER *offset, struct nt_event *event,
	 struct io_status_block *user_status);
wstdcall struct irp *WIN_FUNC(IoBuildDeviceIoControlRequest,9)
	(ULONG ioctl, struct device_object *dev_obj,
	 void *input_buf, ULONG input_buf_len, void *output_buf,
	 ULONG output_buf_len, BOOLEAN internal_ioctl,
	 struct nt_event *event, struct io_status_block *io_status);
wfastcall NTSTATUS WIN_FUNC(IofCallDriver,2)
	(struct device_object *dev_obj, struct irp *irp);
wfastcall void WIN_FUNC(IofCompleteRequest,2)
	(struct irp *irp, CHAR prio_boost);
wstdcall NTSTATUS IoPassIrpDown(struct device_object *dev_obj, struct irp *irp);
wstdcall NTSTATUS IoIrpSyncComplete(struct device_object *dev_obj,
				    struct irp *irp, void *context);
wstdcall NTSTATUS IoSyncForwardIrp(struct device_object *dev_obj,
				   struct irp *irp);
wstdcall NTSTATUS IoAsyncForwardIrp(struct device_object *dev_obj,
				    struct irp *irp);
wstdcall NTSTATUS IoInvalidDeviceRequest(struct device_object *dev_obj,
					 struct irp *irp);
wstdcall NTSTATUS WIN_FUNC(IoConnectInterrupt,11)
	(struct kinterrupt **kinterrupt, PKSERVICE_ROUTINE isr, void *isr_ctx,
	 NT_SPIN_LOCK *lock, ULONG vector, KIRQL irql, KIRQL synch_irql,
	 enum kinterrupt_mode mode, BOOLEAN shared, KAFFINITY cpu_mask,
	 BOOLEAN save_fp);
wstdcall void WIN_FUNC(IoDisconnectInterrupt,1)
	(struct kinterrupt *interrupt);
wstdcall struct mdl *WIN_FUNC(IoAllocateMdl,5)
	(void *virt, ULONG length, BOOLEAN second_buf, BOOLEAN charge_quota,
	 struct irp *irp);
wstdcall void WIN_FUNC(IoFreeMdl,1)
	(struct mdl *mdl);
wstdcall struct io_workitem *WIN_FUNC(IoAllocateWorkItem,1)
	(struct device_object *dev_obj);
wstdcall void WIN_FUNC(IoFreeWorkItem,1)
	(struct io_workitem *io_workitem);
wstdcall void WIN_FUNC(IoQueueWorkItem,4)
	(struct io_workitem *io_workitem, void *func,
	 enum work_queue_type queue_type, void *context);
wstdcall void WIN_FUNC(ExQueueWorkItem,2)
	(struct io_workitem *io_workitem, enum work_queue_type queue_type);
wstdcall NTSTATUS WIN_FUNC(IoAllocateDriverObjectExtension,4)
	(struct driver_object *drv_obj, void *client_id, ULONG extlen,
	 void **ext);
wstdcall void *WIN_FUNC(IoGetDriverObjectExtension,2)
	(struct driver_object *drv_obj, void *client_id);
wstdcall NTSTATUS WIN_FUNC(IoCreateDevice,7)
	(struct driver_object *drv_obj, ULONG dev_ext_length,
	 struct unicode_string *dev_name, DEVICE_TYPE dev_type,
	 ULONG dev_chars, BOOLEAN exclusive, struct device_object **newdev);
wstdcall NTSTATUS WIN_FUNC(IoCreateUnprotectedSymbolicLink,2)
	(struct unicode_string *link, struct unicode_string *dev_name);
wstdcall NTSTATUS WIN_FUNC(IoCreateSymbolicLink,2)
	(struct unicode_string *link, struct unicode_string *dev_name);
wstdcall NTSTATUS WIN_FUNC(IoDeleteSymbolicLink,1)
	(struct unicode_string *link);
wstdcall void WIN_FUNC(IoDeleteDevice,1)
	(struct device_object *dev);
wstdcall void WIN_FUNC(IoDetachDevice,1)
	(struct device_object *tgt);
wstdcall struct device_object *WIN_FUNC(IoGetAttachedDevice,1)
	(struct device_object *dev);
wstdcall struct device_object *WIN_FUNC(IoGetAttachedDeviceReference,1)
	(struct device_object *dev);
wstdcall struct device_object *WIN_FUNC(IoAttachDeviceToDeviceStack,2)
	(struct device_object *src, struct device_object *tgt);
wstdcall NTSTATUS WIN_FUNC(IoGetDeviceProperty,5)
	(struct device_object *pdo, enum device_registry_property dev_property,
	 ULONG buffer_len, void *buffer, ULONG *result_len);
wstdcall NTSTATUS WIN_FUNC(IoGetDeviceObjectPointer,4)
	(struct unicode_string *name, ACCESS_MASK desired_access,
	 void *file_obj, struct device_object *dev_obj);
wstdcall union power_state WIN_FUNC(PoSetPowerState,3)
	(struct device_object *dev_obj, enum power_state_type type,
	 union power_state state);
wstdcall NTSTATUS WIN_FUNC(PoCallDriver,2)
	(struct device_object *dev_obj, struct irp *irp);
wstdcall NTSTATUS WIN_FUNC(PoRequestPowerIrp,6)
	(struct device_object *dev_obj, UCHAR minor_fn,
	 union power_state power_state, void *completion_func,
	 void *context, struct irp **pirp);
wstdcall void WIN_FUNC(PoStartNextPowerIrp,1)
	(struct irp *irp);
wstdcall void WIN_FUNC(IoInitializeRemoveLockEx,5)
	(struct io_remove_lock *lock, ULONG alloc_tag, ULONG max_locked_min,
	 ULONG high_mark, ULONG lock_size);
wstdcall void *WIN_FUNC(IoAllocateErrorLogEntry,2)
	(void *io_object, UCHAR entry_size);
wstdcall void WIN_FUNC(IoWriteErrorLogEntry,1)
	(void *entry);
wstdcall void WIN_FUNC(IoFreeErrorLogEntry,1)
	(void *entry);
wstdcall NTSTATUS WIN_FUNC(IoAcquireRemoveLockEx,5)
	(struct io_remove_lock lock, void *tag, char *file, ULONG line,
	 ULONG lock_size);
wstdcall NTSTATUS WIN_FUNC(IoReleaseRemoveLockEx,3)
	(struct io_remove_lock lock, void *tag, ULONG lock_size);
wstdcall NTSTATUS WIN_FUNC(IoRegisterDeviceInterface,4)
	(struct device_object *pdo, struct guid *guid_class,
	 struct unicode_string *reference, struct unicode_string *link);
wstdcall NTSTATUS WIN_FUNC(IoSetDeviceInterfaceState,2)
	(struct unicode_string *link, BOOLEAN enable);
wstdcall NTSTATUS WIN_FUNC(IoOpenDeviceRegistryKey,4)
	(struct device_object *dev_obj, ULONG type, ACCESS_MASK mask,
	 void **handle);
wstdcall NTSTATUS WIN_FUNC(IoWMIRegistrationControl,2)
	(struct device_object *dev_obj, ULONG action);
wstdcall void WIN_FUNC(IoInvalidateDeviceRelations,2)
	(struct device_object *dev_obj, enum device_relation_type type);
wstdcall void WIN_FUNC(IoInvalidateDeviceState,1)
	(struct device_object *pdo);
#ifdef CONFIG_X86_64
WIN_FUNC_DECL(ExQueueWorkItem, 2)
WIN_FUNC_DECL(IoAcquireCancelSpinLock, 1)
WIN_FUNC_DECL(IoAcquireRemoveLockEx, 5)
WIN_FUNC_DECL(IoAllocateDriverObjectExtension, 4)
WIN_FUNC_DECL(IoAllocateErrorLogEntry, 2)
WIN_FUNC_DECL(IoAllocateIrp, 2)
WIN_FUNC_DECL(IoAllocateMdl, 5)
WIN_FUNC_DECL(IoAllocateWorkItem, 1)
WIN_FUNC_DECL(IoAttachDeviceToDeviceStack, 2)
WIN_FUNC_DECL(IoBuildAsynchronousFsdRequest, 6)
WIN_FUNC_DECL(IoBuildDeviceIoControlRequest, 9)
WIN_FUNC_DECL(IoBuildSynchronousFsdRequest, 7)
WIN_FUNC_DECL(IoCancelIrp, 1)
WIN_FUNC_DECL(IoConnectInterrupt, 11)
WIN_FUNC_DECL(IoCreateDevice, 7)
WIN_FUNC_DECL(IoCreateSymbolicLink, 2)
WIN_FUNC_DECL(IoCreateUnprotectedSymbolicLink, 2)
WIN_FUNC_DECL(IoDeleteDevice, 1)
WIN_FUNC_DECL(IoDeleteSymbolicLink, 1)
WIN_FUNC_DECL(IoDetachDevice, 1)
WIN_FUNC_DECL(IoDisconnectInterrupt, 1)
WIN_FUNC_DECL(IoFreeErrorLogEntry, 1)
WIN_FUNC_DECL(IoFreeIrp, 1)
WIN_FUNC_DECL(IoFreeMdl, 1)
WIN_FUNC_DECL(IoFreeWorkItem, 1)
WIN_FUNC_DECL(IoGetAttachedDevice, 1)
WIN_FUNC_DECL(IoGetAttachedDeviceReference, 1)
WIN_FUNC_DECL(IoGetDeviceObjectPointer, 4)
WIN_FUNC_DECL(IoGetDeviceProperty, 5)
WIN_FUNC_DECL(IoGetDriverObjectExtension, 2)
WIN_FUNC_DECL(IoInitializeIrp, 3)
WIN_FUNC_DECL(IoInitializeRemoveLockEx, 5)
WIN_FUNC_DECL(IoInvalidateDeviceRelations, 2)
WIN_FUNC_DECL(IoInvalidateDeviceState, 1)
WIN_FUNC_DECL(IoIrpSyncComplete, 3)
WIN_FUNC_DECL(IoIs32bitProcess, 1)
WIN_FUNC_DECL(IoIsWdmVersionAvailable, 2)
WIN_FUNC_DECL(IoOpenDeviceRegistryKey, 4)
WIN_FUNC_DECL(IoQueueWorkItem, 4)
WIN_FUNC_DECL(IoRegisterDeviceInterface, 4)
WIN_FUNC_DECL(IoReleaseCancelSpinLock, 1)
WIN_FUNC_DECL(IoReleaseRemoveLockEx, 3)
WIN_FUNC_DECL(IoReuseIrp, 2)
WIN_FUNC_DECL(IoSetDeviceInterfaceState, 2)
WIN_FUNC_DECL(IoWMIRegistrationControl, 2)
WIN_FUNC_DECL(IoWriteErrorLogEntry, 1)
WIN_FUNC_DECL(IofCallDriver, 2)
WIN_FUNC_DECL(IofCompleteRequest, 2)
WIN_FUNC_DECL(PoCallDriver, 2)
WIN_FUNC_DECL(PoRequestPowerIrp, 6)
WIN_FUNC_DECL(PoSetPowerState, 3)
WIN_FUNC_DECL(PoStartNextPowerIrp, 1)
#endif
extern struct wrap_export ntoskernel_io_exports[];
struct wrap_export ntoskernel_io_exports[] = {
	WIN_SYMBOL(ExQueueWorkItem, 2),
	WIN_SYMBOL(IoAcquireCancelSpinLock, 1),
	WIN_SYMBOL(IoAcquireRemoveLockEx, 5),
	WIN_SYMBOL(IoAllocateDriverObjectExtension, 4),
	WIN_SYMBOL(IoAllocateErrorLogEntry, 2),
	WIN_SYMBOL(IoAllocateIrp, 2),
	WIN_SYMBOL(IoAllocateMdl, 5),
	WIN_SYMBOL(IoAllocateWorkItem, 1),
	WIN_SYMBOL(IoAttachDeviceToDeviceStack, 2),
	WIN_SYMBOL(IoBuildAsynchronousFsdRequest, 6),
	WIN_SYMBOL(IoBuildDeviceIoControlRequest, 9),
	WIN_SYMBOL(IoBuildSynchronousFsdRequest, 7),
	WIN_SYMBOL(IoCancelIrp, 1),
	WIN_SYMBOL(IoConnectInterrupt, 11),
	WIN_SYMBOL(IoCreateDevice, 7),
	WIN_SYMBOL(IoCreateSymbolicLink, 2),
	WIN_SYMBOL(IoCreateUnprotectedSymbolicLink, 2),
	WIN_SYMBOL(IoDeleteDevice, 1),
	WIN_SYMBOL(IoDeleteSymbolicLink, 1),
	WIN_SYMBOL(IoDetachDevice, 1),
	WIN_SYMBOL(IoDisconnectInterrupt, 1),
	WIN_SYMBOL(IoFreeErrorLogEntry, 1),
	WIN_SYMBOL(IoFreeIrp, 1),
	WIN_SYMBOL(IoFreeMdl, 1),
	WIN_SYMBOL(IoFreeWorkItem, 1),
	WIN_SYMBOL(IoGetAttachedDevice, 1),
	WIN_SYMBOL(IoGetAttachedDeviceReference, 1),
	WIN_SYMBOL(IoGetDeviceObjectPointer, 4),
	WIN_SYMBOL(IoGetDeviceProperty, 5),
	WIN_SYMBOL(IoGetDriverObjectExtension, 2),
	WIN_SYMBOL(IoInitializeIrp, 3),
	WIN_SYMBOL(IoInitializeRemoveLockEx, 5),
	WIN_SYMBOL(IoInvalidateDeviceRelations, 2),
	WIN_SYMBOL(IoInvalidateDeviceState, 1),
	WIN_SYMBOL(IoIs32bitProcess, 1),
	WIN_SYMBOL(IoIsWdmVersionAvailable, 2),
	WIN_SYMBOL(IoOpenDeviceRegistryKey, 4),
	WIN_SYMBOL(IoQueueWorkItem, 4),
	WIN_SYMBOL(IoRegisterDeviceInterface, 4),
	WIN_SYMBOL(IoReleaseCancelSpinLock, 1),
	WIN_SYMBOL(IoReleaseRemoveLockEx, 3),
	WIN_SYMBOL(IoReuseIrp, 2),
	WIN_SYMBOL(IoSetDeviceInterfaceState, 2),
	WIN_SYMBOL(IoWMIRegistrationControl, 2),
	WIN_SYMBOL(IoWriteErrorLogEntry, 1),
	WIN_SYMBOL(IofCallDriver, 2),
	WIN_SYMBOL(IofCompleteRequest, 2),
	WIN_SYMBOL(PoCallDriver, 2),
	WIN_SYMBOL(PoRequestPowerIrp, 6),
	WIN_SYMBOL(PoSetPowerState, 3),
	WIN_SYMBOL(PoStartNextPowerIrp, 1),
	{NULL, NULL}
};
