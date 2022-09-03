// clang -g -O0 -L./libpng/.libs driver.c -o driver -I./libpng -lpng
// lldb driver ~/Downloads/Gunther1.png

#include <stdlib.h>
#include <stdio.h>

#include "libpng/png.h"


void dumb() {
  printf("dumb\n");
}

// Based loosely off https://chromium.googlesource.com/chromium/src/+/refs/heads/main/testing/libfuzzer/fuzzers/libpng_read_fuzzer.cc
int main(int argc, char* argv[]) {
  // Read file data
  FILE* f;
  char* data;
  long len;

  f = fopen(argv[1], "rb");
  fseek(f,0,SEEK_END);
  len = ftell(f);
  rewind(f);
  data = (char *)malloc(len * sizeof(char));
  fread(data, len, 1, f);
  fclose(f);

  // Read png from lib
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);

  png_infop info_ptr = png_create_info_struct(png_ptr);

  png_set_progressive_read_fn(png_ptr, 0,0,0,0);
  png_process_data(png_ptr, info_ptr, data, len);

  return 0;

}
