/opt/homebrew/opt/llvm/bin/llvm-objdump -p original_boot.efi

original_boot.efi:	file format coff-<unknown arch>
Characteristics 0x2122
	executable
	large address aware
	32 bit words
	DLL

Time/Date               Wed Jan 29 12:41:02 2014
Magic                   010b	(PE32)
MajorLinkerVersion      11
MinorLinkerVersion      0
SizeOfCode              0009b200
SizeOfInitializedData   00019600
SizeOfUninitializedData 00000000
AddressOfEntryPoint     00011511
BaseOfCode              00001000
BaseOfData              0009d000
ImageBase               10000000
SectionAlignment        00001000
FileAlignment           00000200
MajorOSystemVersion     0
MinorOSystemVersion     0
MajorImageVersion       0
MinorImageVersion       0
MajorSubsystemVersion   1
MinorSubsystemVersion   0
Win32Version            00000000
SizeOfImage             000ec000
SizeOfHeaders           00000400
CheckSum                000c6101
Subsystem               0000000a	(EFI application)
DllCharacteristics      00000000
SizeOfStackReserve      00100000
SizeOfStackCommit       00001000
SizeOfHeapReserve       00100000
SizeOfHeapCommit        00001000
LoaderFlags             00000000
NumberOfRvaAndSizes     00000010

The Data Directory
Entry 0 0009c0c0 00000034 Export Directory [.edata (or where ever we found it)]
Entry 1 00000000 00000000 Import Directory [parts of .idata]
Entry 2 000d9000 0000fce0 Resource Directory [.rsrc]
Entry 3 000d3000 00005aa8 Exception Directory [.pdata]
Entry 4 000b4c00 000023d8 Security Directory
Entry 5 000e9000 00002ca0 Base Relocation Directory [.reloc]
Entry 6 00001000 00000038 Debug Directory
Entry 7 00000000 00000000 Description Directory
Entry 8 00000000 00000000 Special Directory
Entry 9 00000000 00000000 Thread Storage Directory [.tls]
Entry a 00000000 00000000 Load Configuration Directory
Entry b 00000000 00000000 Bound Import Directory
Entry c 00000000 00000000 Import Address Table Directory
Entry d 00000000 00000000 Delay Import Directory
Entry e 00000000 00000000 CLR Runtime Header
Entry f 00000000 00000000 Reserved

