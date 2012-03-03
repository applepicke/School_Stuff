/* automatically generated from src */
wstdcall void WIN_FUNC(NdisInitializeWrapper,4)
	(void **driver_handle, struct driver_object *driver,
	 struct unicode_string *reg_path, void *unused);
wstdcall void WIN_FUNC(NdisTerminateWrapper,2)
	(struct device_object *dev_obj, void *system_specific);
wstdcall NDIS_STATUS WIN_FUNC(NdisMRegisterMiniport,3)
	(struct driver_object *drv_obj, struct miniport *mp, UINT length);
wstdcall NDIS_STATUS WIN_FUNC(NdisMRegisterDevice,6)
	(struct driver_object *drv_obj, struct unicode_string *dev_name,
	 struct unicode_string *link, void **funcs,
	 struct device_object **dev_obj, void **dev_obj_handle);
wstdcall NDIS_STATUS WIN_FUNC(NdisMDeregisterDevice,1)
	(struct device_object *dev_obj);
wstdcall NDIS_STATUS WIN_FUNC(NdisAllocateMemoryWithTag,3)
	(void **dest, UINT length, ULONG tag);
wstdcall NDIS_STATUS WIN_FUNC(NdisAllocateMemory,4)
	(void **dest, UINT length, UINT flags, NDIS_PHY_ADDRESS highest_address);
wstdcall void WIN_FUNC(NdisFreeMemory,3)
	(void *addr, UINT length_tag, UINT flags);
noregparm void WIN_FUNC(NdisWriteErrorLogEntry,12)
	(struct driver_object *drv_obj, ULONG error, ULONG count, ...);
wstdcall void WIN_FUNC(NdisOpenConfiguration,3)
	(NDIS_STATUS *status, struct ndis_mp_block **conf_handle,
	 struct ndis_mp_block *handle);
wstdcall void WIN_FUNC(NdisOpenProtocolConfiguration,3)
	(NDIS_STATUS *status, void **confhandle,
	 struct unicode_string *section);
wstdcall void WIN_FUNC(NdisOpenConfigurationKeyByName,4)
	(NDIS_STATUS *status, void *handle,
	 struct unicode_string *key, void **subkeyhandle);
wstdcall void WIN_FUNC(NdisOpenConfigurationKeyByIndex,5)
	(NDIS_STATUS *status, void *handle, ULONG index,
	 struct unicode_string *key, void **subkeyhandle);
wstdcall void WIN_FUNC(NdisCloseConfiguration,1)
	(void *handle);
wstdcall void WIN_FUNC(NdisOpenFile,5)
	(NDIS_STATUS *status, struct wrap_bin_file **file,
	 UINT *filelength, struct unicode_string *filename,
	 NDIS_PHY_ADDRESS highest_address);
wstdcall void WIN_FUNC(NdisMapFile,3)
	(NDIS_STATUS *status, void **mappedbuffer, struct wrap_bin_file *file);
wstdcall void WIN_FUNC(NdisUnmapFile,1)
	(struct wrap_bin_file *file);
wstdcall void WIN_FUNC(NdisCloseFile,1)
	(struct wrap_bin_file *file);
wstdcall void WIN_FUNC(NdisGetSystemUpTime,1)
	(ULONG *ms);
wstdcall ULONG WIN_FUNC(NDIS_BUFFER_TO_SPAN_PAGES,1)
	(ndis_buffer *buffer);
wstdcall void WIN_FUNC(NdisGetBufferPhysicalArraySize,2)
	(ndis_buffer *buffer, UINT *arraysize);
wstdcall void WIN_FUNC(NdisReadConfiguration,5)
	(NDIS_STATUS *status, struct ndis_configuration_parameter **param,
	 struct ndis_mp_block *nmb, struct unicode_string *key,
	 enum ndis_parameter_type type);
wstdcall void WIN_FUNC(NdisWriteConfiguration,4)
	(NDIS_STATUS *status, struct ndis_mp_block *nmb,
	 struct unicode_string *key, struct ndis_configuration_parameter *param);
wstdcall void WIN_FUNC(NdisReadNetworkAddress,4)
	(NDIS_STATUS *status, void **addr, UINT *len,
	 struct ndis_mp_block *nmb);
wstdcall void WIN_FUNC(NdisInitializeString,2)
	(struct unicode_string *dest, UCHAR *src);
wstdcall void WIN_FUNC(NdisInitAnsiString,2)
	(struct ansi_string *dst, CHAR *src);
wstdcall void WIN_FUNC(NdisInitUnicodeString,2)
	(struct unicode_string *dest, const wchar_t *src);
wstdcall NDIS_STATUS WIN_FUNC(NdisAnsiStringToUnicodeString,2)
	(struct unicode_string *dst, struct ansi_string *src);
wstdcall NDIS_STATUS WIN_FUNC(NdisUnicodeStringToAnsiString,2)
	(struct ansi_string *dst, struct unicode_string *src);
wstdcall NTSTATUS WIN_FUNC(NdisUpcaseUnicodeString,2)
	(struct unicode_string *dst, struct unicode_string *src);
wstdcall void WIN_FUNC(NdisMSetAttributesEx,5)
	(struct ndis_mp_block *nmb, void *mp_ctx,
	 UINT hangcheck_interval, UINT attributes, ULONG adaptertype);
wstdcall ULONG WIN_FUNC(NdisReadPciSlotInformation,5)
	(struct ndis_mp_block *nmb, ULONG slot,
	 ULONG offset, char *buf, ULONG len);
wstdcall ULONG WIN_FUNC(NdisImmediateReadPciSlotInformation,5)
	(struct ndis_mp_block *nmb, ULONG slot,
	 ULONG offset, char *buf, ULONG len);
