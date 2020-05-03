#include <os.h>
#include <unistd.h>
#include <nspireio/console.hpp>
#include "ui.cpp"
#include "drivers/gpio.cpp"
// #include "rtc.cpp"
// #include "touchpad.cpp"
// #include <inttypes.h>

int main(void) {
// 	GPIO *gpios = new GPIO();
	// RTC *rtc = new RTC();
	// NSPIRE *ns = new NSPIRE();
	UI *ui = new UI();
	ui->init();

	while(!isKeyPressed(KEY_NSPIRE_ESC)){
		SDL_Event event;
		ui->redraw();

        SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_KEYDOWN:
				ui->handle_keydown(event.key.keysym.sym);
				break;
			default:
				break;
		}
	}
	// rtc->write_rtc(22,01,00,29,04,2020);

	// nio_console csl;
	// nio_init(&csl,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,TRUE);
	// nio_set_default(&csl);
	// nio_color(&csl,NIO_COLOR_BLACK,NIO_COLOR_WHITE);
	// nio_printf("                        GPIO Test                    ");
	// nio_printf("         Compiled the %s At %s        ",__DATE__,__TIME__);
	// nio_color(&csl,NIO_COLOR_BLACK,NIO_COLOR_LIGHTRED);
	// nio_printf("      Press ESC key to exit and H to get an help.    ");
	// nio_printf("                                                     ");
	// nio_color(&csl,NIO_COLOR_WHITE,NIO_COLOR_BLACK);
	// nio_puts("");

	// gpios->pinMode(0, GPIO::OUTPUT);
	// gpios->pinMode(4, GPIO::OUTPUT);
	// gpios->pinMode(22, GPIO::OUTPUT);
	
	// char arr[33] = "01234567890123456789012345678901";
	// char sta[33] = "O   OII         II    O   I     ";
	// while(!isKeyPressed(KEY_NSPIRE_ESC)){
	// 	for (int i = 0; i < 32; ++i)
	// 	{
	// 		nio_printf("%d",gpios->digitalRead(i));
	// 	}
	// 	nio_printf("\n");
	// 	for (int i = 0; i < 32; ++i)
	// 	{
	// 		nio_printf("%c",arr[i]);
	// 	}
	// 	nio_printf("\n");
	// 	for (int i = 0; i < 32; ++i)
	// 	{
	// 		nio_printf("%c",sta[i]);
	// 	}
	// 	nio_printf("\n");
	// 	msleep(75);
	// 	nio_clear(&csl);
	// }
	// double a = (double)gpios->analogRead(0);
	// double b = (double)gpios->analogRead(1);//VBAT
	// double c = (double)gpios->analogRead(2);//VSYS
	// double d = (double)gpios->analogRead(3);//B12
	// double e = (double)gpios->analogRead(4);//B12
	// double f = (double)gpios->analogRead(5);//B12
	
	// nio_clear(&csl);
	// nio_printf("0: %4f\n1: %4f\n2: %4f\n3: %4f\n4: %4f\n5: %4f\n",a,b,c,d,e,f);

	// 	uint32_t val = rtc->read_rtc();
	// 	nio_printf("Timestamp: %d\n",val);

	// 	nio_puts("1");
	// 	// gpios->digitalWrite(16, GPIO::LOW);
	// 	gpios->digitalWrite(5, GPIO::HIGH);
	// 	gpios->digitalWrite(6, GPIO::HIGH);
	// 	msleep(1000);

	// 	nio_puts("2");
	// 	// gpios->digitalWrite(16, GPIO::HIGH);
	// 	gpios->digitalWrite(5, GPIO::LOW);
	// 	gpios->digitalWrite(6, GPIO::LOW);
	// 	msleep(1000);
	// }

    // nio_printf("Bye World!\n");
    // nio_free(&csl);
	// wait_key_pressed();
	return 0;
}
