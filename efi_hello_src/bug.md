
/opt/homebrew/opt/llvm/bin/llvm-objdump -p 1.efi

1.efi:	file format coff-arm
Characteristics 0x102
	executable
	32 bit words

Time/Date               Sat Jul  4 17:43:12 2026
Magic                   010b	(PE32)
MajorLinkerVersion      14
MinorLinkerVersion      0
SizeOfCode              00000200
SizeOfInitializedData   00000400
SizeOfUninitializedData 00000000
AddressOfEntryPoint     00001001
BaseOfCode              00001000
BaseOfData              00000000
ImageBase               10000000
SectionAlignment        00001000
FileAlignment           00000200
MajorOSystemVersion     6
MinorOSystemVersion     0
MajorImageVersion       0
MinorImageVersion       0
MajorSubsystemVersion   6
MinorSubsystemVersion   0
Win32Version            00000000
SizeOfImage             00004000
SizeOfHeaders           00000200
CheckSum                00000000
Subsystem               0000000a	(EFI application)
DllCharacteristics      00008140
					DYNAMIC_BASE
					NX_COMPAT
					TERMINAL_SERVER_AWARE
SizeOfStackReserve      00100000
SizeOfStackCommit       00001000
SizeOfHeapReserve       00100000
SizeOfHeapCommit        00001000
LoaderFlags             00000000
NumberOfRvaAndSizes     00000010

The Data Directory
Entry 0 00000000 00000000 Export Directory [.edata (or where ever we found it)]
Entry 1 00000000 00000000 Import Directory [parts of .idata]
Entry 2 00000000 00000000 Resource Directory [.rsrc]
Entry 3 00000000 00000000 Exception Directory [.pdata]
Entry 4 00000000 00000000 Security Directory
Entry 5 00003000 0000000c Base Relocation Directory [.reloc]
Entry 6 00000000 00000000 Debug Directory
Entry 7 00000000 00000000 Description Directory
Entry 8 00000000 00000000 Special Directory
Entry 9 00000000 00000000 Thread Storage Directory [.tls]
Entry a 00000000 00000000 Load Configuration Directory
Entry b 00000000 00000000 Bound Import Directory
Entry c 00000000 00000000 Import Address Table Directory
Entry d 00000000 00000000 Delay Import Directory
Entry e 00000000 00000000 CLR Runtime Header
Entry f 00000000 00000000 Reserved

