#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>

STATIC EFI_GUID mFdtTableGuid = { 
    0xb1b621d5, 0xf19c, 0x41a5,
    { 0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0 }
};

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    Print(L"Hello ARM UEFI!\n");

    EFI_LOADED_IMAGE_PROTOCOL *CurrentLoadedImage;
    EFI_STATUS Status = gBS->OpenProtocol(
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID **)&CurrentLoadedImage,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
    if (EFI_ERROR(Status)) {
        Print(L"OpenProtocol failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    // get memory map
    EFI_MEMORY_DESCRIPTOR *MemoryMap = NULL;
    UINTN MemoryMapSize = 0;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
    Status = gBS->GetMemoryMap(
        &MemoryMapSize,
        MemoryMap,
        &MapKey,
        &DescriptorSize,
        &DescriptorVersion
    );
    if (Status != EFI_BUFFER_TOO_SMALL) {
        Print(L"GetMemoryMap failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        goto gop;
    }
    MemoryMapSize += DescriptorSize * 8;
    gBS->AllocatePool(
        EfiLoaderData,
        MemoryMapSize,
        (VOID **)&MemoryMap
    );
    Status = gBS->GetMemoryMap(
        &MemoryMapSize,
        MemoryMap,
        &MapKey,
        &DescriptorSize,
        &DescriptorVersion
    );
    if (EFI_ERROR(Status)) {
        Print(L"GetMemoryMap failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        goto gop;
    }
    for (UINTN Offset = 0; Offset < MemoryMapSize; Offset += DescriptorSize)
    {
        EFI_MEMORY_DESCRIPTOR *Descriptor = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)MemoryMap + Offset);
        switch (Descriptor->Type) {
            case EfiConventionalMemory:
                Print(L"Conventional Memory: 0x%lx - 0x%lx\n", Descriptor->PhysicalStart, Descriptor->PhysicalStart + (Descriptor->NumberOfPages * 4096));
                break;
            case EfiMemoryMappedIO:
                Print(L"Memory Mapped IO: 0x%lx - 0x%lx\n", Descriptor->PhysicalStart, Descriptor->PhysicalStart + (Descriptor->NumberOfPages * 4096));
                break;
            case EfiMemoryMappedIOPortSpace:
                Print(L"Memory Mapped IO Port Space: 0x%lx - 0x%lx\n", Descriptor->PhysicalStart, Descriptor->PhysicalStart + (Descriptor->NumberOfPages * 4096));
                break;
            default:
                break;
        }
    }
    gBS->Stall(5 * 1000 * 1000);

    // try the GOP
    gop:

    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    Status = gBS->LocateProtocol(
        &gEfiGraphicsOutputProtocolGuid,
        NULL,
        (VOID **)&Gop
    );
    if (EFI_ERROR(Status)) {
        Print(L"LocateProtocol failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    UINT32 Width  = Gop->Mode->Info->HorizontalResolution;
    UINT32 Height = Gop->Mode->Info->VerticalResolution;
    Print(L"Screen Resolution: %ux%u\n", Width, Height);
    Print(L"Pixel Format: %d\n", Gop->Mode->Info->PixelFormat);

    EFI_PHYSICAL_ADDRESS FrameBufferBase = Gop->Mode->FrameBufferBase;
    UINTN FrameBufferSize = Gop->Mode->FrameBufferSize;
    Print(L"FB Base : 0x%lx\n", FrameBufferBase);
    Print(L"FB Size : %lu bytes\n", FrameBufferSize);

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Purple = {
        .Blue = 255,
        .Green = 0,
        .Red = 255,
        .Reserved = 0
    };
    Gop->Blt(
        Gop,
        &Purple,
        EfiBltVideoFill,
        0, 0, Width/2, Height/2,
        200, 200,
        0
    );

    // load lumia920.dtb
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFs;
    Status = gBS->OpenProtocol(
        CurrentLoadedImage->DeviceHandle,
        &gEfiSimpleFileSystemProtocolGuid,
        (VOID **)&SimpleFs,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
    if (EFI_ERROR(Status)) {
        Print(L"OpenProtocol(SimpleFS) failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    EFI_FILE_PROTOCOL *Root;
    Status = SimpleFs->OpenVolume(SimpleFs, &Root);
    if (EFI_ERROR(Status)) {
        Print(L"OpenVolume failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    EFI_FILE_PROTOCOL *DtbFile;
    Status = Root->Open(
        Root,
        &DtbFile,
        L"\\EFI\\BOOT\\lumia920.dtb",
        EFI_FILE_MODE_READ,
        0
    );
    if (EFI_ERROR(Status)) {
        Print(L"Open DTB failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    UINTN FileInfoSize = SIZE_OF_EFI_FILE_INFO + 256;
    UINT8 FileInfoBuffer[FileInfoSize];
    EFI_FILE_INFO *FileInfo = (EFI_FILE_INFO *)FileInfoBuffer;
    Status = DtbFile->GetInfo(
        DtbFile,
        &gEfiFileInfoGuid,
        &FileInfoSize,
        FileInfo
    );
    if (EFI_ERROR(Status)) {
        Print(L"GetInfo failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    VOID *DtbBuffer;
    UINTN DtbSize = (UINTN)FileInfo->FileSize;
    Status = gBS->AllocatePool(
        EfiLoaderData,
        DtbSize,
        &DtbBuffer
    );
    if (EFI_ERROR(Status)) {
        Print(L"AllocatePool(DTB) failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    SetMem(DtbBuffer, DtbSize, 0);
    Status = DtbFile->Read(DtbFile, &DtbSize, DtbBuffer);
    if (EFI_ERROR(Status)) {
        Print(L"Read DTB failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }
    Print(L"DTB loaded: %lu bytes @ %p\n", DtbSize, DtbBuffer);
    gBS->Stall(2 * 1000 * 1000);

    Status = gBS->InstallConfigurationTable(
        &mFdtTableGuid,
        DtbBuffer
    );
    if (EFI_ERROR(Status)) {
        Print(L"InstallConfigurationTable failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }
    Print(L"EFI DTB table installed\n");
    gBS->Stall(2 * 1000 * 1000);

    // start the linux_arm.efi
    EFI_DEVICE_PATH_PROTOCOL *KernelDevicePath = FileDevicePath(
        CurrentLoadedImage->DeviceHandle,
        L"\\EFI\\BOOT\\linux_arm.efi"
    );
    Print(L"KernelDevicePath: %s\n", ConvertDevicePathToText(KernelDevicePath, TRUE, TRUE));
    gBS->Stall(2 * 1000 * 1000);

    EFI_HANDLE NewImageHandle;
    Status = gBS->LoadImage(
        FALSE,
        ImageHandle,
        KernelDevicePath,
        NULL,
        0,
        &NewImageHandle
    );
    if (EFI_ERROR(Status)) {
        Print(L"LoadImage failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }
    Print(L"NewImageHandle: %p\n", NewImageHandle);
    gBS->Stall(2 * 1000 * 1000);

    Status = gBS->StartImage(
        NewImageHandle,
        NULL,
        NULL
    );
    if (EFI_ERROR(Status)) {
        Print(L"StartImage failed: %r\n", Status);
        gBS->Stall(2 * 1000 * 1000);
        return Status;
    }

    Print(L"Target image returned: %r\n", Status);
    gBS->Stall(2 * 1000 * 1000);
    return Status;
}