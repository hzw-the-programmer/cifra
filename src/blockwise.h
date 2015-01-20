#ifndef BLOCKWISE_H
#define BLOCKWISE_H

#include <stdint.h>
#include <stddef.h>

/* Processing function for cf_blockwise_accumulate. */
typedef void (*cf_blockwise_in_fn)(void *ctx, const uint8_t *data);

/* Processing function for cf_blockwise_xor. */
typedef void (*cf_blockwise_out_fn)(void *ctx, uint8_t *data);

/* This function manages the common abstraction of accumulating input in
 * a buffer, and processing it when a full block is available.
 *
 * partial is the buffer (maintained by the caller)
 * on entry, npartial is the currently valid count of used bytes on
 *   the front of partial.
 * on exit, npartial is updated to reflect the status of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * input is the new data to process, of length nbytes.
 * process is the processing function, passed ctx and a pointer
 *   to the data to process (always exactly nblock bytes long!)
 *   which may not neccessarily be the same as partial.
 */
void cf_blockwise_accumulate(uint8_t *partial, size_t *npartial,
                             size_t nblock,
                             const void *input, size_t nbytes,
                             cf_blockwise_in_fn process, 
                             void *ctx);

/* This function manages the common abstraction of accumulating input in
 * a buffer, and processing it when a full block is available.
 * This version supports calling a different processing function for
 * the last block.
 *
 * partial is the buffer (maintained by the caller)
 * on entry, npartial is the currently valid count of used bytes on
 *   the front of partial.
 * on exit, npartial is updated to reflect the status of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * input is the new data to process, of length nbytes.
 * process is the processing function, passed ctx and a pointer
 *   to the data to process (always exactly nblock bytes long!)
 *   which may not neccessarily be the same as partial.
 * process_final is called last (but may not be called at all if
 *   all input is buffered).
 */
void cf_blockwise_accumulate_final(uint8_t *partial, size_t *npartial,
                                   size_t nblock,
                                   const void *input, size_t nbytes,
                                   cf_blockwise_in_fn process, 
                                   cf_blockwise_in_fn process_final,
                                   void *ctx);

/* This function manages XORing an input stream with a keystream
 * to produce an output stream.  The keystream is produced in blocks
 * (ala a block cipher in counter mode).
 *
 * partial is the keystream buffer (maintained by the caller)
 * on entry, *npartial is the currently valid count of bytes in partial:
 *   unused bytes are at the *end*.  So *npartial = 4 means the last four
 *   bytes of partial are usable as keystream.
 * on exit, npartial is updated to reflect the new state of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * input is the new data to process, of length nbytes.
 * output is where to write input xored with the keystream -- also length
 *   nbytes.
 * process is the processing function, passed ctx and partial which it
 *   should fill with fresh key stream.
 */
void cf_blockwise_xor(uint8_t *partial, size_t *npartial,
                      size_t nblock,
                      const void *input, void *output, size_t nbytes,
                      cf_blockwise_out_fn newblock,
                      void *ctx);

#endif