wstdcall ULONG WIN_FUNC(NdisWritePciSlotInformation,5)
	(struct ndis_mp_block *nmb, ULONG slot,
	 ULONG offset, char *buf, ULONG len);
wstdcall NDIS_STATUS WIN_FUNC(NdisMRegisterIoPortRange,4)
	(void **virt, struct ndis_mp_block *nmb, UINT start, UINT len);
wstdcall void WIN_FUNC(NdisMDeregisterIoPortRange,4)
	(struct ndis_mp_block *nmb, UINT start, UINT len, void* virt);
wstdcall void WIN_FUNC(NdisReadPortUchar,3)
	(struct ndis_mp_block *nmb, ULONG port, char *data);
wstdcall void WIN_FUNC(NdisImmediateReadPortUchar,3)
	(struct ndis_mp_block *nmb, ULONG port, char *data);
wstdcall void WIN_FUNC(NdisWritePortUchar,3)
	(struct ndis_mp_block *nmb, ULONG port, char data);
wstdcall void WIN_FUNC(NdisImmediateWritePortUchar,3)
	(struct ndis_mp_block *nmb, ULONG port, char data);
wstdcall void WIN_FUNC(NdisMQueryAdapterResources,4)
	(NDIS_STATUS *status, struct ndis_mp_block *nmb,
	 NDIS_RESOURCE_LIST *resource_list, UINT *size);
wstdcall NDIS_STATUS WIN_FUNC(NdisMPciAssignResources,3)
	(struct ndis_mp_block *nmb, ULONG slot_number,
	 NDIS_RESOURCE_LIST **resources);
wstdcall NDIS_STATUS WIN_FUNC(NdisMMapIoSpace,4)
	(void __iomem **virt, struct ndis_mp_block *nmb,
	 NDIS_PHY_ADDRESS phy_addr, UINT len);
wstdcall void WIN_FUNC(NdisMUnmapIoSpace,3)
	(struct ndis_mp_block *nmb, void __iomem *virt, UINT len);
wstdcall void WIN_FUNC(NdisAllocateSpinLock,1)
	(struct ndis_spinlock *lock);
wstdcall void WIN_FUNC(NdisFreeSpinLock,1)
	(struct ndis_spinlock *lock);
wstdcall void WIN_FUNC(NdisAcquireSpinLock,1)
	(struct ndis_spinlock *lock);
wstdcall void WIN_FUNC(NdisReleaseSpinLock,1)
	(struct ndis_spinlock *lock);
wstdcall void WIN_FUNC(NdisDprAcquireSpinLock,1)
	(struct ndis_spinlock *lock);
wstdcall void WIN_FUNC(NdisDprReleaseSpinLock,1)
	(struct ndis_spinlock *lock);
wstdcall void WIN_FUNC(NdisInitializeReadWriteLock,1)
	(struct ndis_rw_lock *rw_lock);
wstdcall void WIN_FUNC(NdisAcquireReadWriteLock,3)
	(struct ndis_rw_lock *rw_lock, BOOLEAN write,
	 struct lock_state *lock_state);
wstdcall void WIN_FUNC(NdisReleaseReadWriteLock,2)
	(struct ndis_rw_lock *rw_lock, struct lock_state *lock_state);
wstdcall NDIS_STATUS WIN_FUNC(NdisMAllocateMapRegisters,5)
	(struct ndis_mp_block *nmb, UINT dmachan,
	 NDIS_DMA_SIZE dmasize, ULONG basemap, ULONG max_buf_size);
wstdcall void WIN_FUNC(NdisMFreeMapRegisters,1)
	(struct ndis_mp_block *nmb);
wstdcall void WIN_FUNC(NdisMStartBufferPhysicalMapping,6)
	(struct ndis_mp_block *nmb, ndis_buffer *buf,
	 ULONG index, BOOLEAN write_to_dev,
	 struct ndis_phy_addr_unit *phy_addr_array, UINT *array_size);
wstdcall void WIN_FUNC(NdisMCompleteBufferPhysicalMapping,3)
	(struct ndis_mp_block *nmb, ndis_buffer *buf, ULONG index);
wstdcall void WIN_FUNC(NdisMAllocateSharedMemory,5)
	(struct ndis_mp_block *nmb, ULONG size,
	 BOOLEAN cached, void **virt, NDIS_PHY_ADDRESS *phys);
wstdcall void WIN_FUNC(NdisMFreeSharedMemory,5)
	(struct ndis_mp_block *nmb, ULONG size, BOOLEAN cached,
	 void *virt, NDIS_PHY_ADDRESS addr);
wstdcall void alloc_shared_memory_async(void *arg1, void *arg2);
wstdcall NDIS_STATUS WIN_FUNC(NdisMAllocateSharedMemoryAsync,4)
	(struct ndis_mp_block *nmb, ULONG size, BOOLEAN cached, void *ctx);
wstdcall void WIN_FUNC(NdisAllocateBufferPool,3)
	(NDIS_STATUS *status, struct ndis_buffer_pool **pool_handle,
	 UINT num_descr);
wstdcall void WIN_FUNC(NdisAllocateBuffer,5)
	(NDIS_STATUS *status, ndis_buffer **buffer,
	 struct ndis_buffer_pool *pool, void *virt, UINT length);
wstdcall void WIN_FUNC(NdisFreeBuffer,1)
	(ndis_buffer *buffer);
wstdcall void WIN_FUNC(NdisFreeBufferPool,1)
	(struct ndis_buffer_pool *pool);
wstdcall void WIN_FUNC(NdisAdjustBufferLength,2)
	(ndis_buffer *buffer, UINT length);
wstdcall void WIN_FUNC(NdisQueryBuffer,3)
	(ndis_buffer *buffer, void **virt, UINT *length);
