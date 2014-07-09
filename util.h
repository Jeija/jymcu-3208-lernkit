// Modify single bits in registers / bytes
#define sbi(ADDR, BIT) ((ADDR |=  (1<<BIT)))
#define cbi(ADDR, BIT) ((ADDR &= ~(1<<BIT)))
#define gbi(ADDR, BIT) ((ADDR &   (1<<BIT)))
#define tbi(ADDR, BIT) ((ADDR ^=  (1<<BIT)))

// Sleep 1 cycle
#define nop() asm volatile ("nop")
