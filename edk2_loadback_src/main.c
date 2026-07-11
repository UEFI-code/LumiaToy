#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DevicePathLib.h>
#include <Protocol/LoadedImage.h>

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    Print(L"Hello ARM UEFI!\n");
    gBS->Stall(5 * 1000 * 1000);

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
    Print(L"CurrentLoadedImage->DeviceHandle: %p\n", CurrentLoadedImage->DeviceHandle);
    gBS->Stall(2 * 1000 * 1000);

    EFI_DEVICE_PATH_PROTOCOL *TargetDevicePath = FileDevicePath(
        CurrentLoadedImage->DeviceHandle,
        L"\\EFI\\BOOT\\orig_bootarm.efi"
    );
    Print(L"TargetDevicePath: %s\n", ConvertDevicePathToText(TargetDevicePath, TRUE, TRUE));
    gBS->Stall(2 * 1000 * 1000);

    EFI_HANDLE NewImageHandle;
    Status = gBS->LoadImage(
        FALSE,
        ImageHandle,
        TargetDevicePath,
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