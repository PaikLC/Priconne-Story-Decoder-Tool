
/**
 * `b64.h' - b64
 *
 * copyright (c) 2014 joseph werle
 */

#ifndef B64_H
#define B64_H 1

typedef struct b64_buffer {
    char * ptr;
    int bufc;
} b64_buffer_t;

/**
 *  Memory allocation functions to use. You can define b64_malloc and
 * b64_realloc to custom functions if you want.
 */

#ifndef b64_malloc
#  define b64_malloc(ptr) malloc(ptr)
#endif
#ifndef b64_realloc
#  define b64_realloc(ptr, size) realloc(ptr, size)
#endif

 // How much memory to allocate per buffer
#define B64_BUFFER_SIZE		(1024 * 64) // 64K

 // Start buffered memory
int b64_buf_malloc(b64_buffer_t * buffer);

// Update memory size. Returns the same pointer if we
// have enough space in the buffer. Otherwise, we add
// additional buffers.
int b64_buf_realloc(b64_buffer_t * buffer, size_t size);

/**
 * Base64 index table.
 */

static const char b64_table[] = {
  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
  0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
  0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
  0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
  0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
  0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
  0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2B, 0x2F
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encode `unsigned char *' source with `size_t' size.
 * Returns a `char *' base64 encoded string.
 */

char *
b64_encode (const unsigned char *, size_t);

/**
 * Decode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string.
 */
unsigned char *
b64_decode (const char *, size_t);

/**
 * Decode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string + size of decoded string.
 */
unsigned char *
b64_decode_ex (const char *, size_t, size_t *);

#ifdef __cplusplus
}
#endif

#endif
