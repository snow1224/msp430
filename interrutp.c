#include <msp430.h>
unsigned char count=0,i,j;
void check(void);

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= BIT0 + BIT6;       // set P1.0 & P1.6 as output
    P1OUT &=~ (BIT0 + BIT6);
    P1DIR &=~ BIT3;             // set P1.3 as input
    P1REN |= BIT3;              // set P1.3 pull-up/pull-down enable
    P1OUT |= BIT3;             // set P1.3  pull-up
    P1OUT |= BIT0;
    while(1){

        P1OUT &=~ BIT6;
        for(j=0;j<60;j++){
            __delay_cycles(50000);
            check();
        }

        P1OUT |= BIT6;
        P1OUT &=~ BIT0;
        for(j=0;j<60;j++){
            __delay_cycles(50000);
            check();
        }
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1IFG &= ~BIT3;           // P1.3 IFG cleared
//  P1OUT |= BIT6;
//  P1OUT &=~ BIT0;
  for(i=0;i<10;i++){
              P1OUT ^= BIT6;
              __delay_cycles(200000);
          }
  __delay_cycles(300000);
}

void check(void)
{
    if((P1IN&BIT3)==0){
        for(i=0;i<10;i++){
            P1OUT ^= BIT0;
            __delay_cycles(200000);
        }
    }
}
