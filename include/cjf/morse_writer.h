#ifndef F7AB272A_BDF9_4856_8998_E6D18FCA7101
#define F7AB272A_BDF9_4856_8998_E6D18FCA7101

#include <stdint.h>
#include "morse_code_itu.h"

namespace cjf
{

  /**
   * @brief Class for writing Morse Code using specified output functions and delays.
   */
  class morse_writer
  {
  public:
    /**
     * @brief Function pointer type for delay functions.
     */
    typedef void (*delay_func)(uint32_t milliseconds);

    /**
     * @brief Function pointer type for output functions.
     */
    typedef void (*output_func)();

    /**
     * @brief Constructor for morse_writer class.
     *
     * @param output_on Function to turn on the output.
     * @param output_off Function to turn off the output.
     * @param dot_duration_ms Duration of a dot in milliseconds.
     * @param code Pointer to the Morse Code table.
     * @param delay Function pointer to the delay function.
     */
    morse_writer(
        output_func output_on,
        output_func output_off,
        const uint32_t dot_duration_ms = 250,
        const uint8_t *code = MORSE_CODE_ITU,
        delay_func delay = delay_freertos);

    /**
     * @brief Writes a single character in Morse Code.
     *
     * Supported characters are:
     *   - 26 letters of the English alphabet (case-insenstive)
     *   - Digits 0-9
     *   - Space (outputs a word gap).
     *
     * All other characters will output a letter gap.
     *
     * @param c The character to write.
     */
    void write_character(const char c) const;

    /**
     * @brief Writes a dash (-) in Morse Code.
     */
    void write_dash() const;

    /**
     * @brief Writes a dot (.) in Morse Code.
     */
    void write_dot() const;

    /**
     * @brief Writes Morse Code from a single encoded byte.
     *
     * The single byte encoding is as follows:
     *   - Bits 2..0: Length of the morse code sequence (up to 5)
     *   - Bits 7..3: Morse code sequence, 1 = dash, 0 = dot (LSB first)
     *
     * This javascript function can be used to encode a string of dots and dashes:
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
     * @param encoded_char The encoded representation to write.
     */
    void write_encoded(uint8_t encoded_char) const;

    /**
     * @brief Writes a string in Morse Code.
     *
     * @param str The string to write.
     */
    void write_string(const char *str) const;

    /**
     * @brief Writes SOS in Morse Code.
     */
    void write_sos() const;

    /**
     * @brief Writes a letter gap in Morse Code.
     */
    void write_letter_gap() const;

    /**
     * @brief Writes a word gap in Morse Code.
     */
    void write_word_gap() const;

    /**
     * @brief Busy loop delay function using ESP-IDF.
     *
     * @param milliseconds The duration to delay in milliseconds.
     */
    static void delay_esp32(uint32_t milliseconds);

    /**
     * @brief Delay function using FreeRTOS vTaskDelay.
     * @note Resolution is limited to FreeRTOS tick time.
     *
     * @param milliseconds The duration to delay in milliseconds.
     */
    static void delay_freertos(uint32_t milliseconds);

  private:
    const uint8_t *_code;            // Pointer to the Morse Code table
    const delay_func _delay;         // Function pointer to the delay function
    const uint32_t _dot_duration_ms; // The duration of a dot in milliseconds
    const output_func _output_off;   // Function pointer to the output off function
    const output_func _output_on;    // Function pointer to the output on function
  };

} // namespace cjf

#endif /* F7AB272A_BDF9_4856_8998_E6D18FCA7101 */
