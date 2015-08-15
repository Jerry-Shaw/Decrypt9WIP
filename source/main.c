#include "common.h"
#include "draw.h"
#include "fs.h"
#include "menu.h"
#include "i2c.h"
#include "decryptor/features.h"


MenuEntry menu[] =
{
	{ 0, "NCCH Xorpad Generator", "NCCH Padgen", NcchPadgen, "menu0.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "SD Xorpad Generator", "SD Padgen", SdPadgen, "menu1.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "CTR ROM Decryptor", "Decrypt ROM(s)", DecryptTitles, "menu2.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "Titlekey Decryptor (file)", "Titlekey Decryption", DecryptTitlekeysFile, "menu3.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "Titlekey Decryptor (NAND)", "Titlekey Decryption", DecryptTitlekeysNand, "menu4.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "Ticket Dumper", "Dump Ticket", DumpTicket, "menu5.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "NAND FAT16 Xorpad Generator", "CTRNAND Padgen", CtrNandPadgen, "menu6.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "TWLN FAT16 Xorpad Generator", "TWLN Padgen", TwlNandPadgen, "menu7.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "FIRM0 Xorpad Generator", "FIRM Padgen", FirmPadgen, "menu8.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
#ifdef DANGER_ZONE
	{ 0, "NAND Backup", "Backup NAND", DumpNand, "menu9.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "NAND Restore", "Restore NAND", RestoreNand, "menu10.bin", NULL, "warning.bin", "progress.bin", "done.bin", "failed.bin" },
	{ 0, "CTR Partitions Decryptor", "Decrypt CTR Partitions", DecryptCtrPartitions, "menu11.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "CTR Partitions Injector", "Inject CTR Partitions", InjectCtrPartitions, "menu12.bin", NULL, "warning.bin", "progress.bin", "done.bin", "failed.bin" },
	{ 0, "TWL Partitions Decryptor", "Decrypt TWL Partitions", DecryptTwlAgbPartitions, "menu13.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "TWL Partitions Injector", "Inject TWL Partitions", InjectTwlAgbPartitions, "menu14.bin", NULL, "warning.bin", "progress.bin", "done.bin", "failed.bin" },
#else
	{ 0, "NAND Backup", "Backup NAND", DumpNand, "menu9.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "CTR Partitions Decryptor", "Decrypt CTR Partitions", DecryptCtrPartitions, "menu11.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" },
	{ 0, "TWL Partitions Decryptor", "Decrypt TWL Partitions", DecryptTwlAgbPartitions, "menu13.bin", NULL, NULL, "progress.bin", "done.bin", "failed.bin" }
#endif
};
    
void Reboot()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2);
    while(true);
}

void PowerOff()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
    while (true);
}

int main()
{
    u32 result;
    
    InitFS();
    DebugInit();
    
    result = ProcessMenu(menu, sizeof(menu) / sizeof(MenuEntry));
    
    DeinitFS();
    (result == 1) ? Reboot() : PowerOff();
    return 0;
}