wstdcall void WIN_FUNC(NdisQueryBufferSafe,4)
	(ndis_buffer *buffer, void **virt, UINT *length,
	 enum mm_page_priority priority);
wstdcall void *WIN_FUNC(NdisBufferVirtualAddress,1)
	(ndis_buffer *buffer);
wstdcall ULONG WIN_FUNC(NdisBufferLength,1)
	(ndis_buffer *buffer);
wstdcall void WIN_FUNC(NdisQueryBufferOffset,3)
	(ndis_buffer *buffer, UINT *offset, UINT *length);
wstdcall void WIN_FUNC(NdisUnchainBufferAtBack,2)
	(struct ndis_packet *packet, ndis_buffer **buffer);
wstdcall void WIN_FUNC(NdisUnchainBufferAtFront,2)
	(struct ndis_packet *packet, ndis_buffer **buffer);
wstdcall void WIN_FUNC(NdisGetFirstBufferFromPacketSafe,6)
	(struct ndis_packet *packet, ndis_buffer **first_buffer,
	 void **first_buffer_va, UINT *first_buffer_length,
	 UINT *total_buffer_length, enum mm_page_priority priority);
wstdcall void WIN_FUNC(NdisGetFirstBufferFromPacket,6)
	(struct ndis_packet *packet, ndis_buffer **first_buffer,
	 void **first_buffer_va, UINT *first_buffer_length,
	 UINT *total_buffer_length, enum mm_page_priority priority);
wstdcall void WIN_FUNC(NdisAllocatePacketPoolEx,5)
	(NDIS_STATUS *status, struct ndis_packet_pool **pool_handle,
	 UINT num_descr, UINT overflowsize, UINT proto_rsvd_length);
wstdcall void WIN_FUNC(NdisAllocatePacketPool,4)
	(NDIS_STATUS *status, struct ndis_packet_pool **pool_handle,
	 UINT num_descr, UINT proto_rsvd_length);
wstdcall void WIN_FUNC(NdisFreePacketPool,1)
	(struct ndis_packet_pool *pool);
wstdcall UINT WIN_FUNC(NdisPacketPoolUsage,1)
	(struct ndis_packet_pool *pool);
wstdcall void WIN_FUNC(NdisAllocatePacket,3)
	(NDIS_STATUS *status, struct ndis_packet **ndis_packet,
	 struct ndis_packet_pool *pool);
wstdcall void WIN_FUNC(NdisDprAllocatePacket,3)
	(NDIS_STATUS *status, struct ndis_packet **packet,
	 struct ndis_packet_pool *pool);
wstdcall void WIN_FUNC(NdisFreePacket,1)
	(struct ndis_packet *packet);
wstdcall struct ndis_packet_stack *WIN_FUNC(NdisIMGetCurrentPacketStack,2)
	(struct ndis_packet *packet, BOOLEAN *stacks_remain);
wstdcall void WIN_FUNC(NdisCopyFromPacketToPacketSafe,7)
	(struct ndis_packet *dst, UINT dst_offset, UINT num_to_copy,
	 struct ndis_packet *src, UINT src_offset, UINT *num_copied,
	 enum mm_page_priority priority);
wstdcall void WIN_FUNC(NdisCopyFromPacketToPacket,6)
	(struct ndis_packet *dst, UINT dst_offset, UINT num_to_copy,
	 struct ndis_packet *src, UINT src_offset, UINT *num_copied);
wstdcall void WIN_FUNC(NdisIMCopySendPerPacketInfo,2)
	(struct ndis_packet *dst, struct ndis_packet *src);
wstdcall void WIN_FUNC(NdisSend,3)
	(NDIS_STATUS *status, struct ndis_mp_block *nmb,
	 struct ndis_packet *packet);
wstdcall void mp_timer_dpc(struct kdpc *kdpc, void *ctx, void *arg1, void *arg2);
wstdcall void WIN_FUNC(NdisMInitializeTimer,4)
	(struct ndis_mp_timer *timer, struct ndis_mp_block *nmb,
	 DPC func, void *ctx);
wstdcall void WIN_FUNC(NdisMSetPeriodicTimer,2)
	(struct ndis_mp_timer *timer, UINT period_ms);
wstdcall void WIN_FUNC(NdisMCancelTimer,2)
	(struct ndis_mp_timer *timer, BOOLEAN *canceled);
wstdcall void WIN_FUNC(NdisInitializeTimer,3)
	(struct ndis_timer *timer, void *func, void *ctx);
wstdcall void WIN_FUNC(NdisSetTimer,2)
	(struct ndis_timer *timer, UINT duetime_ms);
wstdcall void WIN_FUNC(NdisCancelTimer,2)
	(struct ndis_timer *timer, BOOLEAN *canceled);
wstdcall void WIN_FUNC(NdisMRegisterAdapterShutdownHandler,3)
	(struct ndis_mp_block *nmb, void *ctx, void *func);
wstdcall void WIN_FUNC(NdisMDeregisterAdapterShutdownHandler,1)
	(struct ndis_mp_block *nmb);
wstdcall void deserialized_irq_handler(struct kdpc *kdpc, void *ctx,
				       void *arg1, void *arg2);
wstdcall void serialized_irq_handler(struct kdpc *kdpc, void *ctx,
				     void *arg1, void *arg2);
wstdcall BOOLEAN ndis_isr(struct kinterrupt *kinterrupt, void *ctx);
wstdcall NDIS_STATUS WIN_FUNC(NdisMRegisterInterrupt,7)
	(struct ndis_mp_interrupt *mp_interrupt,
	 struct ndis_mp_block *nmb, UINT vector, UINT level,
	 BOOLEAN req_isr, BOOLEAN shared, enum kinterrupt_mode mode);
