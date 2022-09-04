# goblib\_test
Unit test with googletest. shared between goblib and goblib\_m5s.
Used as a submodule in goblib and goblib\_m5s.

## test_dir

| dir / file | description|
|---|---|
|test\_dir/test\_\*.cpp| Test cases used in all tests |
|test\_dir/embedded/test\_m5s| Test cases for M5Stack |
|test\_dir/dummy/test\_dummy| Dummy for native.<br> Don't compile test\_dir/test_*.cpp if not any test\_nnn folder matched by test runner.|

## platform.ini

### Use test cases only test\_dir
test\_filter=dummy/test_dummy

### Use test cases embedded/test\_m5s and test\_dir
test\_filter=embedded/test_m5s

