#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <err.h>

#include <libsh.h>
#include <libsh/cxx.hpp>

#define SIZE 64

using namespace std::literals;

int main(int, char *argv[])
{
  long n;
  char src[SIZE];
  char res[SIZE];
  char *endptr;
  char *resptr;

  sh_init (argv[0]);
  sh_arg_parse (&argv, "Usage: "s + sh_get_program () + " [OPTION]... FROM TO\n"s, "");

  long from = sh_xx_strtol (sh_arg_operand (&argv), 0);
  long to   = sh_xx_strtol (sh_arg_operand (&argv), 0);

  sh_arg_end (argv);

  if (from < 2 || from > 36)errx (EXIT_FAILURE, "%ld: invalid base", from);
  if (to < 2 || to > 36)errx (EXIT_FAILURE, "%ld: invalid base", to);

  while (fgets(src, SIZE, stdin) != NULL){
    errno = 0;
    n = strtol(src, &endptr, from);

    if (errno != 0){
      warn (NULL); /* Out of range */
      continue;
    }

    if (*endptr != '\0' && *endptr != '\n'){
      warnx ("invalid number");
      continue;
    }

    if (n == 0){
      fputs("0\n", stdout);
      continue;
    }

    resptr = res + SIZE - 1;
    *resptr = '\0';

    do{
      int digit = n % to;
      --resptr;
      if (digit < 10){
        *resptr = '0' + digit;
      }else{
        *resptr = ('a' - 10) + digit;
      }
      n /= to;
    }while (n != 0);

    puts(resptr);
  }
}
