#ifndef _I386_H
#define _I386_H

#define PAGE_SIZE 4096
#define PAGE_ALIGN(x) (((x) + (PAGE_SIZE-1)) & ~(PAGE_SIZE-1))

#define KERNEL_CODE_SEG 0x8

typedef struct desc_struct {
	unsigned int a,b;
} desc_table;

#define nop() __asm__ ("nop"::)



#define iret() __asm__ ("iret"::)

#define invalidate_TLB(va) \
	__asm__("invlpg (%0)" : : "r" (va))

#define outb(value,port) \
__asm__ ("outb %%al,%%dx"::"a" (value),"d" (port))


#define inb(port) ({ \
unsigned char _v; \
__asm__ volatile ("inb %%dx,%%al":"=a" (_v):"d" (port)); \
_v; \
})

#define outb_p(value,port) \
__asm__ ("outb %%al,%%dx\n" \
		"\tjmp 1f\n" \
		"1:\tjmp 1f\n" \
		"1:"::"a" (value),"d" (port))

#define inb_p(port) ({ \
unsigned char _v; \
__asm__ volatile ("inb %%dx,%%al\n" \
	"\tjmp 1f\n" \
	"1:\tjmp 1f\n" \
	"1:":"=a" (_v):"d" (port)); \
_v; \
})

#endif
