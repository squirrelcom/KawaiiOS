#include <stdint.h>
#include <printk.h>
#include <descriptor_tables.h>
#include <timer.h>
#include <drivers/keyboard/ps2.h>
#include <isr.h>
#include <screen.h>

void kernel_main()
{

	char kawaii[] = {
		0x20, 0x5f, 0x20, 0x20, 0x20, 0x5f, 0x5f, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x20, 0x5f,
		0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x5f, 0x5f,
		0x5f, 0x5f, 0x20, 0xa, 0x7c, 0x20, 0x7c, 0x20, 0x2f, 0x20,
		0x2f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x28, 0x5f, 0x7c, 0x5f, 0x29, 0x20, 0x20, 0x5f, 0x20, 0x20,
		0x2f, 0x20, 0x20, 0x5f, 0x5f, 0x5f, 0x7c, 0xa, 0x7c, 0x20,
		0x7c, 0x2f, 0x20, 0x2f, 0x20, 0x20, 0x5f, 0x5f, 0x20, 0x5f,
		0x5f, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x5f,
		0x5f, 0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x7c, 0x20,
		0x7c, 0x20, 0x7c, 0x20, 0x5c, 0x20, 0x60, 0x2d, 0x2d, 0x2e,
		0x20, 0xa, 0x7c, 0x20, 0x20, 0x20, 0x20, 0x5c, 0x20, 0x2f,
		0x20, 0x5f, 0x60, 0x20, 0x5c, 0x20, 0x5c, 0x20, 0x2f, 0x5c,
		0x20, 0x2f, 0x20, 0x2f, 0x20, 0x5f, 0x60, 0x20, 0x7c, 0x20,
		0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x60,
		0x2d, 0x2d, 0x2e, 0x20, 0x5c, 0xa, 0x7c, 0x20, 0x7c, 0x5c,
		0x20, 0x20, 0x5c, 0x20, 0x28, 0x5f, 0x7c, 0x20, 0x7c, 0x5c,
		0x20, 0x56, 0x20, 0x20, 0x56, 0x20, 0x2f, 0x20, 0x28, 0x5f,
		0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x5c, 0x20, 0x5c, 0x5f,
		0x2f, 0x20, 0x2f, 0x5c, 0x5f, 0x5f, 0x2f, 0x20, 0x2f, 0xa,
		0x5c, 0x5f, 0x7c, 0x20, 0x5c, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f,
		0x2c, 0x5f, 0x7c, 0x20, 0x5c, 0x5f, 0x2f, 0x5c, 0x5f, 0x2f,
		0x20, 0x5c, 0x5f, 0x5f, 0x2c, 0x5f, 0x7c, 0x5f, 0x7c, 0x5f,
		0x7c, 0x5c, 0x5f, 0x5f, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f, 0x5f,
		0x5f, 0x2f, 0x20, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0xa, 0x0
	};

	cls();

	printk(kawaii);

	printk("the educational operating system.\n");
	printk("By Ahmed Khaled <nemoload@aol.com>\n");
	printk("Source code is at: https:/*github.com/nemoload/KawaiiOS\n\n");

	init_descriptor_tables();

	printk("[*] Global Descriptor Table updated\n");
	/* char *idt = "[*] Interrupt Descriptor Table crated\n"; */
	/* printk(idt); */

	keyboard_init();
	printk("[*] PS/2 driver is ready\n");

	__asm__ volatile ("sti");

	/* uint16_t freq = 44000; */
	/* init_timer(freq); */
	/* uint8_t mask = 4; */
	/* outb(0x60,0xED|mask); */
}