wstdcall void WIN_FUNC(NdisMDeregisterInterrupt,1)
	(struct ndis_mp_interrupt *mp_interrupt);
wstdcall BOOLEAN WIN_FUNC(NdisMSynchronizeWithInterrupt,3)
	(struct ndis_mp_interrupt *mp_interrupt,
	 PKSYNCHRONIZE_ROUTINE sync_func, void *ctx);
wstdcall void WIN_FUNC(NdisMIndicateStatus,4)
	(struct ndis_mp_block *nmb, NDIS_STATUS status, void *buf, UINT len);
wstdcall void WIN_FUNC(NdisMIndicateStatusComplete,1)
	(struct ndis_mp_block *nmb);
wstdcall void NdisMSendComplete(struct ndis_mp_block *nmb,
				struct ndis_packet *packet, NDIS_STATUS status);
wstdcall void NdisMSendResourcesAvailable(struct ndis_mp_block *nmb);
wstdcall void return_packet(void *arg1, void *arg2);
wstdcall void NdisMIndicateReceivePacket(struct ndis_mp_block *nmb,
					 struct ndis_packet **packets,
					 UINT nr_packets);
wstdcall void EthRxIndicateHandler(struct ndis_mp_block *nmb, void *rx_ctx,
				   char *header1, char *header, UINT header_size,
				   void *look_ahead, UINT look_ahead_size,
				   UINT packet_size);
wstdcall void NdisMTransferDataComplete(struct ndis_mp_block *nmb,
					struct ndis_packet *packet,
					NDIS_STATUS status, UINT bytes_txed);
wstdcall void EthRxComplete(struct ndis_mp_block *nmb);
wstdcall void NdisMQueryInformationComplete(struct ndis_mp_block *nmb,
					    NDIS_STATUS status);
wstdcall void NdisMSetInformationComplete(struct ndis_mp_block *nmb,
					  NDIS_STATUS status);
wstdcall void NdisMResetComplete(struct ndis_mp_block *nmb,
				 NDIS_STATUS status, BOOLEAN address_reset);
wstdcall void WIN_FUNC(NdisMSleep,1)
	(ULONG us);
wstdcall void WIN_FUNC(NdisGetCurrentSystemTime,1)
	(LARGE_INTEGER *time);
wstdcall LONG WIN_FUNC(NdisInterlockedDecrement,1)
	(LONG *val);
wstdcall LONG WIN_FUNC(NdisInterlockedIncrement,1)
	(LONG *val);
wstdcall struct nt_list *WIN_FUNC(NdisInterlockedInsertHeadList,3)
	(struct nt_list *head, struct nt_list *entry,
	 struct ndis_spinlock *lock);
wstdcall struct nt_list *WIN_FUNC(NdisInterlockedInsertTailList,3)
	(struct nt_list *head, struct nt_list *entry,
	 struct ndis_spinlock *lock);
wstdcall struct nt_list *WIN_FUNC(NdisInterlockedRemoveHeadList,2)
	(struct nt_list *head, struct ndis_spinlock *lock);
wstdcall NDIS_STATUS WIN_FUNC(NdisMInitializeScatterGatherDma,3)
	(struct ndis_mp_block *nmb, BOOLEAN dma_size, ULONG max_phy_map);
wstdcall ULONG WIN_FUNC(NdisMGetDmaAlignment,1)
	(struct ndis_mp_block *nmb);
wstdcall CHAR WIN_FUNC(NdisSystemProcessorCount,0)
	(void);
wstdcall void WIN_FUNC(NdisGetCurrentProcessorCounts,3)
	(ULONG *idle, ULONG *kernel_user, ULONG *index);
wstdcall void WIN_FUNC(NdisInitializeEvent,1)
	(struct ndis_event *ndis_event);
wstdcall BOOLEAN WIN_FUNC(NdisWaitEvent,2)
	(struct ndis_event *ndis_event, UINT ms);
wstdcall void WIN_FUNC(NdisSetEvent,1)
	(struct ndis_event *ndis_event);
wstdcall void WIN_FUNC(NdisResetEvent,1)
	(struct ndis_event *ndis_event);
wstdcall NDIS_STATUS WIN_FUNC(NdisScheduleWorkItem,1)
	(struct ndis_work_item *ndis_work_item);
wstdcall void WIN_FUNC(NdisMGetDeviceProperty,6)
	(struct ndis_mp_block *nmb, void **phy_dev, void **func_dev,
	 void **next_dev, void **alloc_res, void**trans_res);
wstdcall void WIN_FUNC(NdisMRegisterUnloadHandler,2)
	(struct driver_object *drv_obj, void *unload);
wstdcall UINT WIN_FUNC(NdisGetVersion,0)
	(void);
wstdcall NDIS_STATUS WIN_FUNC(NdisMQueryAdapterInstanceName,2)
	(struct unicode_string *name, struct ndis_mp_block *nmb);
wstdcall NDIS_STATUS WIN_FUNC(NdisWriteEventLogEntry,7)
	(void *handle, NDIS_STATUS code, ULONG value, USHORT n,
	 void *strings, ULONG datasize, void *data);
wstdcall void *WIN_FUNC(NdisGetRoutineAddress,1)
	(struct unicode_string *unicode_string);
wstdcall ULONG WIN_FUNC(NdisReadPcmciaAttributeMemory,4)
	(struct ndis_mp_block *nmb, ULONG offset, void *buffer,
	 ULONG length);
wstdcall ULONG WIN_FUNC(NdisWritePcmciaAttributeMemory,4)
	(struct ndis_mp_block *nmb, ULONG offset, void *buffer,
	 ULONG length);
wstdcall void WIN_FUNC(NdisMCoIndicateReceivePacket,3)
	(struct ndis_mp_block *nmb, struct ndis_packet **packets,
	 UINT nr_packets);
