# Lumia Toy

DISCLAIMER:

```
This project is for educational and research purposes only.
Do not use this project for any malicious activities.
Do not use this project for commercial purposes.
The author is not responsible for any damage caused by the use of this project.
```

## Idea

Wana an `Embedded System` Phone Toy?

U might heard about `HTC HD2`, `iPhone 3G/4/4s/5 (checkm8)`, `iPhone 5s - X(checkm8)`, `Pinephone (Linux)`, `Sony Xperia (bootloader unlock)`, etc

BUT, u may just ignored that `Lumia WP8` series!

Since `WPInternals` Team figured out how to unlock lumia bootloader, you can run customized code on them, or even run `Linux` if you'd like to `workaround`

## Lumia 920 Background

I wana to focus on `Lumia 920 (MSM8960)` since it's classic and cheap nowadays, and it has a `4.5 inch screen`

Bootchain:

```
PBL -> SBL1 -> SBL2 -> SBL3 -> UEFI -> Windows Boot Loader -> ntoskrnl
```