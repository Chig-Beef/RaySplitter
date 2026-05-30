#include <stdlib.h>
#include <memory.h>

int countUntilChar(char *str, char c) {
  char *p = str;
  while (*p && *p != c) ++p;
  return p-str;
}

char **splitString(char *str, char delim, int *outCount) {
  // How many items?
  int count = 1;
  for (char *p = str; *p; ++p) if (*p == delim) ++count;

  // Allocate buffer for items
  char **out = malloc(count*sizeof(char*));
  if (!out) return NULL;

  // Load in each arg
  char *p = str;
  for (int i = 0; i < count; ++i) {
    // Find the length of the element
    int eleLength = countUntilChar(p, delim);

    // Alloc and copy
    out[i] = malloc(eleLength+1);
    memcpy(out[i], p, eleLength);
    out[i][eleLength] = 0;

    p += eleLength+1;
  }

  *outCount = count;
  return out;
}