wstdcall void WIN_FUNC(NdisMCoSendComplete,3)
	(NDIS_STATUS status, struct ndis_mp_block *nmb,
	 struct ndis_packet *packet);
wstdcall void WIN_FUNC(NdisMCoRequestComplete,3)
	(NDIS_STATUS status, struct ndis_mp_block *nmb,
	 struct ndis_request *ndis_request);
wstdcall NDIS_STATUS WIN_FUNC(NdisIMNotifiyPnPEvent,2)
	(struct ndis_mp_block *nmb, struct net_pnp_event *event);
wstdcall void WIN_FUNC(NdisCompletePnPEvent,2)
	(NDIS_STATUS status, void *handle, struct net_pnp_event *event);
wstdcall NDIS_STATUS WIN_FUNC(NdisMSetMiniportSecondary,2)
	(struct ndis_mp_block *nmb2, struct ndis_mp_block *nmb1);
wstdcall NDIS_STATUS WIN_FUNC(NdisMPromoteMiniport,1)
	(struct ndis_mp_block *nmb);
wstdcall void WIN_FUNC(NdisMCoActivateVcComplete,3)
	(NDIS_STATUS status, void *handle, void *params);
wstdcall void WIN_FUNC(NdisMCoDeactivateVcComplete,2)
	(NDIS_STATUS status, void *handle);
wstdcall void WIN_FUNC(NdisMRemoveMiniport,1)
	(void *handle);
