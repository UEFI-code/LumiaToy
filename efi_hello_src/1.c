typedef unsigned long long UINTN;
typedef unsigned short CHAR16;
typedef void* EFI_HANDLE;
typedef long EFI_STATUS;

#define EFI_SUCCESS 0

typedef struct {
    EFI_STATUS (*OutputString)(
        void *This,
        CHAR16 *String
    );
} SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
    char _pad[64];
    SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
} EFI_SYSTEM_TABLE;

static CHAR16 msg[] = {
    'H','e','l','l','o','\r','\n',0
};

__attribute__((used)) EFI_STATUS efi_main(
    EFI_HANDLE ImageHandle,
    EFI_SYSTEM_TABLE *SystemTable
)
{
    SystemTable->ConOut->OutputString(
        SystemTable->ConOut,
        msg
    );
    while (1);

    return EFI_SUCCESS;
}