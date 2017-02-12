#include "include/screen.h"
#include "include/idt.h"
#include "include/isr.h"
#include "include/irq.h"
#include "include/timer.h"
#include "include/kbd.h"


void kmain(){
  clear_screen();
  //print("Hello World!\nHow\nIs\nNew\nLines\nWorking?");



  //clear_screen();
  //print_char_at('b', 0, -1);
  //vidmem[4] = 'h';


  idt_install();
  isrs_install();
  irq_install_handler(0, timer_handler);
  irq_install_handler(1,keyboard_handler);
  irq_install();
  asm volatile("sti");

  //print("Installed idt, isrs, irq\n");

  //print("Hello!");
  //print_char_at('\n', 0, -1);
  print("Installed idt, isrs, irq\nWelcome to CosmOS v 1.0!\nCopyright 2017 MittuDev (Nikhil MittuDev)\n\nCosmOS: \\ >");
  //print("a\nb\nc\nd\ne\nf\ng\nh");
  //print("Hello\nW");
  /*char letter = 'a'-1;
  for(int i = 0; i< MAX_COLS*MAX_ROWS+10; i++){
    if(i%MAX_COLS == 0){
      letter++;
    }
    print_char_at(letter, i, -1);
  }*/

  while (1);
}
