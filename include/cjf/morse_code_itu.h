#ifndef B9EB1BFE_4662_4774_B8CB_7BF28B287AB5
#define B9EB1BFE_4662_4774_B8CB_7BF28B287AB5

#include <stdint.h>

namespace cjf
{

/**
 * ITU Morse code table
 *
 * Characters are encoded as follows:
 *
 * Bits 2:0 - Number of dots and dashes for the character
 * Bits 7:3 - Encoded dots and dashes where 1 = dash, 0 = dot.
 *            Encoding runs LSB -> MSB ie. Bit 3 is the first dot or dash.
 *

 *
 */


/**
 * @brief International Morse Code lookup table.
 *
 * This lookup table contains the International Morse Code representation
 * for the 26 letters of the English alphabet and the 10 digits (0-9).
 * Each character is represented by a sequence of dots (.) and dashes (-).
 *
 * The index of each character in the table corresponds to:
 *   - ASCII value minus 48 for digits (eg. '0' is MORSE_CODE_ITU[0])
 *   - ASCII value minus 55 for uppercase letters (eg. 'A' is MORSE_CODE_ITU[10])
 *
 * The morse code representation is stored in a single byte as follows:
 *   - Bits 2..0: Length of the morse code sequence (up to 5)
 *   - Bits 7..3: Morse code sequence, 1 = dash, 0 = dot (LSB first)
 *
 * This javascript function can be used to encode a string of dots and dashes
 * into the right format for this table:
 *
 * ```javascript
 * function encode_morse(dotDashStr)
 * {
 *   const length = dotDashStr.length;
 *   return Array.prototype.reduce.call(dotDashStr, (prev, c, i) => {
 *     return c === "-" ? prev | (1 << i + 3) : prev;
 *   }, length);
 * }
 * ```
 */
extern const uint8_t MORSE_CODE_ITU[36];

} // namespace cjf

#endif /* B9EB1BFE_4662_4774_B8CB_7BF28B287AB5 */
