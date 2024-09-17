#include <cjf/morse_writer.h>

#include <driver/gpio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <cctype>

using namespace cjf;

morse_writer::morse_writer(
    output_func output_on,
    output_func output_off,
    const uint32_t dot_duration_ms,
    const uint8_t *code,
    delay_func delay)
    : _code(code), _delay(delay), _dot_duration_ms(dot_duration_ms), _output_off(output_off), _output_on(output_on)
{}

void morse_writer::write_character(const char c) const
{
  const char C = toupper(c);
  if (c >= '0' && c <= '9')
  {
    write_encoded(*(_code + c - '0'));
  }
  else if (C >= 'A' && C <= 'Z')
  {
    write_encoded(*(_code + 10 + C - 'A'));
  }
  if (C == ' ')
  {
    write_word_gap();
  }
  else
  {
    write_letter_gap();
  }
}

void morse_writer::write_dash() const
{
  _output_on();
  _delay(3 * _dot_duration_ms);
  _output_off();
  _delay(_dot_duration_ms);
}

void morse_writer::write_dot() const
{
  _output_on();
  _delay(_dot_duration_ms);
  _output_off();
  _delay(_dot_duration_ms);
}

void morse_writer::write_encoded(uint8_t encoded_char) const
{
  uint8_t length = encoded_char & 0x7;
  encoded_char >>= 3;
  for (; length > 0; length--)
  {
    if (encoded_char & 0x1)
    {
      write_dash();
    }
    else
    {
      write_dot();
    }
    encoded_char >>= 1;
  }
}

void morse_writer::write_string(const char *str) const
{
  for (; *str != '\0'; str++)
  {
    write_character(*str);
  }
}

void morse_writer::write_sos() const
{
  write_encoded(0b00000011);
  write_encoded(0b00111011);
  write_encoded(0b00000011);
  write_word_gap();
}

void morse_writer::write_letter_gap() const
{
  _output_off();
  _delay(3 * _dot_duration_ms);
}

void morse_writer::write_word_gap() const
{
  _output_off();
  _delay(7 * _dot_duration_ms);
}

void morse_writer::delay_esp32(uint32_t milliseconds)
{
  esp_rom_delay_us(milliseconds * 1000);
}

void morse_writer::delay_freertos(uint32_t milliseconds)
{
  vTaskDelay(pdMS_TO_TICKS(milliseconds));
}
