/* automatically generated from src */
wstdcall void wrap_cancel_irp(struct device_object *dev_obj, struct irp *irp);
wstdcall union nt_urb *WIN_FUNC(USBD_CreateConfigurationRequestEx,2)
	(struct usb_config_descriptor *config,
	 struct usbd_interface_list_entry *intf_list);
wstdcall struct usb_interface_descriptor *
WIN_FUNC(USBD_ParseConfigurationDescriptorEx,7)
	(struct usb_config_descriptor *config, void *start,
	 LONG bInterfaceNumber, LONG bAlternateSetting, LONG bInterfaceClass,
	 LONG bInterfaceSubClass, LONG bInterfaceProtocol);
wstdcall union nt_urb *WIN_FUNC(USBD_CreateConfigurationRequest,2)
	(struct usb_config_descriptor *config, USHORT *size);
wstdcall struct usb_interface_descriptor *
WIN_FUNC(USBD_ParseConfigurationDescriptor,3)
	(struct usb_config_descriptor *config, UCHAR bInterfaceNumber,
	 UCHAR bAlternateSetting);
wstdcall usb_common_descriptor_t *WIN_FUNC(USBD_ParseDescriptors,4)
	(void *buf, ULONG length, void *start, LONG type);
wstdcall void WIN_FUNC(USBD_GetUSBDIVersion,1)
	(struct usbd_version_info *version_info);
wstdcall void
USBD_InterfaceGetUSBDIVersion(void *context,
			      struct usbd_version_info *version_info,
			      ULONG *hcd_capa);
wstdcall BOOLEAN USBD_InterfaceIsDeviceHighSpeed(void *context);
wstdcall void USBD_InterfaceReference(void *context);
wstdcall void USBD_InterfaceDereference(void *context);
wstdcall NTSTATUS USBD_InterfaceQueryBusTime(void *context, ULONG *frame);
wstdcall NTSTATUS USBD_InterfaceSubmitIsoOutUrb(void *context,
					       union nt_urb *nt_urb);
wstdcall NTSTATUS
USBD_InterfaceQueryBusInformation(void *context, ULONG level, void *buf,
				  ULONG *buf_length, ULONG *buf_actual_length);
wstdcall NTSTATUS
USBD_InterfaceLogEntry(void *context, ULONG driver_tag, ULONG enum_tag,
		       ULONG p1, ULONG p2);
#ifdef CONFIG_X86_64
WIN_FUNC_DECL(USBD_CreateConfigurationRequest, 2)
WIN_FUNC_DECL(USBD_CreateConfigurationRequestEx, 2)
WIN_FUNC_DECL(USBD_GetUSBDIVersion, 1)
WIN_FUNC_DECL(USBD_ParseConfigurationDescriptor, 3)
WIN_FUNC_DECL(USBD_ParseConfigurationDescriptorEx, 7)
WIN_FUNC_DECL(USBD_ParseDescriptors, 4)
WIN_FUNC_DECL(wrap_cancel_irp, 2)
#endif
extern struct wrap_export usb_exports[];
struct wrap_export usb_exports[] = {
	WIN_SYMBOL(USBD_CreateConfigurationRequest, 2),
	WIN_SYMBOL(USBD_CreateConfigurationRequestEx, 2),
	WIN_SYMBOL(USBD_GetUSBDIVersion, 1),
	WIN_SYMBOL(USBD_ParseConfigurationDescriptor, 3),
	WIN_SYMBOL(USBD_ParseConfigurationDescriptorEx, 7),
	WIN_SYMBOL(USBD_ParseDescriptors, 4),
	{"_USBD_CreateConfigurationRequestEx@8", (generic_func)USBD_CreateConfigurationRequestEx},
	{"_USBD_ParseConfigurationDescriptorEx@28", (generic_func)USBD_ParseConfigurationDescriptorEx},
	{"_USBD_ParseDescriptors@16", (generic_func)USBD_ParseDescriptors},
	{NULL, NULL}
};
