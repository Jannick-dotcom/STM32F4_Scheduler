/*// FreeRTOSConfig.h
#include"TaskScheduler.h"
#include <mbed.h>
//Kontext Switch
extern uint8_t switchEnable;
extern function_struct *currentTask;
extern Ticker systemSwitchEvent;

static uint32_t * stack; //This is stored on the heap rather than the stack

#define MAIN_RETURN 0xFFFFFFF9  //Tells the handler to return using the MSP
#define THREAD_RETURN 0xFFFFFFFD //Tells the handler to return using the PSP

//This defines the stack frame that is saved  by the hardware
typedef struct {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t pc;
  uint32_t psr;
} hw_stack_frame_t;

//This defines the stack frame that must be saved by the software
typedef struct {
  uint32_t r4;
  uint32_t r5;
  uint32_t r6;
  uint32_t r7;
  uint32_t r8;
  uint32_t r9;
  uint32_t r10;
  uint32_t r11;
} sw_stack_frame_t;

static char m_stack[sizeof(sw_stack_frame_t)];

int new_task(void *(*p)(void*), void * arg, void * stackaddr, int stack_size){
    int i, j;
    void * mem;
    uint32_t * argp;
    void * pc;
    hw_stack_frame_t * process_frame;
    //Disable context switching to support multi-threaded calls to this function
    systick_disable_irq();
    for(i=1; i < MAX_TASKS; i++){
        if( core_proc_table[i].flags == 0 ){
            process_frame = (hw_stack_frame_t *)(stackaddr - sizeof(hw_stack_frame_t));
            process_frame->r0 = (uint32_t)arg;
            process_frame->r1 = 0;
            process_frame->r2 = 0;
            process_frame->r3 = 0;
            process_frame->r12 = 0;
            process_frame->pc = ((uint32_t)p);
            process_frame->lr = (uint32_t)del_process;
            process_frame->psr = 0x21000000; //default PSR value
            core_proc_table[i].flags = IN_USE_FLAG | EXEC_FLAG;
            core_proc_table[i].sp = mem + stack_size - sizeof(hw_stack_frame_t) - sizeof(sw_stack_frame_t);
            break;
        }
    }
    systick_enable_irq();  //Enable context switching
    if ( i == MAX_TASKS ){
        //New task could not be created
        return 0;
    } else {
        //New task ID is i
        return i;
    }
}

//This is called when the task returns
void del_process(void){
  task_table[current_task_index].flags = 0; //clear the in use and exec flags
  SCB->ICSR |= (1<<28); //switch the context
  while(1); //once the context changes, the program will no longer return to this thread
}



//Reads the main stack pointer
static inline void * rd_stack_ptr(void){
  void * result=NULL;
  asm volatile ("MRS %0, msp\n\t"
      //"MOV r0, %0 \n\t"
      : "=r" (result) );
  return result;
}

//This saves the context on the PSP, the Cortex-M3 pushes the other registers using hardware
static inline void save_context(void){
  uint32_t scratch;
  asm volatile ("MRS %0, psp\n\t"
      "STMDB %0!, {r4-r11}\n\t"
      "MSR psp, %0\n\t"  : "=r" (scratch) );
}

//This loads the context from the PSP, the Cortex-M3 loads the other registers using hardware
static inline void load_context(void){
  uint32_t scratch;
  asm volatile ("MRS %0, psp\n\t"
      "LDMFD %0!, {r4-r11}\n\t"
      "MSR psp, %0\n\t"  : "=r" (scratch) );
}

//The SysTick interrupt handler -- this grabs the main stack value then calls the context switcher
void systick_handler(void){
    save_context();  //The context is immediately saved
    stack = (uint32_t *)rd_stack_ptr();
    if ( SysTick->CTRL & (1<16) ){ //Indicates timer counted to zero
        context_switcher();
    }
    load_context(); //Since the PSP has been updated, this loads the last state of the new task
}

//This does the same thing as the SysTick handler -- it is just triggered in a different way
void pendsv_handler(void){
    save_context();  //The context is immediately saved
    stack = (uint32_t *)rd_stack_ptr();
    core_proc_context_switcher();
    load_context(); //Since the PSP has been updated, this loads the last state of the new task
}

//This reads the PSP so that it can be stored in the task table
static inline void * rd_thread_stack_ptr(void){
    void * result=NULL;
    asm volatile ("MRS %0, psp\n\t" : "=r" (result) );
    return(result);
}

//This writes the PSP so that the task table stack pointer can be used again
static inline void wr_thread_stack_ptr(void * ptr){
    asm volatile ("MSR psp, %0\n\t" : : "r" (ptr) );
}

void context_switcher(void){
   task_table[current_task].sp = rd_proc_stack_ptr(); //Save the current task's stack pointer
   do {
      current_task++;
      if ( current_task == MAX_TASKS ){
         current_task = 0;
         *((uint32_t*)stack) = MAIN_RETURN; //Return to main process using main stack
         break;
      } else if ( task_table[current_task].flags & EXEC_FLAG ){ //Check exec flag
         //change to unprivileged mode
         *((uint32_t*)stack) = THREAD_RETURN; //Use the thread stack upon handler return
         break;
      }
   } while(1);
   wr_proc_stack_ptr( task_table[current_task].sp ); //write the value of the PSP to the new task
}*/