#ifdef CONFIG_X86_64
WIN_FUNC_DECL(EthRxComplete, 1)
WIN_FUNC_DECL(EthRxIndicateHandler, 8)
WIN_FUNC_DECL(NDIS_BUFFER_TO_SPAN_PAGES, 1)
WIN_FUNC_DECL(NdisAcquireReadWriteLock, 3)
WIN_FUNC_DECL(NdisAcquireSpinLock, 1)
WIN_FUNC_DECL(NdisAdjustBufferLength, 2)
WIN_FUNC_DECL(NdisAllocateBuffer, 5)
WIN_FUNC_DECL(NdisAllocateBufferPool, 3)
WIN_FUNC_DECL(NdisAllocateMemory, 4)
WIN_FUNC_DECL(NdisAllocateMemoryWithTag, 3)
WIN_FUNC_DECL(NdisAllocatePacket, 3)
WIN_FUNC_DECL(NdisAllocatePacketPool, 4)
WIN_FUNC_DECL(NdisAllocatePacketPoolEx, 5)
WIN_FUNC_DECL(NdisAllocateSpinLock, 1)
WIN_FUNC_DECL(NdisAnsiStringToUnicodeString, 2)
WIN_FUNC_DECL(NdisBufferLength, 1)
WIN_FUNC_DECL(NdisBufferVirtualAddress, 1)
WIN_FUNC_DECL(NdisCancelTimer, 2)
WIN_FUNC_DECL(NdisCloseConfiguration, 1)
WIN_FUNC_DECL(NdisCloseFile, 1)
WIN_FUNC_DECL(NdisCompletePnPEvent, 2)
WIN_FUNC_DECL(NdisCopyFromPacketToPacket, 6)
WIN_FUNC_DECL(NdisCopyFromPacketToPacketSafe, 7)
WIN_FUNC_DECL(NdisDprAcquireSpinLock, 1)
WIN_FUNC_DECL(NdisDprAllocatePacket, 3)
WIN_FUNC_DECL(NdisDprReleaseSpinLock, 1)
WIN_FUNC_DECL(NdisFreeBuffer, 1)
WIN_FUNC_DECL(NdisFreeBufferPool, 1)
WIN_FUNC_DECL(NdisFreeMemory, 3)
WIN_FUNC_DECL(NdisFreePacket, 1)
WIN_FUNC_DECL(NdisFreePacketPool, 1)
WIN_FUNC_DECL(NdisFreeSpinLock, 1)
WIN_FUNC_DECL(NdisGetBufferPhysicalArraySize, 2)
WIN_FUNC_DECL(NdisGetCurrentProcessorCounts, 3)
WIN_FUNC_DECL(NdisGetCurrentSystemTime, 1)
WIN_FUNC_DECL(NdisGetFirstBufferFromPacket, 6)
WIN_FUNC_DECL(NdisGetFirstBufferFromPacketSafe, 6)
WIN_FUNC_DECL(NdisGetRoutineAddress, 1)
WIN_FUNC_DECL(NdisGetSystemUpTime, 1)
WIN_FUNC_DECL(NdisGetVersion, 0)
WIN_FUNC_DECL(NdisIMCopySendPerPacketInfo, 2)
WIN_FUNC_DECL(NdisIMGetCurrentPacketStack, 2)
WIN_FUNC_DECL(NdisIMNotifiyPnPEvent, 2)
WIN_FUNC_DECL(NdisImmediateReadPciSlotInformation, 5)
WIN_FUNC_DECL(NdisImmediateReadPortUchar, 3)
WIN_FUNC_DECL(NdisImmediateWritePortUchar, 3)
WIN_FUNC_DECL(NdisInitAnsiString, 2)
WIN_FUNC_DECL(NdisInitUnicodeString, 2)
WIN_FUNC_DECL(NdisInitializeEvent, 1)
WIN_FUNC_DECL(NdisInitializeReadWriteLock, 1)
WIN_FUNC_DECL(NdisInitializeString, 2)
WIN_FUNC_DECL(NdisInitializeTimer, 3)
WIN_FUNC_DECL(NdisInitializeWrapper, 4)
WIN_FUNC_DECL(NdisInterlockedDecrement, 1)
WIN_FUNC_DECL(NdisInterlockedIncrement, 1)
WIN_FUNC_DECL(NdisInterlockedInsertHeadList, 3)
WIN_FUNC_DECL(NdisInterlockedInsertTailList, 3)
WIN_FUNC_DECL(NdisInterlockedRemoveHeadList, 2)
WIN_FUNC_DECL(NdisMAllocateMapRegisters, 5)
WIN_FUNC_DECL(NdisMAllocateSharedMemory, 5)
WIN_FUNC_DECL(NdisMAllocateSharedMemoryAsync, 4)
WIN_FUNC_DECL(NdisMCancelTimer, 2)
WIN_FUNC_DECL(NdisMCoActivateVcComplete, 3)
WIN_FUNC_DECL(NdisMCoDeactivateVcComplete, 2)
WIN_FUNC_DECL(NdisMCoIndicateReceivePacket, 3)
WIN_FUNC_DECL(NdisMCoRequestComplete, 3)
WIN_FUNC_DECL(NdisMCoSendComplete, 3)
WIN_FUNC_DECL(NdisMCompleteBufferPhysicalMapping, 3)
WIN_FUNC_DECL(NdisMDeregisterAdapterShutdownHandler, 1)
WIN_FUNC_DECL(NdisMDeregisterDevice, 1)
WIN_FUNC_DECL(NdisMDeregisterInterrupt, 1)
WIN_FUNC_DECL(NdisMDeregisterIoPortRange, 4)
WIN_FUNC_DECL(NdisMFreeMapRegisters, 1)
WIN_FUNC_DECL(NdisMFreeSharedMemory, 5)
WIN_FUNC_DECL(NdisMGetDeviceProperty, 6)
WIN_FUNC_DECL(NdisMGetDmaAlignment, 1)
WIN_FUNC_DECL(NdisMIndicateReceivePacket, 3)
WIN_FUNC_DECL(NdisMIndicateStatus, 4)
WIN_FUNC_DECL(NdisMIndicateStatusComplete, 1)
WIN_FUNC_DECL(NdisMInitializeScatterGatherDma, 3)
WIN_FUNC_DECL(NdisMInitializeTimer, 4)
WIN_FUNC_DECL(NdisMMapIoSpace, 4)
WIN_FUNC_DECL(NdisMPciAssignResources, 3)
WIN_FUNC_DECL(NdisMPromoteMiniport, 1)
WIN_FUNC_DECL(NdisMQueryAdapterInstanceName, 2)
WIN_FUNC_DECL(NdisMQueryAdapterResources, 4)
WIN_FUNC_DECL(NdisMQueryInformationComplete, 2)
WIN_FUNC_DECL(NdisMRegisterAdapterShutdownHandler, 3)
WIN_FUNC_DECL(NdisMRegisterDevice, 6)
WIN_FUNC_DECL(NdisMRegisterInterrupt, 7)
WIN_FUNC_DECL(NdisMRegisterIoPortRange, 4)
WIN_FUNC_DECL(NdisMRegisterMiniport, 3)
WIN_FUNC_DECL(NdisMRegisterUnloadHandler, 2)
WIN_FUNC_DECL(NdisMRemoveMiniport, 1)
WIN_FUNC_DECL(NdisMResetComplete, 3)
WIN_FUNC_DECL(NdisMSendComplete, 3)
WIN_FUNC_DECL(NdisMSendResourcesAvailable, 1)
WIN_FUNC_DECL(NdisMSetAttributesEx, 5)
WIN_FUNC_DECL(NdisMSetInformationComplete, 2)
WIN_FUNC_DECL(NdisMSetMiniportSecondary, 2)
WIN_FUNC_DECL(NdisMSetPeriodicTimer, 2)
WIN_FUNC_DECL(NdisMSleep, 1)
WIN_FUNC_DECL(NdisMStartBufferPhysicalMapping, 6)
WIN_FUNC_DECL(NdisMSynchronizeWithInterrupt, 3)
WIN_FUNC_DECL(NdisMTransferDataComplete, 4)
WIN_FUNC_DECL(NdisMUnmapIoSpace, 3)
WIN_FUNC_DECL(NdisMapFile, 3)
WIN_FUNC_DECL(NdisOpenConfiguration, 3)
WIN_FUNC_DECL(NdisOpenConfigurationKeyByIndex, 5)
WIN_FUNC_DECL(NdisOpenConfigurationKeyByName, 4)
WIN_FUNC_DECL(NdisOpenFile, 5)
WIN_FUNC_DECL(NdisOpenProtocolConfiguration, 3)
WIN_FUNC_DECL(NdisPacketPoolUsage, 1)
WIN_FUNC_DECL(NdisQueryBuffer, 3)
WIN_FUNC_DECL(NdisQueryBufferOffset, 3)
WIN_FUNC_DECL(NdisQueryBufferSafe, 4)
WIN_FUNC_DECL(NdisReadConfiguration, 5)
WIN_FUNC_DECL(NdisReadNetworkAddress, 4)
WIN_FUNC_DECL(NdisReadPciSlotInformation, 5)
WIN_FUNC_DECL(NdisReadPcmciaAttributeMemory, 4)
WIN_FUNC_DECL(NdisReadPortUchar, 3)
WIN_FUNC_DECL(NdisReleaseReadWriteLock, 2)
WIN_FUNC_DECL(NdisReleaseSpinLock, 1)
WIN_FUNC_DECL(NdisResetEvent, 1)
WIN_FUNC_DECL(NdisScheduleWorkItem, 1)
WIN_FUNC_DECL(NdisSend, 3)
WIN_FUNC_DECL(NdisSetEvent, 1)
WIN_FUNC_DECL(NdisSetTimer, 2)
WIN_FUNC_DECL(NdisSystemProcessorCount, 0)
WIN_FUNC_DECL(NdisTerminateWrapper, 2)
WIN_FUNC_DECL(NdisUnchainBufferAtBack, 2)
WIN_FUNC_DECL(NdisUnchainBufferAtFront, 2)
WIN_FUNC_DECL(NdisUnicodeStringToAnsiString, 2)
WIN_FUNC_DECL(NdisUnmapFile, 1)
WIN_FUNC_DECL(NdisUpcaseUnicodeString, 2)
WIN_FUNC_DECL(NdisWaitEvent, 2)
WIN_FUNC_DECL(NdisWriteConfiguration, 4)
WIN_FUNC_DECL(NdisWriteErrorLogEntry, 12)
WIN_FUNC_DECL(NdisWriteEventLogEntry, 7)
WIN_FUNC_DECL(NdisWritePciSlotInformation, 5)
WIN_FUNC_DECL(NdisWritePcmciaAttributeMemory, 4)
WIN_FUNC_DECL(NdisWritePortUchar, 3)
WIN_FUNC_DECL(alloc_shared_memory_async, 2)
WIN_FUNC_DECL(deserialized_irq_handler, 4)
WIN_FUNC_DECL(mp_timer_dpc, 4)
WIN_FUNC_DECL(ndis_isr, 2)
WIN_FUNC_DECL(return_packet, 2)
WIN_FUNC_DECL(serialized_irq_handler, 4)
#endif
extern struct wrap_export ndis_exports[];
struct wrap_export ndis_exports[] = {
	WIN_SYMBOL(NDIS_BUFFER_TO_SPAN_PAGES, 1),
	WIN_SYMBOL(NdisAcquireReadWriteLock, 3),
	WIN_SYMBOL(NdisAcquireSpinLock, 1),
	WIN_SYMBOL(NdisAdjustBufferLength, 2),
	WIN_SYMBOL(NdisAllocateBuffer, 5),
	WIN_SYMBOL(NdisAllocateBufferPool, 3),
	WIN_SYMBOL(NdisAllocateMemory, 4),
	WIN_SYMBOL(NdisAllocateMemoryWithTag, 3),
	WIN_SYMBOL(NdisAllocatePacket, 3),
	WIN_SYMBOL(NdisAllocatePacketPool, 4),
	WIN_SYMBOL(NdisAllocatePacketPoolEx, 5),
	WIN_SYMBOL(NdisAllocateSpinLock, 1),
	WIN_SYMBOL(NdisAnsiStringToUnicodeString, 2),
	WIN_SYMBOL(NdisBufferLength, 1),
	WIN_SYMBOL(NdisBufferVirtualAddress, 1),
	WIN_SYMBOL(NdisCancelTimer, 2),
	WIN_SYMBOL(NdisCloseConfiguration, 1),
	WIN_SYMBOL(NdisCloseFile, 1),
	WIN_SYMBOL(NdisCompletePnPEvent, 2),
	WIN_SYMBOL(NdisCopyFromPacketToPacket, 6),
	WIN_SYMBOL(NdisCopyFromPacketToPacketSafe, 7),
	WIN_SYMBOL(NdisDprAcquireSpinLock, 1),
	WIN_SYMBOL(NdisDprAllocatePacket, 3),
	WIN_SYMBOL(NdisDprReleaseSpinLock, 1),
	WIN_SYMBOL(NdisFreeBuffer, 1),
	WIN_SYMBOL(NdisFreeBufferPool, 1),
	WIN_SYMBOL(NdisFreeMemory, 3),
	WIN_SYMBOL(NdisFreePacket, 1),
	WIN_SYMBOL(NdisFreePacketPool, 1),
	WIN_SYMBOL(NdisFreeSpinLock, 1),
	WIN_SYMBOL(NdisGetBufferPhysicalArraySize, 2),
	WIN_SYMBOL(NdisGetCurrentProcessorCounts, 3),
	WIN_SYMBOL(NdisGetCurrentSystemTime, 1),
	WIN_SYMBOL(NdisGetFirstBufferFromPacket, 6),
	WIN_SYMBOL(NdisGetFirstBufferFromPacketSafe, 6),
	WIN_SYMBOL(NdisGetRoutineAddress, 1),
	WIN_SYMBOL(NdisGetSystemUpTime, 1),
	WIN_SYMBOL(NdisGetVersion, 0),
	WIN_SYMBOL(NdisIMCopySendPerPacketInfo, 2),
	WIN_SYMBOL(NdisIMGetCurrentPacketStack, 2),
	WIN_SYMBOL(NdisIMNotifiyPnPEvent, 2),
	WIN_SYMBOL(NdisImmediateReadPciSlotInformation, 5),
	WIN_SYMBOL(NdisImmediateReadPortUchar, 3),
	WIN_SYMBOL(NdisImmediateWritePortUchar, 3),
	WIN_SYMBOL(NdisInitAnsiString, 2),
	WIN_SYMBOL(NdisInitUnicodeString, 2),
	WIN_SYMBOL(NdisInitializeEvent, 1),
	WIN_SYMBOL(NdisInitializeReadWriteLock, 1),
	WIN_SYMBOL(NdisInitializeString, 2),
	WIN_SYMBOL(NdisInitializeTimer, 3),
	WIN_SYMBOL(NdisInitializeWrapper, 4),
	WIN_SYMBOL(NdisInterlockedDecrement, 1),
	WIN_SYMBOL(NdisInterlockedIncrement, 1),
	WIN_SYMBOL(NdisInterlockedInsertHeadList, 3),
	WIN_SYMBOL(NdisInterlockedInsertTailList, 3),
	WIN_SYMBOL(NdisInterlockedRemoveHeadList, 2),
	WIN_SYMBOL(NdisMAllocateMapRegisters, 5),
	WIN_SYMBOL(NdisMAllocateSharedMemory, 5),
	WIN_SYMBOL(NdisMAllocateSharedMemoryAsync, 4),
	WIN_SYMBOL(NdisMCancelTimer, 2),
	WIN_SYMBOL(NdisMCoActivateVcComplete, 3),
	WIN_SYMBOL(NdisMCoDeactivateVcComplete, 2),
	WIN_SYMBOL(NdisMCoIndicateReceivePacket, 3),
	WIN_SYMBOL(NdisMCoRequestComplete, 3),
	WIN_SYMBOL(NdisMCoSendComplete, 3),
	WIN_SYMBOL(NdisMCompleteBufferPhysicalMapping, 3),
	WIN_SYMBOL(NdisMDeregisterAdapterShutdownHandler, 1),
	WIN_SYMBOL(NdisMDeregisterDevice, 1),
	WIN_SYMBOL(NdisMDeregisterInterrupt, 1),
	WIN_SYMBOL(NdisMDeregisterIoPortRange, 4),
	WIN_SYMBOL(NdisMFreeMapRegisters, 1),
	WIN_SYMBOL(NdisMFreeSharedMemory, 5),
	WIN_SYMBOL(NdisMGetDeviceProperty, 6),
	WIN_SYMBOL(NdisMGetDmaAlignment, 1),
	WIN_SYMBOL(NdisMIndicateStatus, 4),
	WIN_SYMBOL(NdisMIndicateStatusComplete, 1),
	WIN_SYMBOL(NdisMInitializeScatterGatherDma, 3),
	WIN_SYMBOL(NdisMInitializeTimer, 4),
	WIN_SYMBOL(NdisMMapIoSpace, 4),
	WIN_SYMBOL(NdisMPciAssignResources, 3),
	WIN_SYMBOL(NdisMPromoteMiniport, 1),
	WIN_SYMBOL(NdisMQueryAdapterInstanceName, 2),
	WIN_SYMBOL(NdisMQueryAdapterResources, 4),
	WIN_SYMBOL(NdisMRegisterAdapterShutdownHandler, 3),
	WIN_SYMBOL(NdisMRegisterDevice, 6),
	WIN_SYMBOL(NdisMRegisterInterrupt, 7),
	WIN_SYMBOL(NdisMRegisterIoPortRange, 4),
	WIN_SYMBOL(NdisMRegisterMiniport, 3),
	WIN_SYMBOL(NdisMRegisterUnloadHandler, 2),
	WIN_SYMBOL(NdisMRemoveMiniport, 1),
	WIN_SYMBOL(NdisMSetAttributesEx, 5),
	WIN_SYMBOL(NdisMSetMiniportSecondary, 2),
	WIN_SYMBOL(NdisMSetPeriodicTimer, 2),
	WIN_SYMBOL(NdisMSleep, 1),
	WIN_SYMBOL(NdisMStartBufferPhysicalMapping, 6),
	WIN_SYMBOL(NdisMSynchronizeWithInterrupt, 3),
	WIN_SYMBOL(NdisMUnmapIoSpace, 3),
	WIN_SYMBOL(NdisMapFile, 3),
	WIN_SYMBOL(NdisOpenConfiguration, 3),
	WIN_SYMBOL(NdisOpenConfigurationKeyByIndex, 5),
	WIN_SYMBOL(NdisOpenConfigurationKeyByName, 4),
	WIN_SYMBOL(NdisOpenFile, 5),
	WIN_SYMBOL(NdisOpenProtocolConfiguration, 3),
	WIN_SYMBOL(NdisPacketPoolUsage, 1),
	WIN_SYMBOL(NdisQueryBuffer, 3),
	WIN_SYMBOL(NdisQueryBufferOffset, 3),
	WIN_SYMBOL(NdisQueryBufferSafe, 4),
	WIN_SYMBOL(NdisReadConfiguration, 5),
	WIN_SYMBOL(NdisReadNetworkAddress, 4),
	WIN_SYMBOL(NdisReadPciSlotInformation, 5),
	WIN_SYMBOL(NdisReadPcmciaAttributeMemory, 4),
	WIN_SYMBOL(NdisReadPortUchar, 3),
	WIN_SYMBOL(NdisReleaseReadWriteLock, 2),
	WIN_SYMBOL(NdisReleaseSpinLock, 1),
	WIN_SYMBOL(NdisResetEvent, 1),
	WIN_SYMBOL(NdisScheduleWorkItem, 1),
	WIN_SYMBOL(NdisSend, 3),
	WIN_SYMBOL(NdisSetEvent, 1),
	WIN_SYMBOL(NdisSetTimer, 2),
	WIN_SYMBOL(NdisSystemProcessorCount, 0),
	WIN_SYMBOL(NdisTerminateWrapper, 2),
	WIN_SYMBOL(NdisUnchainBufferAtBack, 2),
	WIN_SYMBOL(NdisUnchainBufferAtFront, 2),
	WIN_SYMBOL(NdisUnicodeStringToAnsiString, 2),
	WIN_SYMBOL(NdisUnmapFile, 1),
	WIN_SYMBOL(NdisUpcaseUnicodeString, 2),
	WIN_SYMBOL(NdisWaitEvent, 2),
	WIN_SYMBOL(NdisWriteConfiguration, 4),
	WIN_SYMBOL(NdisWriteErrorLogEntry, 12),
	WIN_SYMBOL(NdisWriteEventLogEntry, 7),
	WIN_SYMBOL(NdisWritePciSlotInformation, 5),
	WIN_SYMBOL(NdisWritePcmciaAttributeMemory, 4),
	WIN_SYMBOL(NdisWritePortUchar, 3),
	{NULL, NULL}
};
