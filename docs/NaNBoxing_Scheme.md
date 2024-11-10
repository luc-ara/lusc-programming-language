# NaNBoxing Scheme

## Explanation

**NaNBoxing** encodes multiple data types in a single 64-bit type, exploiting the fact that many values are defined as `NaN` by the floating-point standard, but only a few are actually used. Doubles retain their actual value, while other types are encoded in the quiet `NaN` space. This allows encoding up to 2⁴ 48-bit types or up to 2²⁰ 32-bit types. The following schema supports 2⁴ - 1 48-bit types (for pointers, which in most implementations fit within 48 bits) and 2¹⁶ 32-bit types.

### Double Space

| Bits             | Sign bit (63) | Exponent bits (62-52) | Signal bit (51) | Flag bits (50-48) | Type bits (47-32)         | Value bits (31-0)                             | Condition                                     |
|------------------|---------------|------------------------|------------------|--------------------|---------------------------|----------------------------------------------|-----------------------------------------------|
| Infinity         | `*`           | `11111111111`         | `0`              | `000`              | `0000000000000000`        | `00000000000000000000000000000000`          |                                               |
| Signalling NAN   | `*`           | `11111111111`         | `0`              | `***`              | `****************`        | `********************************`          | At least one of the last 51 bits must be 1    |
| Quiet NAN        | `*`           | `11111111111`         | `1`              | `***`              | `****************`        | `********************************`          |                                               |
| Valid double     | `*`           | `***********`         | `*`              | `***`              | `****************`        | `********************************`          | At least one of the exponent bits must be 0   |

### NaNBoxing Space (Quiet NaN)

| Bits             | Sign bit (63) | Exponent bits (62-52) | Signal bit (51) | Flag bits (50-48) | Type bits (47-32)         | Value bits (31-0)                             | Condition                                     |
|------------------|---------------|------------------------|------------------|--------------------|---------------------------|----------------------------------------------|-----------------------------------------------|
| 32-bit values    | `0`           | `11111111111`         | `1`              | `000`              | `****************`        | `********************************`          |                                               |
| Pointer values   | `*`           | `11111111111`         | `1`              | `***`              | `****************`        | `********************************`          | At least one of the sign or flag bits must be 1 |
| Error            | `0`           | `11111111111`         | `1`              | `000`              | `0000000000000000`        | `********************************`          | At least one of the value bits must be 1      |
| Boolean          | `0`           | `11111111111`         | `1`              | `000`              | `0000000000000001`        | `********************************`          |                                               |
| Comparison       | `0`           | `11111111111`         | `1`              | `000`              | `0000000000000010`        | `********************************`          |                                               |
| Character        | `0`           | `11111111111`         | `1`              | `000`              | `0000000000000011`        | `********************************`          |                                               |
| Integer          | `0`           | `11111111111`         | `1`              | `000`              | `0000000000000100`        | `********************************`          |                                               |
| String           | `0`           | `11111111111`         | `1`              | `001`              | `****************`        | `********************************`          |                                               |
| Pair             | `0`           | `11111111111`         | `1`              | `010`              | `****************`        | `********************************`          |                                               |
