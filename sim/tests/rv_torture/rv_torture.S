#include "riscv_macros.h"

RVTEST_RV32U
RVTEST_CODE_BEGIN

  addi x1, x0, 2
  addi x2, x0, 3
  add x3, x1, x2
  sw x3, test_memory + 8, t1

  RVTEST_PASS

  TEST_PASSFAIL

RVTEST_CODE_END

.data
RVTEST_DATA_BEGIN
.align 8
test_memory: .space 64, 0
RVTEST_DATA_END
