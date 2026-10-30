#!/usr/bin/env bash
set -euo pipefail
lab_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
test_build="$(mktemp -d /tmp/lab2-tests.XXXXXX)"
trap 'rm -f -- "$test_build/rtc" "$test_build/presence" "$test_build/access"; rmdir -- "$test_build"' EXIT
flags=(-std=c11 -Wall -Wextra -Werror -fsanitize=address,undefined)
gcc "${flags[@]}" -I "$lab_dir/tests" -I "$lab_dir/Lab2_Peripherals/Core/Inc" \
    "$lab_dir/tests/test_ds1307.c" "$lab_dir/Lab2_Peripherals/Core/Src/ds1307.c" -o "$test_build/rtc"
"$test_build/rtc"
gcc "${flags[@]}" -I "$lab_dir/Lab2_Peripherals/Core/Inc" \
    "$lab_dir/tests/test_card_presence.c" "$lab_dir/Lab2_Peripherals/Core/Src/card_presence.c" -o "$test_build/presence"
"$test_build/presence"
gcc "${flags[@]}" -I "$lab_dir/tests" -I "$lab_dir/Lab2_AccessControl/Core/Inc" \
    "$lab_dir/tests/test_access_control.c" "$lab_dir/Lab2_AccessControl/Core/Src/access_control.c" -o "$test_build/access"
"$test_build/access"
