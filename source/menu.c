#include "fs.h"
#include "draw.h"
#include "hid.h"
#include "i2c.h"
#include "menu.h"
#include "console.h"
#include "decryptor/features.h"

//variables needed for menu gui
int menu_idx = 0;
#define MENU_ITEMS 9 //10 when uncart is implemented
int TOP_Current = 0;

void Reboot()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2);
    while(true);
}

void PowerOff()
{
	i2cWriteRegister(I2C_DEV_MCU, 0x20, (u8)(1 << 0));
	while (true);
}

int MainMenu() 
{
	while (true)
	{
		
		//DRAW BOTTOM GUI
		char path[] = "/3ds/Decrypt9/UI/menu0.bin";
		path[21] = menu_idx + 48;
		DrawBottomSplash(path);	//BOTTOM SCREEN
		if (TOP_Current == 0) {
			DrawTopSplash("/3ds/Decrypt9/UI/menuTOP.bin");	//TOP SCREEN
			DrawFreeSpace();
			TOP_Current = 1;
		}
		u32 pad_state = InputWait();
		if (pad_state & BUTTON_START) {		//REBOOT
			goto reboot;
		} 
		if (pad_state & BUTTON_SELECT) {	//POWER OFF
			goto poweroff;
		}
		if ((pad_state & BUTTON_RIGHT) && menu_idx != MENU_ITEMS - 1)	//MOVE RIGHT
		{
			menu_idx++;
		}
		else if ((pad_state & BUTTON_LEFT) && menu_idx != 0)	//MOVE LEFT
		{
			menu_idx--;
		}
		else if (pad_state & BUTTON_A)
		{
			if (menu_idx == 0) {
				ConsoleInit();
				ConsoleSetTitle("NCCH Xorpad Generator");
				ConsoleShow();
				Debug("NCCH Padgen: %s!", NcchPadgen() == 0 ? "succeeded" : "failed");	//menu0.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 1) {
				ConsoleInit();
				ConsoleSetTitle("SD Xorpad Generator");
				ConsoleShow();
				Debug("SD Padgen: %s!", SdPadgen() == 0 ? "succeeded" : "failed");	//menu1.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 2) {
				ConsoleInit();
				ConsoleSetTitle("NAND fat16 Xorpad Generator");
				ConsoleShow();
				Debug("NAND Padgen: %s!", NandPadgen() == 0 ? "succeeded" : "failed");	//menu2.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 3) {
				if(pad_state & BUTTON_UP) {
				ConsoleInit();
				ConsoleSetTitle("NAND Restore");
				ConsoleShow();
				Debug("Restore NAND: %s!", RestoreNand() == 0 ? "succeeded" : "failed");	//menu3.bin
				}
				else 
				{
				ConsoleInit();
				ConsoleSetTitle("NAND Dumper");
				ConsoleShow();
				Debug("NAND Padgen: %s!", DumpNand() == 0 ? "succeeded" : "failed");	//menu3.bin
				}
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 4) {
				ConsoleInit();
				ConsoleSetTitle("Decrypt NAND Partitions");
				ConsoleShow();
			  Debug("Decrypt NAND Partitions: %s!", DecryptNandPartitions() == 0 ? "succeeded" : "failed");   //menu4.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 5) {
				ConsoleInit();
				ConsoleSetTitle("Decrypt NAND System Titles");
				ConsoleShow();
				Debug("Decrypt NAND Partitions: %s!", DecryptNandSystemTitles() == 0 ? "succeeded" : "failed");   //menu5.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 6) {
				ConsoleInit();
				ConsoleSetTitle("Decrypt Titlekeys File");
				ConsoleShow();
				Debug("Titlekey Decryption: %s!", DecryptTitlekeysFile() == 0 ? "succeeded" : "failed");	//menu6.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 7) {
				ConsoleInit();
				ConsoleSetTitle("Decrypt Titlekeys Nand");
				ConsoleShow();	
				Debug("Titlekey Decryptor: %s!", DecryptTitlekeysNand() == 0 ? "succeeded" : "failed");  //menu7.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
			else if (menu_idx == 8) {
				ConsoleInit();
				ConsoleSetTitle("Ticket Dumper");
				ConsoleShow();
				Debug("Ticket Dump: %s!", DumpTicket() == 0 ? "succeeded" : "failed");    //menu8.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}
/*			else if (menu_idx == 9) { //Not Implemented yet
				ConsoleInit();
				ConsoleSetTitle("Game Cart Dumper");
				ConsoleShow();	
			//	Debug("Dump Game: %s!", DumpGame() == 0 ? "succeeded" : "failed");  //menu9.bin
				Debug("Press B to exit");
				while (true) {
					if (InputWait() & BUTTON_B) {
						DebugClear();
						break;
					}
				}
			}*/
		}
	}
	
poweroff:
	DeinitFS();
	PowerOff();
	return 0;


reboot:
    DeinitFS();
    Reboot();
    return 0;
	
}