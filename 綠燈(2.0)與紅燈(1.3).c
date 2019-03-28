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

    P1IE |= BIT3;
    P1IES &=~ BIT3;                      // low-to-higj
    P1IFG &=~ BIT3;                     //intrrutp flag 現在沒有中斷
    _BIS_SR(GIE);            // General Interrupt Enable

    P2IE |= BIT2;
    P2IES &=~ BIT2;                      // low-to-higj
    P2IFG &=~ BIT2;
    _BIS_SR(GIE);

    while(1){
        P1OUT |= BIT0;
        P1OUT &=~ BIT6;
        __delay_cycles(3000000);

        P1OUT |= BIT6;
        P1OUT &=~ BIT0;
        __delay_cycles(3000000);
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
//    if((P1IN&BIT3)==0){
        for(i=0;i<10;i++){
            P1OUT ^= BIT0;
            __delay_cycles(200000);
        }
//    }
    P1IFG &= ~BIT3;           // P1.3 IFG cleared
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    for(i=0;i<10;i++){
          P1OUT ^= BIT6;
         __delay_cycles(200000);
    }

    P2IFG &= ~BIT2;           // P1.3 IFG cleared
}
