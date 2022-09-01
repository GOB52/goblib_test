# goblib\_test
Unit test with googletest. shared between goblib and goblib_m5s.

## test_dir

| dir / file | description|
|---|---|
|test\_dir/test\_\*.cpp| Test cases used in all tests |
|test\_dir/embedded/test\_m5s| Test cases for M5Stack |
|test\_dir/shared/test\_shared| Dummy for native.<br> Don't compile test\_dir/test_*.cpp if not any test\_nnn folder matched by test runner.|

## platform.ini

### Use test cases only test\_dir\test\_\*.cpp
test\_ignore=embedded/*

### Use test cases embedded/test\_m5s and test\_dir/test\_\*.cpp
test\_filter=embedded/test_m5s

