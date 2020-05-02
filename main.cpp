#include <os.h>
#include <unistd.h>
#include <nspireio/console.hpp>
#include "ui.cpp"
#include "drivers/gpio.cpp"
// #include "rtc.cpp"
// #include "touchpad.cpp"
// #include <inttypes.h>

// int main(void) {
// 	GPIO *gpios = new GPIO();
	// RTC *rtc = new RTC();
	// NSPIRE *ns = new NSPIRE();
	// UI *ui = new UI();
	// ui->init();

	// while(!isKeyPressed(KEY_NSPIRE_ESC)){
	// 	SDL_Event event;
	// 	ui->redraw();

 //        SDL_WaitEvent(&event);
	// 	switch(event.type) {
	// 		case SDL_KEYDOWN:
	// 			ui->handle_keydown(event.key.keysym.sym);
	// 			break;
	// 		default:
	// 			break;
	// 	}
	// }
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
// 	return 0;
// }












































































#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <libndls.h>



#include "py/mpstate.h"
#include "py/nlr.h"
#include "py/compile.h"
#include "py/runtime.h"
#include "py/builtin.h"
#include "py/parse.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/stackctrl.h"
#include "py/mphal.h"
#include "py/mpthread.h"
#include "extmod/misc.h"
#include "genhdr/mpversion.h"
// #include "input.h"

// Command line options, with their defaults
/*STATIC uint emit_opt = MP_EMIT_OPT_NONE;

#if MICROPY_ENABLE_GC
	long heap_size = 1024*1024 * (sizeof(mp_uint_t) / 4);
#endif


STATIC void stderr_print_strn(void *env, const char *str, size_t len) {
    (void)env;
    ssize_t dummy = write(STDERR_FILENO, str, len);
    mp_uos_dupterm_tx_strn(str, len);
    (void)dummy;
}

const mp_print_t mp_stderr_print = {NULL, stderr_print_strn};

#define FORCED_EXIT (0x100)
STATIC int handle_uncaught_exception(mp_obj_base_t *exc) {
    // check for SystemExit
    if (mp_obj_is_subclass_fast(MP_OBJ_FROM_PTR(exc->type), MP_OBJ_FROM_PTR(&mp_type_SystemExit))) {
        // None is an exit value of 0; an int is its value; anything else is 1
        mp_obj_t exit_val = mp_obj_exception_get_value(MP_OBJ_FROM_PTR(exc));
        mp_int_t val = 0;
        if (exit_val != mp_const_none && !mp_obj_get_int_maybe(exit_val, &val)) {
            val = 1;
        }
        return FORCED_EXIT | (val & 255);
    }

    // Report all other exceptions
    mp_obj_print_exception(&mp_stderr_print, MP_OBJ_FROM_PTR(exc));
    return 1;
}

#define LEX_SRC_STR (1)
#define LEX_SRC_VSTR (2)
#define LEX_SRC_FILENAME (3)
#define LEX_SRC_STDIN (4)

STATIC int execute_from_lexer(int source_kind, const void *source, mp_parse_input_kind_t input_kind, bool is_repl) {
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        // create lexer based on source kind
        mp_lexer_t *lex;
        if (source_kind == LEX_SRC_STR) {
            const char *line = (char*) source;
            lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, line, strlen(line), false);
        } else if (source_kind == LEX_SRC_VSTR) {
            const vstr_t *vstr = (vstr_t*) source;
            lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, vstr->buf, vstr->len, false);
        } else if (source_kind == LEX_SRC_FILENAME) {
            lex = mp_lexer_new_from_file((const char*)source);
        } else { // LEX_SRC_STDIN
            lex = mp_lexer_new_from_fd(MP_QSTR__lt_stdin_gt_, 0, false);
        }

        qstr source_name = lex->source_name;

        #if MICROPY_PY___FILE__
        if (input_kind == MP_PARSE_FILE_INPUT) {
            mp_store_global(MP_QSTR___file__, MP_OBJ_NEW_QSTR(source_name));
        }
        #endif

        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);

        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, emit_opt, is_repl);

        // execute it
        mp_call_function_0(module_fun);
        // check for pending exception
        if (MP_STATE_VM(mp_pending_exception) != MP_OBJ_NULL) {
            mp_obj_t obj = MP_STATE_VM(mp_pending_exception);
            MP_STATE_VM(mp_pending_exception) = MP_OBJ_NULL;
            nlr_raise(obj);
        }

        nlr_pop();
        return 0;
    } else {
        // uncaught exception
        return handle_uncaught_exception((mp_obj_base_t*)nlr.ret_val);
    }
}*/
// STATIC char* strdup (const char* s) {
//   size_t slen = strlen(s);
//   char* result = (char*)malloc(slen + 1);
//   if(result == NULL)
//   {
//     return NULL;
//   }

//   memcpy(result, s, slen+1);
//   return result;
// }
/*
STATIC char *strjoin(const char *s1, int sep_char, const char *s2) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    char *s = (char*)malloc(l1 + l2 + 2);
    memcpy(s, s1, l1);
    if (sep_char != 0) {
        s[l1] = sep_char;
        l1 += 1;
    }
    memcpy(s + l1, s2, l2);
    s[l1 + l2] = 0;
    return s;
}
char *prompt(char *p) {
    static char buf[256];
    fputs(p, stdout);
    char *s = nio_fgets(buf, sizeof(buf), nio_get_default());
    if(!s)
        return NULL;

    return strdup(buf);
}

STATIC int do_repl(void) {
    mp_hal_stdout_tx_str("MicroPython " MICROPY_GIT_TAG " on " MICROPY_BUILD_DATE "\n");

    // use simple readline
    for (;;) {
        char *line = prompt(">>> ");
        if (line == NULL) {
            // EOF
            return 0;
        }
        while (mp_repl_continue_with_input(line)) {
            char *line2 = prompt("... ");
            if (line2 == NULL) {
                break;
            }
            char *line3 = strjoin(line, '\n', line2);
            free(line);
            free(line2);
            line = line3;
        }

        int ret = execute_from_lexer(LEX_SRC_STR, line, MP_PARSE_SINGLE_INPUT, true);
        if (ret & FORCED_EXIT) return ret;

        free(line);
    }
}*/

MP_NOINLINE int main(int argc, char **argv) {
    mp_stack_set_limit(40000 * (BYTES_PER_WORD / 4));

    setbuf(stdout, NULL);
  
    mp_stack_set_limit(32768);

    mp_init();

    mp_lexer_t *lex;
    lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, "print(\"ABCD\")", 13, false);

    qstr source_name = lex->source_name;

    mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_SINGLE_INPUT);
    mp_obj_t module_fun = mp_compile(&parse_tree, source_name, MP_EMIT_OPT_NONE, true);
    mp_call_function_0(module_fun);


    puts("Press any key to exit.");
    wait_key_pressed();

    mp_deinit();
    return 0;
}