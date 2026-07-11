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
    gBS->Stall(10 * 1000 * 1000);

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
        return Status;
    }

    EFI_DEVICE_PATH_PROTOCOL *TargetDevicePath = FileDevicePath(
        CurrentLoadedImage->DeviceHandle,
        L"\\EFI\\BOOT\\orig_bootarm.efi"
    );

    if (TargetDevicePath == NULL) {
        Print(L"FileDevicePath failed\n");
        return EFI_OUT_OF_RESOURCES;
    }
    Print(L"TargetDevicePath: %s\n", ConvertDevicePathToText(TargetDevicePath, TRUE, TRUE));

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
        return Status;
    }

    Status = gBS->StartImage(
        NewImageHandle,
        NULL,
        NULL
    );

    if (EFI_ERROR(Status)) {
        Print(L"StartImage failed: %r\n", Status);
    }

    return Status;
}