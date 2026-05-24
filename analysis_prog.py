from intelhex import IntelHex

hex_data = IntelHex('FAST8960_RM821.hex')
#hex_data.tobinfile('FAST8960_RM821.bin')
data = hex_data.tobinstr()

print(f'Load address: 0x{hex_data.minaddr():08X} to 0x{hex_data.maxaddr():08X}')

QHSUSB_ARMPRG_UTF16le = 'QHSUSB_ARMPRG'.encode('utf-16le')
QHSUSB_BULK_UTF16le = 'QHSUSB__BULK'.encode('utf-16le')

if QHSUSB_ARMPRG_UTF16le in data:   
    print('QHSUSB_ARMPRG found in the prog.')
elif QHSUSB_BULK_UTF16le in data:
    print('QHSUSB__BULK found in the prog.')
else:
    print('Neither QHSUSB_ARMPRG nor QHSUSB__BULK found in the prog.')