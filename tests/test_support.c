#include "../s21_decimal.h"

char *decimal_to_string(s21_decimal num) {
  __int128_t res = 0;
  int sign = get_sign(num);
  int scale = get_scale(num);
  int k = 0;
  char *str = calloc(32, sizeof(char));
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 31; j++) {
      res = res + ((num.bits[i] >> j) & 1) * (__int128_t)pow(2, k);
      k++;
    }
  }
  int count = 0;
  int data[29] = {0};
  while (res) {
    data[count] = res % 10;
    count++;
    res /= 10;
  }
  if (count <= 0) {
    str[0] = '0';
  } else {
    if (scale >= count) {
      count = scale + 1;
    }

    for (int i = 0; count > 0; count--, i++) {
      if (sign && i == 0) {
        str[i] = '-';
        i++;
      }
      if (count == scale) {
        str[i] = '.';
        i++;
      }
      str[i] = data[count - 1] + '0';
    }
  }
  return str;
}