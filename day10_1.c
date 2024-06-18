#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/io.h>

#define KBD_DATA_REG        0x60    /* I/O port for keyboard data */
#define KBD_CONTROL_REG        0x64 

struct timer_list mytimer;
int ticks;
int count = 0;

void mytimer_function(struct timer_list *ptimer)
{
	
	count++;
	mod_timer(&mytimer, jiffies + ticks);
	outb(0xAE, KBD_CONTROL_REG);
}

static __init int key_init(void)
{
	int sec = 5; //disable for 5 sec
	ticks = sec * HZ;		//

	timer_setup(&mytimer, mytimer_function, 0);
	mytimer.expires = jiffies + ticks;
	add_timer(&mytimer);
    outb(0xAD, KBD_CONTROL_REG);

	
	return 0;
}

static __exit void key_exit(void)
{
	del_timer_sync(&mytimer);
  
	
}

module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("opensource");
MODULE_AUTHOR("superuser");
MODULE_DESCRIPTION("keyboard killer");













