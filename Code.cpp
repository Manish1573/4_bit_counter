#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"
#define R 0x04
#define G 0x02
#define B 0x03
XGpio gpio;
void driverInit() {
int status;
status = XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID);
if (status != XST_SUCCESS) {

print("Err: Gpio initalization failed\n\r");
} else {
print("Info: Gpio Initialization successful\n\r");
}
}
void configGpio() {
XGpio_SetDataDirection(&gpio, 1, 0);
XGpio_SetDataDirection(&gpio, 2, 1);
XGpio_DiscreteSet(&gpio, 1, 0);
}
void runProject() {
int button;
while (1) {
button = XGpio_DiscreteRead(&gpio, 2);
switch (button) {
case 1:
xil_printf("%d: ",button);
XGpio_DiscreteWrite(&gpio, 1, R);
print("\tRED\n\r");
break;
case 2:
xil_printf("%d: ",button);
XGpio_DiscreteWrite(&gpio, 1, G);
print("\tGREEN\n\r");
break;
case 4:
xil_printf("%d: ",button);
XGpio_DiscreteWrite(&gpio, 1, B);
print("\tBLUE\n\r");
break;
case 8:
xil_printf("%d: ", button);
print("\tRGB\n\r");
XGpio_DiscreteWrite(&gpio, 1, R);
sleep(1);
XGpio_DiscreteClear(&gpio, 1, R);

sleep(1);
XGpio_DiscreteWrite(&gpio, 1, G);
sleep(1);
XGpio_DiscreteClear(&gpio, 1, G);
sleep(1);
XGpio_DiscreteWrite(&gpio, 1, B);
sleep(1);
XGpio_DiscreteClear(&gpio, 1, B);
sleep(1);
break;
default:
XGpio_DiscreteClear(&gpio, 1, R);
XGpio_DiscreteClear(&gpio, 1, G);
XGpio_DiscreteClear(&gpio, 1, B);
break;
}
}
}
int main() {
init_platform();
print("Hello World\n\r");
driverInit();
configGpio();
runProject();
cleanup_platform();
return 0;
}
