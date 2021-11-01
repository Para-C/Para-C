/// Testing for the header pbl-string.h
///
/// @author Luna-Klatzer

#include <pbl.h>
#include "gtest/gtest.h"

// IMPORTANT! When actually using PblString_T, do NOT use a bigger length than of the actual string

TEST(StringTypesTest, GetLenghtOfCString) {
  EXPECT_EQ(PblGetLengthOfCString("").actual, 0);
  EXPECT_EQ(PblGetLengthOfCString("1234567890").actual, 10);
  EXPECT_EQ(PblGetLengthOfCString("12345678901234567890123456789012345678901234567890").actual, 50);
}

TEST(StringTypesTest, GetStringConversion) {
  PblString_T string_1 = PblGetStringT("hello");

  EXPECT_EQ(
    string_1.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );
  EXPECT_EQ(string_1.actual.len.actual, 5);
  EXPECT_EQ(string_1.actual.allocated_len.actual, 51);
  EXPECT_EQ(string_1.actual.str_alloc_size.actual, (size_t) 51);

  PblString_T string_2 = PblGetStringT("world");

  EXPECT_EQ(
    string_2.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );
  EXPECT_EQ(string_2.actual.len.actual, 5);
  EXPECT_EQ(string_2.actual.allocated_len.actual, 51);
  EXPECT_EQ(string_2.actual.str_alloc_size.actual, (size_t) 51);

  // deallocating the strings
  PblSafeDeallocateStringT(&string_1);
  PblSafeDeallocateStringT(&string_2);
}

TEST(StringTypesTest, SimpleAllocation1) {
  PblString_T str = PblCreateStringT("hello world", PblGetUIntT(15));

  // size is per default 50 + 1 (for null char)
  EXPECT_EQ(str.actual.str_alloc_size.actual, (50 + 1) * sizeof(char));
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  // deallocating the string
  PblSafeDeallocateStringT(&str);
}

TEST(StringTypesTest, SimpleAllocation2) {
  PblString_T str = PblCreateStringT("hello world", PblGetUIntT(60));

  // size is per default 50 + 1 (for null char) - will be resized to 100, since len is 60
  EXPECT_EQ(str.actual.str_alloc_size.actual, (100 + 1) * sizeof(char));
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  // deallocating the string
  PblSafeDeallocateStringT(&str);
}

TEST(StringTypesTest, SimpleAllocation3) {
  PblString_T str = PblCreateStringT("hello world", PblGetUIntT(600));

  // size is per default 50 + 1 (for null char) - will be resized to 100, since len is 60
  EXPECT_EQ(str.actual.str_alloc_size.actual, (650 + 1) * sizeof(char));
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  // deallocating the string
  PblSafeDeallocateStringT(&str);
}

TEST(StringTypesTest, ValidateDeallocation) {
  PblString_T str = PblCreateStringT("hello world", PblGetUIntT(49));

  // size is per default 50 + 1 (for null char) - will be resized to 100, since len is 60
  EXPECT_EQ(str.actual.str_alloc_size.actual, (50 + 1) * sizeof(char));
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  // deallocating the string
  PblSafeDeallocateStringT(&str);
}

TEST(StringTypesTest, ValidateAllocation) {
  PblString_T str = PblCreateStringT("hello world", PblGetUIntT(49));

  // size is per default 50 + 1 (for null char) - will be resized to 100, since len is 60
  EXPECT_EQ(str.actual.str_alloc_size.actual, (50 + 1) * sizeof(char));
  EXPECT_EQ(str.actual.len.actual, 49);
  EXPECT_EQ(str.actual.allocated_len.actual, 51);
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  // deallocating the string
  PblSafeDeallocateStringT(&str);
}

TEST(StringTypesTest, ValidateOverwrite) {
  PblString_T str = PblCreateStringT("hello world", PblGetUIntT(11));
  // size is per default 50 + 1 (for null char) - will be resized to 100, since len is 60
  EXPECT_EQ(str.actual.str_alloc_size.actual, (50 + 1) * sizeof(char));
  EXPECT_EQ(str.actual.len.actual, 11);
  EXPECT_EQ(str.actual.allocated_len.actual, 51);
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  PblWriteToStringT(&str, "Hello World!!!!", PblGetUIntT(15));
  EXPECT_EQ(str.actual.str_alloc_size.actual, (50 + 1) * sizeof(char));
  EXPECT_EQ(str.actual.len.actual, 15);
  EXPECT_EQ(str.actual.allocated_len.actual, 51);
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  // deallocating the string
  PblSafeDeallocateStringT(&str);
}

TEST(StringTypesTest, ValidateReallocOverwrite) {
  PblString_T str = PblCreateStringT("hello world", PblGetUIntT(11));
  // size is per default 50 + 1 (for null char) - will be resized to 100, since len is 60
  EXPECT_EQ(str.actual.str_alloc_size.actual, (50 + 1) * sizeof(char));
  EXPECT_EQ(str.actual.len.actual, 11);
  EXPECT_EQ(str.actual.allocated_len.actual, 51);
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  PblWriteToStringT(&str, "12345678901234567890123456789012345678901234567890", PblGetUIntT(50));
  EXPECT_EQ(str.actual.str_alloc_size.actual, (100 + 1) * sizeof(char));
  EXPECT_EQ(str.actual.len.actual, 50);
  EXPECT_EQ(str.actual.allocated_len.actual, 101);
  EXPECT_EQ(
    str.meta.byte_size,
    sizeof(size_t) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(char *)
  );

  // deallocating the string
  PblSafeDeallocateStringT(&str);
}